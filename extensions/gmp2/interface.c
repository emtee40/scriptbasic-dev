/*
  FILE   : interface.c
  HEADER : interface.h
  BAS    : gmp2.bas
  AUTHOR : Armando I. Rivera (AIR)

  DATE: 2019-06-15

  CONTENT:
  This is the interface.c file for the ScriptBasic module gmp2
  which provides support for the GMP math library
----------------------------------------------------------------------------

//NTLIBS:
UXLIBS: -lgmp
DWLIBS: -lgmp -macosx_version_min 10.12

*/


/*
  HEADER FILES THAT ARE NEEDED TO COMPILE THIS MODULE
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../basext.h"
#include <gmp.h>


/*
DECLARE HERE THE MODULE OBJECT TYPE. THIS STRUCTURE SHOULD HOLD THE
DATA AVAILABLE FOR EACH INTERPRETER THREAD. USE THIS STRUCTURE TO
STORE GLOBAL VALUES INSTEAD OF USING GLOBAL VARIABLES.
*/
typedef struct _ModuleObject {
  char a; /* You may delete this. It is here to make the initial interface.c compilable. */
  }ModuleObject,*pModuleObject;

mpz_t g_Op1, g_Op2, g_Res;

/*
ALTER THE VERSION NEGOTIATION CODE IF YOU NEED
*/
besVERSION_NEGOTIATE
  return (int)INTERFACE_VERSION;
besEND

/*
ALTER THE ERROR MESSAGE FUNCTION
*/
besSUB_ERRMSG

  switch( iError ){
    case 0x00080000: return "ERROR HAS HAPPENED";
    }
  return "Unknown gmp2 module error.";
besEND

/*
ALTER THE MODULE INITIALIZATION CODE
*/
besSUB_START
  pModuleObject p;

  besMODULEPOINTER = besALLOC(sizeof(ModuleObject));
  if( besMODULEPOINTER == NULL )return 0;

  mpz_init(g_Op1);
  mpz_init(g_Op2);
  mpz_init(g_Res);

besEND

/*
THE MODULE FINISH CODE
*/
besSUB_FINISH
  pModuleObject p;

  /*
    YOU CERTAINLY NEED THIS POINTER TO FREE ALL RESOURCES THAT YOU ALLOCATED
    YOU NEED NOT CALL besFREE TO FREE THE MEMORY ALLOCATED USING besALLOC
    CLOSE ANY FILE THAT REMAINED OPEN, RELEASE DATABASE HANDLES AND ALL
    OTHER RESOURCES INCLUDING MEMORY *NOT* ALLOCATED CALLING besALLOC
  */
  p = (pModuleObject)besMODULEPOINTER;
  if( p == NULL )return 0;
  mpz_clear(g_Op1);
  mpz_clear(g_Op2);
  mpz_clear(g_Res);
  return 0;
besEND


/**
=section init
=H init

Initializes mpz_t object
*/
besFUNCTION(init)
  pModuleObject p;
  mpz_t r;
  char * res;

  p = (pModuleObject)besMODULEPOINTER;


  mpz_init(r);
  res = mpz_get_str(NULL,10,r);
  besSET_RETURN_STRING(res);
  free(res);

  besRETURN_POINTER(r);
besEND


/**
=section init_set
=H init_set

Initializes mpz_t object as a set
*/
besFUNCTION(init_set)
  pModuleObject p;
  char *s, *res;
  int i;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("z")
    &s
  besARGEND

  mpz_init_set_str(g_Res,s,10);
  res = mpz_get_str(NULL,10,g_Res);
  besSET_RETURN_STRING(res);
  free(res);
besEND

/**
=section mul
=H mul

Multiplies mpz_t objects
*/
besFUNCTION(mul)
  pModuleObject p;
  char *s, *t, *res;
  int i;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("zz")
    &s,&t
  besARGEND

  mpz_set_str(g_Op1, s, 10);
  mpz_set_str(g_Op2, t, 10);
  mpz_mul(g_Res, g_Op1, g_Op2);
  res = mpz_get_str(NULL,10,g_Res);
  besSET_RETURN_STRING(res);
  free(res);
besEND


/**
=section mul_si
=H mul_si

Multiplies mpz_t object by an integer value
*/
besFUNCTION(mul_si)
  pModuleObject p;
  char *s,*res;
  long i;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("zi")
    &s,&i
  besARGEND

  mpz_set_str(g_Op1, s, 10);
  mpz_mul_si(g_Res, g_Op1, i);

  res = mpz_get_str(NULL,10,g_Res);
  besSET_RETURN_STRING(res);
  free(res);
besEND


/**
=section add
=H add

Adds mpz_t objects
*/
besFUNCTION(add)
  pModuleObject p;
  char *s, *t, *res;

  int i;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("zz")
    &s,&t
  besARGEND

  mpz_set_str(g_Op1, s, 10);
  mpz_set_str(g_Op2, t, 10);
  mpz_add(g_Res, g_Op1, g_Op2);

  res = mpz_get_str(NULL,10,g_Res);
  besSET_RETURN_STRING(res);
  free(res);
besEND

/**
=section sub
=H sub

Subtract mpz_t objects
*/
besFUNCTION(sub)
  pModuleObject p;
  char *s, *t, *res;

  int i;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("zz")
    &s,&t
  besARGEND

  mpz_set_str(g_Op1, s, 10);
  mpz_set_str(g_Op2, t, 10);
  mpz_sub(g_Res, g_Op1, g_Op2);

  res = mpz_get_str(NULL,10,g_Res);
  besSET_RETURN_STRING(res);
  free(res);
besEND

/**
=section divide
=H div

Divide mpz_t objects
*/
besFUNCTION(divide)
  pModuleObject p;
  char *s, *t, *res;

  int i;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("zz")
    &s,&t
  besARGEND

  mpz_set_str(g_Op1, s, 10);
  mpz_set_str(g_Op2, t, 10);
  mpz_div(g_Res, g_Op1, g_Op2);

  res = mpz_get_str(NULL,10,g_Res);
  besSET_RETURN_STRING(res);
  free(res);
besEND


/*
*TODO*
INSERT HERE THE NAME OF THE FUNCTION AND THE FUNCTION INTO THE
TABLE. THIS TABLE IS USED TO FIND THE FUNCTIONS WHEN THE MODULE
INTERFACE FILE IS COMPILED.
*/

SLFST GMP2_SLFST[] ={

{ "versmodu" , versmodu },
{ "bootmodu" , bootmodu },
{ "finimodu" , finimodu },
{ "emsgmodu" , emsgmodu },
{ "init" , init },
{ "init_set" , init_set },
{ "mul" , mul },
{ "mul_si" , mul_si },
{ "add" , add },
{ "sub" , sub },
{ "divide" , divide },
{ NULL , NULL }
  };
