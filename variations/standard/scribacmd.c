/*

FILE:   scribacmd.c
HEADER: scribacmd.h

Common MIT License - Jan 31, 2018

ScriptBasic Copyright (c) 2018 Peter Verhas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

TO_HEADER:

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../getopt.h"
#include "../../scriba.h"
#include "../../basext.h"
#include "../../confpile.h"

#if BCC32 || CYGWIN
char *_pgmptr;
#endif


int GetC(void *f){ return getc((FILE *)f); }

#ifdef _DEBUG
#define ERREXIT do{getchar();scriba_destroy(pProgram);exit(iError);}while(0)
#else
#define ERREXIT exit(iError)
#endif

#ifdef WIN32
main(int argc, char *argv[]){
#else
  char **_environ;
main(int argc, char *argv[], char *env[]){
#endif
  int iError;
  int iErrorCounter;
  int OptionIndex;
  tConfigTree MyCONF;
  pSbProgram pProgram;
  char *pszForcedConfigurationFileName;
  unsigned long fErrorFlags;
  char *szInputFile,
       *szOutputFile;
  char *optarg,opt;
  /* the maximal number of preprocessors that are applied in chain */
#define MAXPREPROC 100
  char *pszEPreproc[MAXPREPROC],*pszPreprocessedFileName;
  char *pszIPreproc[MAXPREPROC];
  int iEPreprocIndex,iIPreprocIndex;
  int giveusage,binarycode,nocache,iscgi,isCoutput,isEoutput;
  int execute,ConfCompile,ConfDump;
#define FULL_PATH_BUFFER_LENGTH 256
  char CmdLinBuffer[FULL_PATH_BUFFER_LENGTH];
  extern int GlobalDebugDisplayFlag;
  long lOffset,lEOFfset;
  char *realArgv0;

#ifdef __MACOS__
  argc = ccommand(&argv);
#endif

/*pSbData p,psb;
SbData RetVale;*/
#ifndef WIN32
  _environ = env;
#endif

#if BCC32 || CYGWIN
  _pgmptr = argv[0];
#endif

#ifdef _DEBUG
#define malloc testa_Alloc
#define free testa_Free
  testa_InitSegment();
#endif
  /* default values for command line options */
  szInputFile = NULL;
  szOutputFile = NULL;
  ConfCompile = 0; /* the default action is to run BASIC program and not configuration file compilation */
  ConfDump    = 0; /* the default action is to run BASIC program and not configuration file dump */
  iEPreprocIndex = 0; /* no external preprocessor by default */
  iIPreprocIndex = 0; /* no internal preprocessor by default */
  pszPreprocessedFileName = NULL;
  *pszEPreproc = NULL;
  *pszIPreproc = NULL;
  giveusage  = 0; /* assume the command line is correct, we need not display usage and stop */
  binarycode = 0; /* input is not binary by default */
  execute    = 0; /* do not execute by default after binary format save */
  nocache   = 0; /* we use cached code if it exists */
  OptionIndex = 0;
  iscgi = 0; /* by default this is not a cgi script, not HTTP/1.0 ... when error message is sent */
  isCoutput = 0;
  isEoutput = 0;
  pszForcedConfigurationFileName = NULL;
  GlobalDebugDisplayFlag = 0;

#ifdef WIN32
  realArgv0 = _pgmptr;
#else
  realArgv0 = argv[0];
#endif

  /* if this exe contains the code itself then jump over it */
  if( build_GetExeCodeOffset(realArgv0,&lOffset,&lEOFfset) ){
    OptionIndex = 1;
    CmdLinBuffer[0] = (char)0;
    while( OptionIndex < argc ){
      strcat(CmdLinBuffer,argv[OptionIndex++]);
      if( OptionIndex < argc )
        strcat(CmdLinBuffer," ");
        }
    goto CmdLineFinished;
    }
#define W(X) fprintf(stderr,"%s\n",X);
  while( (opt = getoptt(argc, argv, "Dkdf:p:i:CEcnvebo:",&optarg,&OptionIndex)) != ':'){
    switch( opt ){
      case 'k':
        if( ConfCompile ){
          giveusage = 1;
          W("Option -k was specified more than once.")
          }
        if( ConfDump ){
          giveusage = 1;
          W("Option -k can not be used together with -D")
          }
        ConfCompile = 1;
        break;
      case 'D':
        if( ConfCompile ){
          giveusage = 1;
          W("Option -k can not be used together with -D")
          }
        if( ConfDump ){
          giveusage = 1;
          W("Option -D was specified more than once.")
          }
        ConfDump = 1;
        break;
      case 'd' :
        if( GlobalDebugDisplayFlag ){
          giveusage = 1;
          W("Option -d was specified more than once.")
          }
        GlobalDebugDisplayFlag = 1;
        break;
      case 'p' :
        if( iEPreprocIndex >= MAXPREPROC-1 ){
          fprintf(stderr,"The maximum number of external preprocessors allowed on the command line is %d\nIt is exceeded.\n",MAXPREPROC);
          giveusage = 1;
          }else{
          pszEPreproc[iEPreprocIndex ++ ] = optarg;
          pszEPreproc[iEPreprocIndex] = NULL;
          }
         break;
      case 'i' :
        if( iIPreprocIndex >= MAXPREPROC-1 ){
          fprintf(stderr,"The maximum number of internal preprocessors allowed on the command line is %d\nIt is exceeded.\n",MAXPREPROC);
          giveusage = 1;
          }else{
          pszIPreproc[iIPreprocIndex ++ ] = optarg;
          pszIPreproc[iIPreprocIndex] = NULL;
          }
         break;
      case 'C' :
        if( isCoutput ){
          giveusage = 1;
          W("Option -C was specified more than once.")
          }
        isCoutput = 1;
        break;
      case 'E' :
        if( isEoutput ){
          giveusage = 1;
          W("Option -E was specified more than once.")
          }
        isEoutput = 1;
        break;
      case 'c' :
        if( iscgi ){
          giveusage = 1;
          W("Option -c was specified more than once.")
          }
        iscgi = 1;
        break;
      case 'n' :
        if( nocache ){
          giveusage = 1;
          W("Option -n was specified more than once.")
          }
        nocache = 1;
        break;
      case 'e' :
        if( execute ){
          giveusage = 1;
          W("Option -e was specified more than once.")
          }
        execute = 1;
        break;
      case 'f' :
        if( execute ){
          giveusage = 1;
          W("Option -f was specified more than once.")
          }
        pszForcedConfigurationFileName = optarg;
        break;
      case 'o' :
        if( szOutputFile || binarycode ){
          W("Using the option -o is invalid when the program is already binary.")
          giveusage = 1;
          }
        szOutputFile = optarg;
        break;
      case 'b':
        if( szOutputFile || binarycode ){
          W("Binary input file can not be used to produce output file.");
          giveusage = 1;
          }
        binarycode =1;
        break;
      case 'v':
#define S fprintf(stderr,
#define E );
                   S "ScriptBasic v%ld.%ld\n",VERSION_HIGH,VERSION_LOW E
                   S "Variation >>%s<< build %ld\n",VARIATION,SCRIPTBASIC_BUILD E
                   S "Magic value %lu\n",build_MagicCode(NULL) E
                   S "Node size is %d\n", sizeof(cNODE) E
                   S "Extension interface version is %d\n",INTERFACE_VERSION E
                   S "Compilation: %s %s\n", __DATE__,__TIME__ E
#ifdef WIN32
                   S "Executable: %s\n", _pgmptr E
#endif
        exit(0);
      case '!' :
        W("Invalid option.");
        giveusage = 1;
        break;
      case '?':
        if( szInputFile ){
          W("Only one input file can be specified. YOu should not see this error message.");
          giveusage = 1;
          }
        szInputFile = optarg;
        CmdLinBuffer[0] = (char)0;
        while( OptionIndex < argc ){
          strcat(CmdLinBuffer,argv[OptionIndex++]);
          if( OptionIndex < argc )
            strcat(CmdLinBuffer," ");
          }
        goto CmdLineFinished;
      }
    }

CmdLineFinished:
  if( execute && binarycode ){
    W("The option -e and binary input file can not be used together.");
    giveusage=1;
    }
  if( isCoutput && !szOutputFile ){
    W("To generate C file an output file has to be specified.");
    giveusage=1;
    }
  if( isEoutput && !szOutputFile ){
    W("To generate executable file an output file has to be specified.");
    giveusage=1;
    }
  /* This is to be a bit more safe with include files changed. Be sure to compile the final version of the BASIC program. */
  if( isEoutput || isCoutput )nocache = 1;
  if( iIPreprocIndex )nocache = 1;
/* NOTE: that external preprocessor effects can be cached!
  if( iEPreprocIndex )nocache = 1;
   On the other hand internal preprocessor provided on the
   command-line (and not in the source 'use' commands)
   is most probably a debugger or profiler, thus no caching
   should be done, because if we use the cache the program
   runs without having the preprocessor in effect.
*/
  if( (!lOffset) && (!ConfDump) && (!ConfCompile) && szInputFile == NULL || giveusage ){
#define U(x) fprintf(stderr,"%s\n",(x));
    U("Usage: basic [options] program.bas")
    U("")
    U("options: -o file_name")
    U("            specify output file, save binary format to file but don't execute")
    U("         -b file_name")
    U("            load binary format from file and execute")
    U("         -n")
    U("            do not use cache (no save, no load)")
    U("         -e")
    U("            execute after binary format was saved")
    U("         -v")
    U("            print version info and stop")
    U("         -c")
    U("            inform scriba that this is a CGI script.")
    U("         -C");
    U("            save C program output.");
    U("         -E");
    U("            save executable output. (may not work under some OS)");
    U("         -p preprocessor");
    U("            specify external preprocessor.");
    U("         -i preprocessor");
    U("            specify internal preprocessor.");
    U("         -f configurationfile");
    U("            specify configuration file");
    U("         -d");
    U("            debug module error (UNIX only)");
    U("         -k text_config_file");
    U("            compile the configuration file to binary");
    U("         -D");
    U("            dump the configuration file in text format");
    exit(1);
    }
  pProgram = scriba_new(malloc,free);
  if( pProgram == NULL ){
    iError = COMMAND_ERROR_MEMORY_LOW;
    ERREXIT;
    }
  /* if the user has specified the option -D then the input file is the compiled configuration file.
      */
  if( ConfDump ){
    /* the output file has to be specified, because that is where we dump the tex format config file */
    if( szOutputFile == NULL )
      szOutputFile = "STDOUT";

    pProgram->pCONF = alloc_Alloc(sizeof(tConfigTree),pProgram->pMEM);
    if( pProgram->pCONF == NULL ){
      iError = COMMAND_ERROR_MEMORY_LOW;
      report_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
      exit(1);
      }
    iError = cft_init(pProgram->pCONF,NULL,NULL,NULL);
    if( iError ){
      report_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
      exit(1);
      }
    if( pszForcedConfigurationFileName == NULL ){
      iError = scriba_GetConfigFileName(pProgram,&pszForcedConfigurationFileName);
      if( iError ){
        report_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
        exit(1);
        }
      }
    iError = cft_ReadConfig(pProgram->pCONF,pszForcedConfigurationFileName);
    if( iError != 0 ){
      fprintf(stderr,"Configuration file %s can not be processed.\n",pszForcedConfigurationFileName);
      exit(1);
      }
    iError = cft_DumpConfig(pProgram->pCONF,szOutputFile);
    if( iError != 0 ){
      fprintf(stderr,"Output file %s can not be processed.\n",szOutputFile);
      exit(iError);
      }
    exit(0);
    }

  /* If the user has specified the option -k then the input file is the configuration file.
     Now we compile the configuration file and do not run any program. This is more convenient
     then the older version using the external program cftc because cftc required two arguments:

     configuration file in text format
     compiled output configuration file name

     scriba -k on the other hand requires only the text configuration file name and saves
     the configuration file into the file name, where it will search for the configuration file
     when it runs a BASIC program.   */
  if( ConfCompile ){
    if( NULL == szInputFile ){
      fprintf(stderr,"The option '-k' needs argument (the name of the config text file)\n");
      exit(1);
      }
    pProgram->pCONF = alloc_Alloc(sizeof(tConfigTree),pProgram->pMEM);
    if( pProgram->pCONF == NULL ){
      iError = COMMAND_ERROR_MEMORY_LOW;
      report_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
      ERREXIT;
      }
    iError = cft_init(pProgram->pCONF,NULL,NULL,NULL);
    if( iError ){
      report_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
      ERREXIT;
      }
    if( pszForcedConfigurationFileName == NULL ){
      iError = scriba_GetConfigFileName(pProgram,&pszForcedConfigurationFileName);
      if( iError ){
        report_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
        ERREXIT;
        }
      }
    iError = cft_ReadTextConfig(pProgram->pCONF,szInputFile);
    switch( iError ){
      case CFT_ERROR_FILE:
        fprintf(stderr,"The file %s can not be read.\n",szInputFile);
        exit(1);
      case CFT_ERROR_EMPTY:
        fprintf(stderr,"The file %s contains no configuration information.\n",szInputFile);
        exit(1);
      case CFT_ERROR_SYNTAX:
        fprintf(stderr,"The file %s has syntax error in it.\n",szInputFile);
        exit(1);
      case CFT_ERROR_MEMORY:
        fprintf(stderr,"Memory exhausted while processing the file %s\n",szInputFile);
        exit(1);
      }
    iError = cft_WriteConfig(pProgram->pCONF,pszForcedConfigurationFileName);
    switch( iError ){
      case CFT_ERROR_FILE:
        fprintf(stderr,"The file %s can not be written\n",pszForcedConfigurationFileName);
        exit(1);
      case CFT_ERROR_MEMORY:
        fprintf(stderr,"Memory exhausted while writing the file %s\n",pszForcedConfigurationFileName);
        exit(1);
      }
    fprintf(stderr,"The configuration file '%s' was created.\n",pszForcedConfigurationFileName);
    exit(0);
    }

  scriba_LoadConfiguration(pProgram,pszForcedConfigurationFileName);

#if _DEBUG
testa_Assert0x80();
#endif
  iError = scriba_LoadInternalPreprocessor(pProgram,pszIPreproc);
#if _DEBUG
testa_Assert0x80();
#endif
  if( iError ){
    report_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
    ERREXIT;
    }

  if( iscgi )scriba_SetCgiFlag(pProgram);
#if _DEBUG
testa_Assert0x80();
#endif
  if( lOffset )
    scriba_SetFileName(pProgram,realArgv0);
  else
    scriba_SetFileName(pProgram,szInputFile);
#if _DEBUG
testa_Assert0x80();
#endif

  if( (!nocache) && scriba_UseCacheFile(pProgram) == SCRIBA_ERROR_SUCCESS )binarycode = 1;
  if( lOffset )binarycode = 1;
  if( binarycode || scriba_IsFileBinaryFormat(pProgram) ){
    if( (iError = scriba_LoadBinaryProgramWithOffset(pProgram,lOffset,lEOFfset)) != 0 ){
      ERREXIT;
      }
    }else{
    if( iError=scriba_RunExternalPreprocessor(pProgram,pszEPreproc) ){
      report_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
      ERREXIT;
      }
    if( scriba_LoadSourceProgram(pProgram) )ERREXIT;
    if( szOutputFile ){
      if( isCoutput )
        scriba_SaveCCode(pProgram,szOutputFile);
      else
      if( isEoutput )
        scriba_SaveECode(pProgram,realArgv0,szOutputFile);
      else
        scriba_SaveCode(pProgram,szOutputFile);
      if( !execute )exit(0);
      }
     if( ! nocache )scriba_SaveCacheFile(pProgram);
    }
/*
  {FILE *fb; fb = fopen("dumpcode.txt","w");
  build_pprint(pProgram->pBUILD,fb);fclose(fb);}
*/
/*#define PRGSTR "print \"hello\\n\"\n\
include \"test.bas\"\
"
  scriba_LoadProgramString(pProgram,PRGSTR,strlen(PRGSTR));
*/
  if( iError=scriba_Run(pProgram,CmdLinBuffer) ){
#if _DEBUG
testa_Assert0x80();
#endif
    if( iError > 0 ){
      char *pszModuleError = pProgram->pEXE ? pProgram->pEXE->pszModuleError : NULL;
      report_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,pszModuleError,&fErrorFlags);
      }else
      iError = -iError;
    ERREXIT;
    }
#if _DEBUG
testa_Assert0x80();
#endif

/*
{
unsigned long i=0;
unsigned long min,max,act;
pSbData pRetVale;
  while( 1 ){
    i++;
    if( i%10000 == 0 ){
      testa_ReportLeak();
#define PRSEG(X)      alloc_GetStat(X,&min,&max,&act);printf("Segment %s is %d\n",#X,act);
      PRSEG(pProgram->pMEM);
      PRSEG(pProgram->pEXE->pMo);
      PRSEG(pProgram->pEXE->pMemorySegment);
      printf("kukk %d\n",i/10000);
      getchar();
      }
    pRetVale = scriba_NewSbData(pProgram);
    scriba_CallArgEx(pProgram,scriba_LookupFunctionByName(pProgram,"main::pred_1"),pRetVale,0,NULL);
    scriba_DestroySbData(pProgram,pRetVale);
    }
}

  printf("testvar type is %d\n",scriba_GetVariableType(pProgram,
  scriba_LookupVariableByName(pProgram,"main::testvar")));
  scriba_GetVariable(pProgram,
                     scriba_LookupVariableByName(pProgram,"main::testvar"),
                     &psb
    );
  printf("testvar from C is %s\n",scriba_GetString(pProgram,*psb));

  scriba_SetVariable(pProgram,scriba_LookupVariableByName(pProgram,"main::testvar"),
                     SBT_ZCHAR,1,2.2,"kukac",4);
  scriba_CallArgEx(pProgram,scriba_LookupFunctionByName(pProgram,"main::thatfunc"),&RetVale,4,p);
*/
  scriba_destroy(pProgram);

#ifdef _DEBUG
  testa_AssertLeak();
  if( ! iscgi ){
    printf("\nPress any key to continue...\n");
    getchar();
    }
#endif
  exit(iError);
  }

