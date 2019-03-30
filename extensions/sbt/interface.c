/*  SBT (Script BASIC Tutorial) - Extension Module
UXLIBS: -lscriba -lpthread -lm
BAS: sbt.bas
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "../../basext.h"
#include "../../scriba.h"
#include "cbasic.h"


/****************************
 Extension Module Functions
****************************/

besVERSION_NEGOTIATE
  RETURN_FUNCTION((int)INTERFACE_VERSION);
besEND

besSUB_START
  DIM AS long PTR p;
  besMODULEPOINTER = besALLOC(sizeof(long));
  IF (besMODULEPOINTER EQ NULL) THEN_DO RETURN_FUNCTION(0);
  p = (long PTR)besMODULEPOINTER;
  RETURN_FUNCTION(0);
besEND

besSUB_FINISH
  DIM AS long PTR p;
  p = (long PTR)besMODULEPOINTER;
  IF (p EQ NULL) THEN_DO RETURN_FUNCTION(0);
  RETURN_FUNCTION(0);
besEND


/**********************
 Script BASIC Instance
**********************/

/******************
 Support Routines
******************/

struct _RunServiceProgram {
  char *pszProgramFileName;
  char *pszCmdLineArgs;
  char *pszConfigFileName;
  pSbProgram pTProgram;
  int iRestart;
  };

static void ExecuteProgramThread(void *p){
  pSbProgram pProgram;
  char szInputFile[1024];
  int iErrorCode;
  struct _RunServiceProgram *pRSP;
  pRSP = p;
  strcpy(szInputFile,pRSP->pszProgramFileName);
  pProgram = scriba_new(malloc,free);
  pRSP->pTProgram = pProgram;
  if( pProgram == NULL )return;
  scriba_SetFileName(pProgram,szInputFile);
  if (pRSP->pszConfigFileName != NULL){
  	strcpy(szInputFile,pRSP->pszConfigFileName);
  	scriba_LoadConfiguration(pProgram, pRSP->pszConfigFileName);
  }else{
  	scriba_SetProcessSbObject(pProgram,pProgram);
  }
  scriba_LoadSourceProgram(pProgram);
  if (pRSP->pszCmdLineArgs != NULL){
  	strcpy(szInputFile,pRSP->pszCmdLineArgs);
    iErrorCode = scriba_Run(pProgram,pRSP->pszCmdLineArgs);
  }else{
    iErrorCode = scriba_Run(pProgram,NULL);
  }
//  scriba_destroy(pProgram);
  return;
}

besFUNCTION(SB_New)
  DIM AS pSbProgram sbobj;
  sbobj = scriba_new(malloc,free);
  besRETURN_LONG(sbobj);
besEND

besFUNCTION(SB_Configure)
  DIM AS unsigned long sbobj;
  DIM AS char PTR cfgfilename;
  DIM AS int rtnval = -1;
  besARGUMENTS("iz")
    AT sbobj, AT cfgfilename
  besARGEND
  rtnval = scriba_LoadConfiguration(sbobj, cfgfilename);
  besRETURN_LONG(rtnval);
besEND

besFUNCTION(SB_Load)
  DIM AS unsigned long sbobj;
  DIM AS char PTR sbfilename;
  DIM AS int rtnval = -1;
  besARGUMENTS("iz")
    AT sbobj, AT sbfilename
  besARGEND
  rtnval = scriba_SetFileName(sbobj, sbfilename);
  scriba_LoadSourceProgram(sbobj);
  besRETURN_LONG(rtnval);
besEND

besFUNCTION(SB_LoadStr)
  DIM AS unsigned long sbobj;
  DIM AS char PTR sbpgm;
  DIM AS int rtnval = -1;
  besARGUMENTS("iz")
    AT sbobj, AT sbpgm
  besARGEND
  scriba_SetFileName(sbobj, "fake");
  rtnval = scriba_LoadProgramString(sbobj, sbpgm, strlen(sbpgm));
  besRETURN_LONG(rtnval);
besEND

besFUNCTION(SB_Run)
  DIM AS unsigned long sbobj;
  DIM AS int rtnval;
  DIM AS char PTR sbcmdline;
  besARGUMENTS("iz")
    AT sbobj, AT sbcmdline
  besARGEND
  IF (besARGNR < 2) THEN_DO sbcmdline = "";
  rtnval = scriba_Run(sbobj, sbcmdline);
  besRETURN_LONG(rtnval);
besEND

besFUNCTION(SB_NoRun)
  DIM AS unsigned long sbobj;
  DIM AS int rtnval;
  besARGUMENTS("i")
    AT sbobj
  besARGEND
  rtnval = scriba_NoRun(sbobj);
  besRETURN_LONG(rtnval);
besEND

besFUNCTION(SB_ThreadStart)
  DIM AS struct _RunServiceProgram PTR pRSP;
  DIM AS THREADHANDLE T;
  DIM AS char PTR pszProgramFileName;
  DIM AS char PTR pszCmdLineArgs;
  DIM AS char PTR pszConfigFileName;
  DIM AS unsigned long rtnval;
  besARGUMENTS("z[z][z]")
    AT pszProgramFileName, AT pszCmdLineArgs, AT pszConfigFileName
  besARGEND
  pRSP = (struct _RunServiceProgram PTR)malloc( sizeof(struct _RunServiceProgram) );
  pRSP->pszProgramFileName = (char PTR)malloc(strlen(pszProgramFileName) + 1);
  strcpy(pRSP->pszProgramFileName,pszProgramFileName);
  IF (pszCmdLineArgs NE NULL) THEN
    pRSP->pszCmdLineArgs = (char PTR)malloc(strlen(pszCmdLineArgs) + 1);
    strcpy(pRSP->pszCmdLineArgs,pszCmdLineArgs);
  ELSE
  	pRSP->pszCmdLineArgs = NULL;
  END_IF
  IF (pszConfigFileName NE NULL) THEN
    pRSP->pszConfigFileName = (char PTR)malloc(strlen(pszConfigFileName) + 1);
    strcpy(pRSP->pszConfigFileName,pszConfigFileName);
  ELSE
  	pRSP->pszConfigFileName = NULL;
  END_IF
  pRSP->iRestart = 0;
  thread_CreateThread(AT T,ExecuteProgramThread,pRSP);
  usleep(500);
  rtnval = pRSP->pTProgram;
  besRETURN_LONG(rtnval);
besEND

besFUNCTION(SB_ThreadEnd)
  thread_ExitThread();
  besRETURNVALUE = NULL;
besEND

besFUNCTION(SB_Destroy)
  DIM AS unsigned long sbobj;
  besARGUMENTS("i")
    AT sbobj
  besARGEND
  scriba_destroy(sbobj);
  RETURN_FUNCTION(0);
besEND

besFUNCTION(SB_CallSub)
  DIM AS unsigned long sbobj;
  DIM AS int funcsernum;
  DIM AS char PTR funcname;
  besARGUMENTS("iz")
    AT sbobj, AT funcname
  besARGEND
  funcsernum = scriba_LookupFunctionByName(sbobj, funcname);
  besRETURN_LONG(scriba_Call(sbobj, funcsernum));
besEND

besFUNCTION(SB_CallSubArgs)
  DIM AS VARIABLE Argument;
  DIM AS SbData ArgData[8];
  DIM AS SbData FunctionResult;
  DIM AS unsigned long sbobj;
  DIM AS char PTR funcname;
  DIM AS int i, sbtype, fnsn;

  Argument = besARGUMENT(1);
  besDEREFERENCE(Argument);
  sbobj = LONGVALUE(Argument);

  Argument = besARGUMENT(2);
  besDEREFERENCE(Argument);
  funcname = STRINGVALUE(Argument);

  DEF_FOR (i = 3 TO i <= besARGNR STEP INCR i)
  BEGIN_FOR
    Argument = besARGUMENT(i);
    besDEREFERENCE(Argument);
    SELECT_CASE (sbtype = TYPE(Argument))
    BEGIN_SELECT
      CASE VTYPE_LONG:
        ArgData[i-3] = PTR scriba_NewSbLong(sbobj, LONGVALUE(Argument));
        END_CASE
      CASE VTYPE_DOUBLE:
        ArgData[i-3] = PTR scriba_NewSbDouble(sbobj, DOUBLEVALUE(Argument));
        END_CASE
      CASE VTYPE_STRING:
        ArgData[i-3] = PTR scriba_NewSbString(sbobj, STRINGVALUE(Argument));
        END_CASE
      CASE_ELSE
      	ArgData[i-3] = PTR scriba_NewSbUndef(sbobj);
      	END_CASE
    END_SELECT
  NEXT

  fnsn = scriba_LookupFunctionByName(sbobj, funcname);
  scriba_CallArgEx(sbobj, fnsn, AT FunctionResult, besARGNR - 2, AT ArgData);

  SELECT_CASE (FunctionResult.type)
  BEGIN_SELECT
    CASE SBT_LONG:
      besRETURN_LONG(FunctionResult.v.l);
      END_CASE
    CASE SBT_DOUBLE:
      besRETURN_DOUBLE(FunctionResult.v.d);
      END_CASE
    CASE SBT_STRING:
      besRETURN_STRING(FunctionResult.v.s);
      END_CASE
    CASE SBT_UNDEF:
      besRETURNVALUE = NULL;
      END_CASE
  END_SELECT
besEND

besFUNCTION(SB_GetVar)
  DIM AS pSbData varobj;
  DIM AS unsigned long sbobj;
  DIM AS int vsn;
  DIM AS char PTR varname;
  besARGUMENTS("iz")
    AT sbobj, AT varname
  besARGEND
  vsn = scriba_LookupVariableByName(sbobj, varname);
  scriba_GetVariable(sbobj, vsn, AT varobj);
  SELECT_CASE (scriba_GetVariableType(sbobj, vsn))
  BEGIN_SELECT
    CASE SBT_LONG   :
      besRETURN_LONG(varobj[0].v.l);
      END_CASE
    CASE SBT_DOUBLE :
      besRETURN_DOUBLE(varobj[0].v.d);
      END_CASE
    CASE SBT_STRING :
      besRETURN_STRING(varobj[0].v.s);
      END_CASE
    CASE SBT_UNDEF  :
      besRETURNVALUE = NULL;
      END_CASE
  END_SELECT
besEND

besFUNCTION(SB_SetUndef)
  DIM AS pSbData varobj;
  DIM AS unsigned long sbobj;
  DIM AS int vsn;
  DIM AS char PTR varname;
  besARGUMENTS("iz")
    AT sbobj, AT varname
  besARGEND
  vsn = scriba_LookupVariableByName(sbobj, varname);
  besRETURN_LONG(scriba_SetVariable(sbobj, vsn, SBT_UNDEF, NULL, 0, "", 0));
besEND

besFUNCTION(SB_SetInt)
  DIM AS VARIABLE Argument;
  DIM AS pSbData varobj;
  DIM AS unsigned long sbobj;
  DIM AS int vsn, usrval, i;
  DIM AS char PTR varname;
  IF (besARGNR < 3) THEN_DO RETURN_FUNCTION(EX_ERROR_TOO_FEW_ARGUMENTS);
  DEF_FOR (i = 1 TO i <= 3 STEP INCR i)
  BEGIN_FOR
    Argument = besARGUMENT(i);
    besDEREFERENCE(Argument);
    IF (i EQ 1) THEN_DO sbobj = LONGVALUE(Argument);
    IF (i EQ 2) THEN_DO varname = STRINGVALUE(Argument);
    IF (i EQ 3) THEN_DO usrval = LONGVALUE(Argument);
  NEXT
  vsn = scriba_LookupVariableByName(sbobj, varname);
  besRETURN_LONG(scriba_SetVariable(sbobj, vsn, SBT_LONG, usrval, 0, "", 0));
besEND

besFUNCTION(SB_SetDbl)
  DIM AS VARIABLE Argument;
  DIM AS pSbData varobj;
  DIM AS unsigned long sbobj;
  DIM AS int vsn, i;
  DIM AS char PTR varname;
  DIM AS double usrval;
  IF (besARGNR < 3) THEN_DO RETURN_FUNCTION(EX_ERROR_TOO_FEW_ARGUMENTS);
  DEF_FOR (i = 1 TO i <= 3 STEP INCR i)
  BEGIN_FOR
    Argument = besARGUMENT(i);
    besDEREFERENCE(Argument);
    IF (i EQ 1) THEN_DO sbobj = LONGVALUE(Argument);
    IF (i EQ 2) THEN_DO varname = STRINGVALUE(Argument);
    IF (i EQ 3) THEN_DO usrval = DOUBLEVALUE(Argument);
  NEXT
  vsn = scriba_LookupVariableByName(sbobj, varname);
  besRETURN_LONG(scriba_SetVariable(sbobj, vsn,  SBT_DOUBLE, 0, usrval, "", 0));
besEND

besFUNCTION(SB_SetStr)
  DIM AS VARIABLE Argument;
  DIM AS pSbData varobj;
  DIM AS unsigned long sbobj;
  DIM AS int vsn, i;
  DIM AS char PTR varname;
  DIM AS char PTR usrval;
  IF (besARGNR < 3) THEN_DO RETURN_FUNCTION(EX_ERROR_TOO_FEW_ARGUMENTS);
  DEF_FOR (i = 1 TO i <= 3 STEP INCR i)
  BEGIN_FOR
    Argument = besARGUMENT(i);
    besDEREFERENCE(Argument);
    IF (i EQ 1) THEN_DO sbobj = LONGVALUE(Argument);
    IF (i EQ 2) THEN_DO varname = STRINGVALUE(Argument);
    IF (i EQ 3) THEN_DO usrval = STRINGVALUE(Argument);
  NEXT
  vsn = scriba_LookupVariableByName(sbobj, varname);
  besRETURN_LONG(scriba_SetVariable(sbobj, vsn,  SBT_STRING, 0, 0, usrval, strlen(usrval)));
besEND

besFUNCTION(SB_ResetVars)
  DIM AS unsigned long sbobj;
  besARGUMENTS("i")
    AT sbobj
  besARGEND
  scriba_ResetVariables(sbobj);
  besRETURNVALUE = NULL;
besEND

besFUNCTION(SB_msSleep)
  //DIM AS int msval, t;
  DIM AS long t;
  besARGUMENTS("i")
    AT t
  besARGEND
  usleep(t);
  besRETURNVALUE = NULL;
besEND
