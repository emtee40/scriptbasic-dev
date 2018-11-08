/*
READ THIS FILE AND CHANGE THE SOURCE WHEREVER YOU SEE COMMENTS STARTING
WITH THE WORD *TODO*

WHEN YOU ARE FINISHED YOU CAN 

  FILE   : interface.c
  HEADER : interface.h
  BAS    : slre.bas
  AUTHOR : Armando I. Rivera (AIR)

  DATE: 2018-11-07

  CONTENT:
  This is the interface.c file for the ScriptBasic module slre
----------------------------------------------------------------------------
Supported OS's
NTLIBS: 
UXLIBS: 
DWLIBS: 
*/

/*
*TODO*
INCLUDE HERE THE SYSTEM HEADER FILES THAT ARE NEEDED TO COMPILE THIS MODULE
*/

#ifdef WIN32
/*
*TODO*
INCLUDE HERE THE WIN32 SPECIFIC HEADER FILES THAT ARE NEEDED TO COMPILE THIS MODULE
*/
#else
/*
*TODO*
INCLUDE HERE THE UNIX SPECIFIC HEADER FILES THAT ARE NEEDED TO COMPILE THIS MODULE
*/
#endif

/*
*TODO*
INCLUDE HERE THE LOCAL HEADER FILES THAT ARE NEEDED TO COMPILE THIS MODULE
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "../../basext.h"
#include "slre.h"

/*
*TODO*
INSERT THE BASIC CODE THAT WILL GET INTO THE FILE slre.BAS
AFTER THE LINE 'TO_BAS:' AND BEFORE THE LINE END OF THE COMMENT

NOTE THAT SUB AND COMMAND DECLARATIONS ARE CREATED AUTOMATICALLY
FROM THE FUNCTION DEFINTIONS WHEN THE MODULE IS CONFIGURED BEFORE
COMPILATION

TO_BAS:
declare sub     ::m alias "match"   lib "slre"
declare sub     ::$ alias "dollar"  lib "slre"
*/

/*
*TODO*
DECLARE HERE THE MODULE OBJECT TYPE. THIS STRUCTURE SHOULD HOLD THE
DATA AVAILABLE FOR EACH INTERPRETER THREAD. USE THIS STRUCTURE TO
STORE GLOBAL VALUES INSTEAD OF USING GLOBAL VARIABLES.
*/
typedef struct _ModuleObject {
  const char *match[100];
  int count;
  }ModuleObject,*pModuleObject;

int ar_match_count;
const char *matches[100];
/*
*TODO*
ALTER THE VERSION NEGOTIATION CODE IF YOU NEED
*/
besVERSION_NEGOTIATE
  return (int)INTERFACE_VERSION;
besEND

/*
*TODO*
ALTER THE ERROR MESSAGE FUNCTION
*/
besSUB_ERRMSG

  switch( iError ){
    case 0x00080000: return "ERROR HAS HAPPENED";
    }
  return "Unknown slre module error.";
besEND

/*
*TODO*
ALTER THE MODULE INITIALIZATION CODE
*/
besSUB_START
  pModuleObject p;

  besMODULEPOINTER = besALLOC(sizeof(ModuleObject));
  if( besMODULEPOINTER == NULL )return 0;
  p = (pModuleObject)besMODULEPOINTER;

/*
*TODO*
INSERT HERE ANY CODE THAT YOU NEED TO INITIALIZE THE MODULE FOR THE
ACTUAL INTERPRETER THREAD
*/

besEND

/*
*TODO*
ALTER THE MODULE FINISH CODE IF NEEDED
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

  for( int x=0; x < ar_match_count; x++){
    if (strlen(matches[x])) {
      free(matches[x]);
    }
  }

  return 0;
besEND


/*
*TODO*
WRITE YOUR MODULE INTERFACE FUNCTIONS FOLLOWING THIS SKELETON

NOTE THAT THIS IS A SAMPLE FUNCTION, YOU CAN ALSO DELETE
LINES FROM IT IF NEEDED
*/
/**
=section match
=H Match a string against a regular expression

=verbatim
slre::match(string,regexp,flags)
=noverbatim

This function is the main regular expression match function. The first argument 
is the string that is to be matched against the regular expression. The second 
argument is the regular expression. If the string matches the regular expression the 
return value of the function is true, otherwise false. The regular expressions 
may contain parentheses inside it. If it does the substrings matching the 
regular expression part between the parentheses will be stored in a 
regular expression dollar array.

The third option determines whether the search will be case-sensitive.  0 if false, 1 is true.

The substrings can be accessed via the function T<slre::dollar()> R<dollar>.
*/

besFUNCTION(match)
  pModuleObject p;
  struct slre_cap cap[100];
  const char *regexp;
  const char *buf;
  int num_caps=100;
  int flags;
  int ret;

  p = (pModuleObject)besMODULEPOINTER;
  besRETURNVALUE = NULL;

  besARGUMENTS("zzi")
  &regexp,&buf,&flags
  besARGEND

  // Reset sub match count
  ar_match_count = 0;
  ret = slre_match(regexp,buf,strlen(buf),cap,num_caps,flags);

  if (ret) {
    for (int x =0; x < ar_match_count; x++) {
      /* Copy info from cap struct into matches array */

      
      if (cap[x].len) {
        matches[x] = strndup(cap[x].ptr, cap[x].len);
      }
    }
  }

  besRETURN_LONG(ret)
besEND

/**
=section n
=H number of matches

=verbatim
slre::n()
=noverbatim
return the number of usable matches substrings
*/
besFUNCTION(nmatch)
  pModuleObject p;

  p = (pModuleObject)besMODULEPOINTER;

  besRETURN_LONG(ar_match_count);
besEND  


/**
=section dollar
=H Return the i-th sub string

=verbatim
re::dollar(i)
re::$(i)
=noverbatim

return the i-th matched substring 
*/
besFUNCTION(dollar)
  pModuleObject p;
  int count;
  long n;

  p = (pModuleObject)besMODULEPOINTER;
  if( p == NULL )return 0;
  
  besARGUMENTS("i")
  &count
  besARGEND

  besSET_RETURN_STRING(matches[count]);

besEND
/*
*TODO*
INSERT HERE THE NAME OF THE FUNCTION AND THE FUNCTION INTO THE
TABLE. THIS TABLE IS USED TO FIND THE FUNCTIONS WHEN THE MODULE
INTERFACE FILE IS COMPILED TO BE LINKED STATIC INTO A VARIATION
OF THE INTERPRETER.
*/

SLFST SLRE_SLFST[] ={

{ "versmodu"  , versmodu },
{ "bootmodu"  , bootmodu },
{ "finimodu"  , finimodu },
{ "emsgmodu"  , emsgmodu },
{ "match"     , match    },
{ "m"         , match    },
{ "n"         , nmatch   },
{ NULL , NULL }
  };
