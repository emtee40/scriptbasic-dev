#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <httpext.h>
#include <process.h>

#include "../../report.h"
#include "../../lexer.h"
#include "../../sym.h"
#include "../../expression.h"
#include "../../syntax.h"
#include "../../reader.h"
#include "../../myalloc.h"
#include "../../builder.h"
#include "../../memory.h"
#include "../../execute.h"
#include "../../buildnum.h"
#include "../../conftree.h"
#include "../../filesys.h"
#include "../../errcodes.h"
#include "../../epreproc.h"
#include "../../uniqfnam.h"

/*
ScriptBasic execution may have pointers to the standard input and
standard output functions. The print command uses the standard
output function pointer unless it is NUL. Here we implement a very
simple function that can be used as standard output function when
running under ISAPI. This function uses the ISAPI interface function
WriteClient in a very inefficient mode sending characters by character,
but the output is buffered anyway.

The function has two arguments. The first is the character to send to
the standard output. The second argument is the embedder pointer. This
pointer in this case is the ISAPI extension control block pointer.
*/
static void IsapiStdOutFunction(char Character, LPEXTENSION_CONTROL_BLOCK lpECB){
  static DWORD dwBytes = 1;
  lpECB->WriteClient(lpECB->ConnID,&Character,&dwBytes,HSE_IO_SYNC);
  }

/*
 Configuration data is read only once, when the first basic program is executed.
 This makes execution faster. You have to restart the web server for any
 configuration change.
*/
static tConfigTree MyCONF;
static char *szCache;
static char *szReportFile;
static FILE *ReportFile;
CRITICAL_SECTION csReport;
static char *szErrorMessage;

static int DoMemoryCache; /* we can switch it off while developing */
CRITICAL_SECTION csCacheWrite;
static SymbolTable ProgramCache;
static void *pCacheMemorySegment;
typedef struct _CacheItem {
  BuildObject *pMyBUILD;
  CRITICAL_SECTION csCompile;
  }CacheItem,*pCacheItem;

static void IsapiErrorScreen(LPEXTENSION_CONTROL_BLOCK lpECB){
  DWORD dwBytes;
  static char *szDefaultErrorMessage =
"</PRE></FONT>\n</BODY>\n</HTML>\n";

  if( szErrorMessage == NULL )szErrorMessage = szDefaultErrorMessage;

  dwBytes = strlen(szErrorMessage);
  lpECB->WriteClient(lpECB->ConnID,szErrorMessage,&dwBytes,HSE_IO_SYNC);

  }

int GetC(void *f){ return getc((FILE *)f); }

void isapi_report(void *vlpECB,
                  char *FileName,
                  long LineNumber,
                  unsigned int iErrorCode,
                  int iErrorSeverity,
                  int *piErrorCounter,
                  char *szErrorString,
                  unsigned long *fFlags
  ){
  char timebuf[9],datebuf[9];
  LPEXTENSION_CONTROL_BLOCK lpECB=vlpECB;
  char ErrMes[256];
  DWORD dwBytes;
  static char *szErrorHeader =
"HTTP/1.0 200 OK\nContent-Type: text/html\n\n"
"<HTML>\n<HEAD>\n<TITLE>ScriptBasic Program Error</TITLE>\n</HEAD>\n<BODY BGCOLOR=\"WHITE\">\n"
"<FONT FACE=\"VERDANA\" SIZE=\"2\">\n"
"<H1>ScriptBasic Program Error</H1>\n"
"An error happened while executing the program.<P>\n<FONT SIZE=\"3\"><TT>";

#define EMIT  dwBytes = strlen(ErrMes);lpECB->WriteClient(lpECB->ConnID,ErrMes,&dwBytes,HSE_IO_SYNC)

  if(  !((*fFlags) & REPORT_F_FRST) ){
    dwBytes = strlen(szErrorHeader);
    lpECB->WriteClient(lpECB->ConnID,szErrorHeader,&dwBytes,HSE_IO_SYNC);
    }

  if( szReportFile == NULL )return;
  EnterCriticalSection(&csReport);
  ReportFile = fopen(szReportFile,"a");
  if( ReportFile == NULL )
    LeaveCriticalSection(&csReport);

  _strtime( timebuf );
  _strdate( datebuf );
  if( szErrorString && strlen(szErrorString) > 80 )szErrorString[79] = (char)0;

  if( iErrorSeverity >= REPORT_ERROR && piErrorCounter )(*piErrorCounter)++;

  if( ReportFile )fprintf(ReportFile,"%s %s:",datebuf,timebuf);
  sprintf(ErrMes,"%s %s:",datebuf,timebuf);
  EMIT;
  if( FileName && ReportFile )fprintf(ReportFile,"%s(%ld):",FileName,LineNumber);
  if( FileName ){
    sprintf(ErrMes,"%s(%ld):",FileName,LineNumber);
    EMIT;
    }
  if( ReportFile )
    fprintf(ReportFile,(iErrorCode < MAX_ERROR_CODE ? " error &H%x:" : " error 0x%08x:"),iErrorCode);
  sprintf(ErrMes,(iErrorCode < MAX_ERROR_CODE ? " error &H%x:" : " error 0x%08x:"),iErrorCode);
  EMIT;
  if( iErrorCode >= MAX_ERROR_CODE )iErrorCode = COMMAND_ERROR_EXTENSION_SPECIFIC;
  if( szErrorString ){
    fprintf(ReportFile,en_error_messages[iErrorCode],szErrorString);
    fprintf(ReportFile,"\n");
    }else
    fprintf(ReportFile,"%s\n",en_error_messages[iErrorCode]);

  if( szErrorString ){
    sprintf(ErrMes,en_error_messages[iErrorCode],szErrorString);
    EMIT;
    sprintf(ErrMes,"<P>\n");
    EMIT;
    }else{
    sprintf(ErrMes,"%s<P>\n",en_error_messages[iErrorCode]);
    EMIT;
    }
  *fFlags |= REPORT_F_FRST;
  if( ReportFile ){
    fclose(ReportFile);
    LeaveCriticalSection(&csReport);
    }
  }


DWORD WINAPI HttpExtensionProc(LPEXTENSION_CONTROL_BLOCK lpECB){
  LexObject MyLEX;
  ReadObject MyREAD;
  BuildObject *pMyBUILD;
#define MyBUILD (*pMyBUILD)
  eXobject MyEX;
  ExecuteObject MyEXE;
  peNODE_l CommandList;
  unsigned long fErrorFlags;
  int iError,iErrorCounter;
  char *szInputFile;
  char *pszPreprocessedFileName=NULL;
  int binarycode;
#define FULL_PATH_BUFFER_LENGTH 256
  char *s;
  char Argv0[FULL_PATH_BUFFER_LENGTH];
  char CachedFileName[FULL_PATH_BUFFER_LENGTH];
  unsigned long FileTime,CacheTime;
  pCacheItem *ppCache;

//DebugBreak();

  lpECB->dwHttpStatusCode = 200; /* if no one else sets */

  /* default values for command line options */
  szInputFile = lpECB->lpszPathTranslated;
  binarycode = 0; /* input is not binary by default */
DoMemoryCache = 0;
  if( DoMemoryCache )
    ppCache = (pCacheItem *)sym_LookupSymbol(szInputFile,
                                             ProgramCache,
                                             0,
                                             alloc_Alloc,
                                             alloc_Free,
                                             pCacheMemorySegment);

  if( DoMemoryCache && ppCache && *ppCache && (*ppCache)->pMyBUILD ){
CodeIsCached:;
    /* we have to enter this critical section to get sure that
       the cache is not under compilation currently */
    EnterCriticalSection( &((*ppCache)->csCompile) );
    LeaveCriticalSection( &((*ppCache)->csCompile) );
    pMyBUILD = (*ppCache)->pMyBUILD;
    }else{

    if( DoMemoryCache ){
      EnterCriticalSection(&csCacheWrite);
      ppCache = (pCacheItem *)sym_LookupSymbol(szInputFile,
                                               ProgramCache,
                                               1,
                                               alloc_Alloc,
                                               alloc_Free,
                                               pCacheMemorySegment);

      if( *ppCache && (*ppCache)->pMyBUILD ){
        /* we get here if the code was not cached when we first looked for it
           but while getting here another thread did cache it instead of us.

           *ppCache can be non-NULL while (*ppCache)->pMyBUILD is NULL when the
           code was corrupt last time, and it is tried to be executed now. */
        LeaveCriticalSection(&csCacheWrite);
        goto CodeIsCached;
        }

      *ppCache = alloc_Alloc(sizeof(CacheItem),pCacheMemorySegment);
      if( *ppCache == NULL ){
        sprintf(lpECB->lpszLogData,"Not enough memory.");
        IsapiErrorScreen(lpECB);
        return HSE_STATUS_SUCCESS;
        }
      InitializeCriticalSection( &((*ppCache)->csCompile) );
      EnterCriticalSection( &((*ppCache)->csCompile) );
      LeaveCriticalSection( &csCacheWrite );
      }

    if( DoMemoryCache )
      pMyBUILD = alloc_Alloc(sizeof(BuildObject),pCacheMemorySegment);
    else
      pMyBUILD = malloc(sizeof(BuildObject));

    if( pMyBUILD == NULL ){
      if( DoMemoryCache ){
        (*ppCache)->pMyBUILD = NULL;
        LeaveCriticalSection( &((*ppCache)->csCompile) );
        }
      sprintf(lpECB->lpszLogData,"Not enough memory.");
      IsapiErrorScreen(lpECB);
      return HSE_STATUS_SUCCESS;
      }

    if( DoMemoryCache )
      (*ppCache)->pMyBUILD = pMyBUILD;

    if( szCache ){
      strcpy(CachedFileName,szCache);
      s = CachedFileName + strlen(CachedFileName); /* point to the end of the cache directory */

      strcpy(s,szInputFile);

      strcpy(Argv0,s);
      uniqfnam(s,s);
      FileTime  = file_time_modified(szInputFile);
      CacheTime = file_time_modified(CachedFileName);
      if( FileTime && CacheTime && CacheTime > FileTime ){
        szInputFile = CachedFileName;
      /* Check that the cache file is in correct format.
         This call will help upgrade without deleting the cache
         files. Former versions tried to load the binary code created by
         a previous version of scriba and resulted error messages
         complaining about corrupt binary file whe trying to execute
         a syntactically correct BASIC program.      */
        binarycode = build_IsFileBinaryFormat(szInputFile);
        }
     }else{
      strcpy(Argv0,szInputFile);
      }

    if( binarycode || build_IsFileBinaryFormat(szInputFile) ){
      /* the code is given as a compiled code */
      MyBUILD.memory_allocating_function = malloc;
      MyBUILD.memory_releasing_function  = free;
      MyBUILD.iErrorCounter = 0;
      MyBUILD.reportptr = lpECB;
      MyBUILD.report   = isapi_report;
      MyBUILD.fErrorFlags = 0;
      build_LoadCode(&MyBUILD,szInputFile);
      if( MyBUILD.iErrorCounter ){
        if( DoMemoryCache ){
          (*ppCache)->pMyBUILD = NULL;
          LeaveCriticalSection( &((*ppCache)->csCompile) );
          }
        alloc_FinishSegment(MyBUILD.pMemorySegment);
        sprintf(lpECB->lpszLogData,"There were %d error(s) reading the code %s while executing %s.",MyBUILD.iErrorCounter,szInputFile,Argv0);
        IsapiErrorScreen(lpECB);
        return HSE_STATUS_SUCCESS;
        }
      }else{
      /* the code is source code basic text format */
    fErrorFlags = 0;
    iErrorCounter = 0;
    iError = epreproc(&MyCONF,szInputFile,&pszPreprocessedFileName,NULL,malloc,free);
    if( iError ){
      isapi_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
      /* there were errors during preprocess */
      sprintf(lpECB->lpszLogData,"There was an error executing the externalpreprocessor.");
      IsapiErrorScreen(lpECB);
      return HSE_STATUS_SUCCESS;
      }

      reader_InitStructure(&MyREAD);
      MyREAD.memory_allocating_function = alloc_Alloc;
      MyREAD.memory_releasing_function = alloc_Free;
      MyREAD.pMemorySegment = alloc_InitSegment(malloc,free);
      MyREAD.report = isapi_report;
      MyREAD.reportptr = lpECB;
      MyREAD.iErrorCounter = 0;
      MyREAD.fErrorFlags = 0;
      MyREAD.pConfig = &MyCONF;
      if( pszPreprocessedFileName )
        reader_ReadLines(&MyREAD,pszPreprocessedFileName);
      else
        reader_ReadLines(&MyREAD,szInputFile);

      if( MyREAD.iErrorCounter ){
        /* there were errors during lexical analisys */
        if( DoMemoryCache ){
          (*ppCache)->pMyBUILD = NULL;
          LeaveCriticalSection( &((*ppCache)->csCompile) );
          }
        sprintf(lpECB->lpszLogData,"There were %d error(s) during read executing %s.",MyREAD.iErrorCounter,szInputFile);
        IsapiErrorScreen(lpECB);
        return HSE_STATUS_SUCCESS;
        }

      reader_StartIteration(&MyREAD);

      MyLEX.memory_allocating_function = alloc_Alloc;
      MyLEX.memory_releasing_function = alloc_Free;
      MyLEX.pMemorySegment = alloc_InitSegment(malloc,free);
      lex_InitStructure(&MyLEX);

      MyLEX.pfGetCharacter = reader_NextCharacter;
      MyLEX.pfFileName = reader_FileName;
      MyLEX.pfLineNumber = reader_LineNumber;

      MyLEX.pNASymbols = NASYMBOLS;
      MyLEX.pASymbols  = ASYMBOLS;
      MyLEX.pCSymbols  = CSYMBOLS;
      MyLEX.report = isapi_report;
      MyLEX.reportptr = lpECB;
      MyLEX.fErrorFlags = MyREAD.fErrorFlags;
      MyLEX.iErrorCounter = 0;
      MyLEX.pLexResult = NULL;


      MyLEX.pvInput = (void *)&MyREAD;
      lex_ReadInput(&MyLEX);

      if( MyLEX.iErrorCounter ){
        /* there were errors during lexical analisys */
        if( DoMemoryCache ){
          (*ppCache)->pMyBUILD = NULL;
          LeaveCriticalSection( &((*ppCache)->csCompile) );
          }
        sprintf(lpECB->lpszLogData,"There were %d error(s) during lex executing %s.",MyLEX.iErrorCounter,szInputFile);
        IsapiErrorScreen(lpECB);
        return HSE_STATUS_SUCCESS;
        }

      lex_RemoveComments(&MyLEX);
      lex_HandleContinuationLines(&MyLEX);

      MyEX.memory_allocating_function = malloc;
      MyEX.memory_releasing_function = free;
      MyEX.cbBuffer = 1024; /* init will allocate the space of this number of characters */
      MyEX.cbCurrentNameSpace = 1024; /* init will allocate the space of this number of characters */
      MyEX.pLex = &MyLEX;

      MyEX.Unaries  = UNARIES;
      MyEX.Binaries = BINARIES;
      MyEX.BuiltInFunctions = INTERNALFUNCTIONS;
      MyEX.MAXPREC  = MAX_BINARY_OPERATOR_PRECEDENCE;
      MyEX.PredeclaredLongConstants = PREDLCONSTS;
      MyEX.reportptr = lpECB;
      MyEX.report   = isapi_report;
      MyEX.fErrorFlags = MyLEX.fErrorFlags;
      MyEX.iErrorCounter = 0;

      MyEX.Command = COMMANDS;

      ex_init(&MyEX);

      ex_Command_l(&MyEX,&CommandList);

      if( MyEX.iErrorCounter ){
        if( DoMemoryCache ){
          (*ppCache)->pMyBUILD = NULL;
          LeaveCriticalSection( &((*ppCache)->csCompile) );
          }
        sprintf(lpECB->lpszLogData,"There were %d error(s) during syntax analisys executing %s.",MyEX.iErrorCounter,szInputFile);
        IsapiErrorScreen(lpECB);
        return HSE_STATUS_SUCCESS;
       }
 
      MyEX.pCommandList = CommandList;

      MyBUILD.memory_allocating_function = malloc;
      MyBUILD.memory_releasing_function  = free;
      MyBUILD.pEx = &MyEX;
      MyBUILD.iErrorCounter = 0;
      MyBUILD.fErrorFlags = MyEX.fErrorFlags;
      MyBUILD.FirstUNIXline = NULL; /* On Windows NT there is no need for this. */

      build_Build(&MyBUILD);

      if( MyBUILD.iErrorCounter ){
        if( DoMemoryCache ){
          (*ppCache)->pMyBUILD = NULL;
          LeaveCriticalSection( &((*ppCache)->csCompile) );
          }
          alloc_FinishSegment(MyBUILD.pMemorySegment);
        sprintf(lpECB->lpszLogData,"There were %d error(s) during building executing %s.",MyBUILD.iErrorCounter,szInputFile);
        IsapiErrorScreen(lpECB);
        return HSE_STATUS_SUCCESS;
        }

      if( DoMemoryCache )
        alloc_Merge(pCacheMemorySegment,MyBUILD.pMemorySegment);

      /* This is the very first place where we can relase the reader memory
         because syntax error messages point to the file name strings that are reserved
         by the reader. */
      alloc_FinishSegment(MyLEX.pMemorySegment);

      ex_free(&MyEX);

      if( szCache ){
        build_SaveCode(&MyBUILD,CachedFileName);
        }
      alloc_FinishSegment(MyREAD.pMemorySegment);
      }/* end of non binary code */
    /* now we have it correctly compiled, we can let others use it */
    if( DoMemoryCache )
      LeaveCriticalSection( &((*ppCache)->csCompile) );
    }/* end of no memory cache */

  MyEXE.memory_allocating_function = malloc;
  MyEXE.memory_releasing_function = free;
  MyEXE.reportptr = lpECB;
  MyEXE.report   = isapi_report;
  MyEXE.fErrorFlags = MyEX.fErrorFlags;

  MyEXE.pConfig = &MyCONF;
  //MyEXE.Argv0 = Argv0;
  build_MagicCode(&(MyEXE.Ver));
  if( execute_InitStructure(&MyEXE,pMyBUILD) ){
    sprintf(lpECB->lpszLogData,"Memory low executing %s.",szInputFile);
    IsapiErrorScreen(lpECB);
    return HSE_STATUS_SUCCESS;
    }
/*
  We could alter the standard input, standard output, the environment
  function and command arguments here . We do only the command
  arguments here in this variation. */
  MyEXE.CmdLineArgument = "";  
  MyEXE.pEmbedder = lpECB;
  MyEXE.fpStdouFunction = IsapiStdOutFunction;
  strcpy(MyEXE.Ver.Variation,"WINISAPI");

  execute_Execute(&MyEXE,&iError);
  alloc_FinishSegment(MyEXE.pMo->pMemorySegment);
  alloc_FinishSegment(MyEXE.pMemorySegment);

  if( pszPreprocessedFileName )free(pszPreprocessedFileName);

  if( ! DoMemoryCache ){
    alloc_FinishSegment(MyBUILD.pMemorySegment);
    free(pMyBUILD);
    }
  sprintf(lpECB->lpszLogData,"Executed %s.",szInputFile);
  return HSE_STATUS_SUCCESS;
  }

BOOL WINAPI TerminateExtension(DWORD dwFlags){
  char timebuf[9],datebuf[9];

  switch( dwFlags ){
    case HSE_TERM_ADVISORY_UNLOAD:
      if( szReportFile != NULL ){
        EnterCriticalSection(&csReport);
        ReportFile = fopen(szReportFile,"a");
        if( ReportFile != NULL ){
          _strtime( timebuf );
          _strdate( datebuf );
          fprintf(ReportFile,"%s %s: ScriptBasic ISAPI variation was unloaded upon request.\n",datebuf,timebuf);
          fclose(ReportFile);
          }
        LeaveCriticalSection(&csReport);
        }
      alloc_FinishSegment(MyCONF.pMemorySegment);
      MyCONF.pMemorySegment = NULL;
      return TRUE;
    case HSE_TERM_MUST_UNLOAD:
      if( szReportFile != NULL ){
        EnterCriticalSection(&csReport);
        ReportFile = fopen(szReportFile,"a");
        if( ReportFile != NULL ){
          _strtime( timebuf );
          _strdate( datebuf );
          fprintf(ReportFile,"%s %s: ScriptBasic ISAPI variation was forcefully unloaded.\n",datebuf,timebuf);
          fclose(ReportFile);
          }
        LeaveCriticalSection(&csReport);
        }
      alloc_FinishSegment(MyCONF.pMemorySegment);
      MyCONF.pMemorySegment = NULL;
      return TRUE;
    default:;
    }
  return 0;
  }

BOOL WINAPI  GetExtensionVersion(HSE_VERSION_INFO *pVer){
  char *szErrorMessageFile,*s;
  FILE *fp;
  int cbErrorMessage;
  char timebuf[9],datebuf[9];
  void *pMEM;

  pMEM = alloc_InitSegment(malloc,free);
  if( pMEM == NULL )return FALSE;

  cft_start(&MyCONF,alloc_Alloc,alloc_Free,pMEM,
#ifdef WIN32
            "Software\\ScriptBasic\\config",
            "WINNT\\SCRIBA.INI",
#else
            "SCRIBACONF",
            "/etc/scriba/basic.conf",
#endif
            NULL);
DebugBreak();
  szCache = cft_GetString(&MyCONF,"cache");
  szCache = NULL;
  szReportFile = cft_GetString(&MyCONF,"isapi.report");
  InitializeCriticalSection(&csReport);

  /* read the error message text that is sent to the client screen when
     error happens in the code. */

  szErrorMessageFile = cft_GetString(&MyCONF,"isapi.errmesfile");
  szErrorMessage = NULL;
  if( szErrorMessageFile ){
    fp = fopen(szErrorMessageFile,"rb");
    if( fp ){
      szErrorMessage = (char *)malloc((cbErrorMessage = file_size(szErrorMessageFile))+1);
      if( (s=szErrorMessage) && cbErrorMessage ){
        while( cbErrorMessage-- )*s++ = getc(fp);
        *s = (char)0;
        fclose(fp);
        }else szErrorMessage = NULL;
      }
    }

  if( szReportFile != NULL ){
    EnterCriticalSection(&csReport);
    ReportFile = fopen(szReportFile,"a");
    if( ReportFile != NULL ){
      _strtime( timebuf );
      _strdate( datebuf );
      fprintf(ReportFile,"%s %s: ScriptBasic ISAPI variation was loaded.\n",datebuf,timebuf);
      fclose(fp);
      }
    LeaveCriticalSection(&csReport);
    }

  /* This variation caches programs in memory, and we should have
     a symbol table that tells us where the collected code is.
  */

  s = cft_GetString(&MyCONF,"isapi.memcache");
  if( s ){
    pCacheMemorySegment = alloc_InitSegment(malloc,free);
    if( pCacheMemorySegment == NULL )return FALSE;
    ProgramCache = sym_NewSymbolTable(alloc_Alloc,pCacheMemorySegment);
    if( ProgramCache == NULL )return FALSE;
    InitializeCriticalSection(&csCacheWrite);
    DoMemoryCache = 1;
    }else{
    DoMemoryCache = 0;
    pCacheMemorySegment = NULL;
    ProgramCache = NULL;
    }

  pVer->dwExtensionVersion = HSE_VERSION;
  return TRUE;
  }
