/* 

FILE:   libscriba.c
HEADER: libscriba.h

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

#if BCC32
char *_pgmptr;
#endif


static int libscriba_LoadBinaryProgram(pSbProgram pProgram
  ){
/*noverbatim
Before calling this function the function R<scriba_SetFileName()> should have been called specifying the
file name.
CUT*/
  pBuildObject pBuild;

  extern unsigned long ulGlobalVariables;
  extern unsigned long ulNodeCounter;
  extern unsigned long ulStartNode;
  extern unsigned long ulStringTableSize;
  extern unsigned char szCommandArray[];
  extern char szStringTable[];

  pProgram->pBUILD = alloc_Alloc( sizeof(BuildObject) , pProgram->pMEM);
  if( pProgram->pBUILD == NULL )return 1;

  pProgram->pBUILD->memory_allocating_function = pProgram->maf;
  pProgram->pBUILD->memory_releasing_function  = pProgram->mrf;
  pProgram->pBUILD->iErrorCounter = 0;
  pProgram->pBUILD->reportptr = pProgram->pReportPointer;
  pProgram->pBUILD->report   = pProgram->fpReportFunction;
  pProgram->pBUILD->fErrorFlags = pProgram->fErrorFlags;
  pBuild = pProgram->pBUILD;

  pBuild->pMemorySegment = alloc_InitSegment(pBuild->memory_allocating_function,
                                             pBuild->memory_releasing_function);
  if( pBuild->pMemorySegment == NULL ){
    return BU_ERROR_MEMORY_LOW;
    }

  pBuild->cGlobalVariables = ulGlobalVariables;
  pBuild->NodeCounter      = ulNodeCounter;
  pBuild->StartNode        = ulStartNode;
  pBuild->CommandArray     = (struct _cNODE *)szCommandArray;
  pBuild->cbStringTable    = ulStringTableSize;
  pBuild->StringTable      = szStringTable;
  pBuild->cbFTable         = 0;
  pBuild->FTable           = NULL;
  pBuild->cbVTable         = 0;
  pBuild->VTable           = NULL;
  return pProgram->pBUILD->iErrorCounter;
  }


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
  pSbProgram pProgram;
  unsigned long fErrorFlags;
#define FULL_PATH_BUFFER_LENGTH 1024
  char CmdLinBuffer[FULL_PATH_BUFFER_LENGTH];
  extern int GlobalDebugDisplayFlag;
  int i;
  
  CmdLinBuffer[0] = (char)0;
  for( i=1 ; i < argc ; i++ ){
    strcat(CmdLinBuffer,argv[i]);
    if( i < argc-1 )strcat(CmdLinBuffer," ");
    }

/*pSbData p,psb;
SbData RetVale;*/
#ifndef WIN32
  _environ = env;
#endif

#if BCC32
  _pgmptr = argv[0];
#endif

#ifdef _DEBUG
#define malloc testa_Alloc
#define free testa_Free
  testa_InitSegment();
#endif
  /* default values for command line options */
#define pszForcedConfigurationFileName NULL
  GlobalDebugDisplayFlag = 0;

  pProgram = scriba_new(malloc,free);
  if( pProgram == NULL ){
    iError = COMMAND_ERROR_MEMORY_LOW;
    ERREXIT;
    }

  scriba_LoadConfiguration(pProgram,pszForcedConfigurationFileName);

  scriba_SetFileName(pProgram,argv[0]);

  if( (iError = libscriba_LoadBinaryProgram(pProgram)) != 0 ){
    ERREXIT;
    }
  if( iError=scriba_Run(pProgram,CmdLinBuffer) ){
    report_report(stderr,"",0,iError,REPORT_ERROR,&iErrorCounter,NULL,&fErrorFlags);
    ERREXIT;
    }

  scriba_destroy(pProgram);
  exit(iError);
  }

