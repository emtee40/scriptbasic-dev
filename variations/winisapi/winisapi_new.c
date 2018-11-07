/*
FILE:   winisapi.c
HEADER: winisapi.h

--GNU LGPL
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

--
*/

/*POD
=H ISAPI variation of ScriptBasic

This file implements the "main" function that embeds ScriptBasic as an isapi extension
application for the Microsoft IIS web server.

This function implements three major and some auxilliary functions. These are:

=toc

These are the functions that all ISAPI extensions should implement. Using this version
under Windows NT instead of the standalone version (with CGI protocol) has speed
advantage. This version reads the config file only once, and may keep the code also
in memory.

The weakness of the implementation is that after a code is loaded into memory it does
not check if the source has changed. Therefore it is recommended to turn memory caching
off during development and on in real word application.

CUT*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <httpext.h>
#include <process.h>

#include "../../scriba.h"

/*POD
=section IsapiStdOutFunction
=H Standard output function

ScriptBasic execution may have pointers to the standard input and
standard output functions. The print command uses the standard
output function pointer unless it is NULL. Here we implement a very
simple function that can be used as standard output function when
running under ISAPI. This function uses the ISAPI interface function
WriteClient in a very inefficient mode sending characters by character,
but the output is buffered anyway.

The function has two arguments. The first is the character to send to
the standard output. The second argument is the embedder pointer. This
pointer in this case is the ISAPI extension control block pointer.
/*FUNCTION*/
static void IsapiStdOutFunction(char Character,
                                LPEXTENSION_CONTROL_BLOCK lpECB
  ){
/*noverbatim
CUT*/
  static DWORD dwBytes = 1;
  lpECB->WriteClient(lpECB->ConnID,&Character,&dwBytes,HSE_IO_SYNC);
  }

/*
 Configuration data is read only once, when the first basic program is executed.
 This makes execution faster. You have to restart the web server for any
 configuration change.
*/
static pSbProgram pProgramConfig;
static char *szCache;
static char *szReportFile;
static FILE *ReportFile;
static CRITICAL_SECTION csReport;
static char *szErrorMessage;

static int DoMemoryCache; /* we can switch it off while developing */
static CRITICAL_SECTION csSymbolTable; /* to lock the symbol table */
static SymbolTable ProgramCache;
static void *pCacheMemorySegment;
typedef struct _CacheItem {
  pSbProgram pProgram;
  int boolValid; /* true if the code is loaded and valid */
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

/*POD
=section HttpExtensionProc
=H Major execution function

This is the major execution function called whenever the extension is expected to run a
BASIC program.

/*FUNCTION*/
DWORD WINAPI HttpExtensionProc(LPEXTENSION_CONTROL_BLOCK lpECB
  ){
/*noverbatim
CUT*/
  pSbProgram pProgram;
  unsigned long fErrorFlags;
  int iError,iErrorCounter;
  char *szInputFile;
  char *pszPreprocessedFileName=NULL;
  int binarycode;
#define FULL_PATH_BUFFER_LENGTH 256
  pCacheItem *ppCache;

  lpECB->dwHttpStatusCode = 200; /* if no one else sets */

  /* default values for command line options */
  szInputFile = lpECB->lpszPathTranslated;

  if( DoMemoryCache ){

    EnterCriticalSection(&csSymbolTable);
    ppCache = (pCacheItem *)sym_LookupSymbol(szInputFile,
                                             ProgramCache,
                                             1,
                                             alloc_Alloc,
                                             alloc_Free,
                                             pCacheMemorySegment);
    /* if the file is not in the cache yet then allocate space for the description */
    if( *ppCache == NULL ){
        *ppCache = alloc_Alloc(sizeof(CacheItem),pCacheMemorySegment);
        if( *ppCache == NULL ){
          LeaveCriticalSection(&csSymbolTable);
          isapi_report(stderr,"",0,COMMAND_ERROR_MEMORY_LOW,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
          return HSE_STATUS_SUCCESS;
          }
      (*ppCache)->pProgram = NULL;
      InitializeCriticalSection(&((*ppCache)->csCompile));
      EnterCriticalSection(&((*ppCache)->csCompile));
      LeaveCriticalSection(&csSymbolTable);
      (*ppCache)->boolValid = 0; /* no valid code is loaded up to now */
      pProgram = (*ppCache)->pProgram = scriba_new(malloc,free);
      if( pProgram == NULL ){
        LeaveCriticalSection(&((*ppCache)->csCompile));
        LeaveCriticalSection(&csSymbolTable);
        isapi_report(stderr,"",0,COMMAND_ERROR_MEMORY_LOW,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
        return HSE_STATUS_SUCCESS;
        }
      scriba_SetFileName(pProgram,szInputFile);
      if( scriba_UseCacheFile(pProgram) == SCRIBA_ERROR_SUCCESS )binarycode = 1;
      if( binarycode || scriba_IsFileBinaryFormat(pProgram) ){
        scriba_LoadBinaryProgram(pProgram);
        }else{
        if( iError=scriba_RunExternalPreprocessor(pProgram,NULL) ){
          LeaveCriticalSection(&((*ppCache)->csCompile));
          LeaveCriticalSection(&csSymbolTable);
          isapi_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
          return HSE_STATUS_SUCCESS;
          }
        if( scriba_LoadSourceProgram(pProgram) )return HSE_STATUS_SUCCESS;
        scriba_SaveCacheFile(pProgram);
        }
      (*ppCache)->boolValid = 1;
      LeaveCriticalSection(&((*ppCache)->csCompile));
      }else{
      LeaveCriticalSection(&csSymbolTable);
      }

    /* this is a simple way to wait for the first occurence of the code to
       load first then we can execute simultaneous */
    EnterCriticalSection(&((*ppCache)->csCompile));
    LeaveCriticalSection(&((*ppCache)->csCompile));

    /* if the code could not be loaded due to syntax error we do not try again */
    if( ! (*ppCache)->boolValid ){
      isapi_report(stderr,"",0,COMMAND_ERROR_INVALID_CODE,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
      return HSE_STATUS_SUCCESS;
      }

    pProgram = scriba_new(malloc,free);
    if( pProgram == NULL ){
      isapi_report(stderr,"",0,COMMAND_ERROR_MEMORY_LOW,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
      return HSE_STATUS_SUCCESS;
      }
    scriba_InheritConfiguration(pProgram,pProgramConfig);
    scriba_InheritBinaryProgram(pProgram,(*ppCache)->pProgram);
    /* here we are ready to execute the code it is loaded into memory */

    }else{/* if we do not use memory cache */

    pProgram = scriba_new(malloc,free);
    if( pProgram == NULL ){
      isapi_report(stderr,"",0,COMMAND_ERROR_MEMORY_LOW,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
      return HSE_STATUS_SUCCESS;
      }
    scriba_InheritConfiguration(pProgram,pProgramConfig);
    scriba_SetFileName(pProgram,szInputFile);
    if( scriba_UseCacheFile(pProgram) == SCRIBA_ERROR_SUCCESS )binarycode = 1;
    if( binarycode || scriba_IsFileBinaryFormat(pProgram) ){
      scriba_LoadBinaryProgram(pProgram);
      }else{
      if( iError=scriba_RunExternalPreprocessor(pProgram,NULL) ){
        isapi_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
        return HSE_STATUS_SUCCESS;
        }
      if( scriba_LoadSourceProgram(pProgram) )return HSE_STATUS_SUCCESS;
      scriba_SaveCacheFile(pProgram);
      }
  }

  scriba_Run(pProgram,NULL);
  scriba_destroy(pProgram);

  sprintf(lpECB->lpszLogData,"executed %s.",szInputFile);
  return HSE_STATUS_SUCCESS;
  }

/*POD
=section TerminateExtension
=H Terminate the extension

This function is called by the IIS before the extension is unloaded.

/*FUNCTION*/
BOOL WINAPI TerminateExtension(DWORD dwFlags
  ){
/*noverbatim
CUT*/
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
      scriba_destroy(pProgramConfig);
      pProgramConfig = NULL;
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
      scriba_destroy(pProgramConfig);
      pProgramConfig = NULL;
      return TRUE;
    default:;
    }
  return 0;
  }

/*POD
=section GetExtensionVersion
=H Version negotiation and startup function

/*FUNCTION*/
BOOL WINAPI  GetExtensionVersion(HSE_VERSION_INFO *pVer
  ){
/*noverbatim
CUT*/
  char *szErrorMessageFile,*s;
  char timebuf[9],datebuf[9];

  /* create the pseudo program that will hold the configuration information */
  pProgramConfig = scriba_new(malloc,free);

  /* note that there is no forced config file name that
     could come from a command line that we do not have */
  scriba_LoadConfiguration(pProgramConfig,NULL);

  /* Get some parameters from the config file. */
  szCache = cft_GetString(pProgramConfig->pCONF,"cache");
  szReportFile = cft_GetString(pProgramConfig->pCONF,"isapi.report");

  /* this lock is used to prevent two threads writing the report file at once */
  InitializeCriticalSection(&csReport);

  /* this lock is used to prevent symultaneous access to the symbol table */
  InitializeCriticalSection(&csSymbolTable);

  /* get the error message text that is sent to the user screen when an error happens */
  szErrorMessageFile = cft_GetString(pProgramConfig->pCONF,"isapi.errormessage");

  /* write the start message into the report file */
  if( szReportFile != NULL ){
    EnterCriticalSection(&csReport);
    ReportFile = fopen(szReportFile,"a");
    if( ReportFile != NULL ){
      _strtime( timebuf );
      _strdate( datebuf );
      fprintf(ReportFile,"%s %s: ScriptBasic ISAPI variation was loaded.\n",datebuf,timebuf);
      fclose(ReportFile);
      }
    LeaveCriticalSection(&csReport);
    }

  /* This variation caches programs in memory, and we should have
     a symbol table that tells us where the collected code is.
  */

  s = cft_GetString(pProgramConfig->pCONF,"isapi.memcache");
  if( s && !strcmp(s,"yes") ){
    pCacheMemorySegment = alloc_InitSegment(malloc,free);
    if( pCacheMemorySegment == NULL )return FALSE;
    ProgramCache = sym_NewSymbolTable(alloc_Alloc,pCacheMemorySegment);
    if( ProgramCache == NULL )return FALSE;
    DoMemoryCache = 1;
    }else{
    DoMemoryCache = 0;
    pCacheMemorySegment = NULL;
    ProgramCache = NULL;
    }

  pVer->dwExtensionVersion = HSE_VERSION;
  return TRUE;
  }
