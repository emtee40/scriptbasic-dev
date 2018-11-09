/*
READ THIS FILE AND CHANGE THE SOURCE WHEREVER YOU SEE COMMENTS STARTING
WITH THE WORD *TODO*

WHEN YOU ARE FINISHED YOU CAN 

  FILE   : interface.c
  HEADER : interface.h
  BAS    : json.bas
  AUTHOR : *TODO*

  DATE: 

  CONTENT:
  This is the interface.c file for the ScriptBasic module json
----------------------------------------------------------------------------

//NTLIBS:
UXLIBS: 
DWLIBS:
----------------------------------------------------------------------------


//DWLIBS:

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
#include "../../basext.h"
#include <stdlib.h>
#include <string.h>
#include "jsmn.h"

/*
*TODO*
INSERT THE BASIC CODE THAT WILL GET INTO THE FILE json.BAS
AFTER THE LINE 'TO_BAS:' AND BEFORE THE LINE END OF THE COMMENT

NOTE THAT SUB AND COMMAND DECLARATIONS ARE CREATED AUTOMATICALLY
FROM THE FUNCTION DEFINTIONS WHEN THE MODULE IS CONFIGURED BEFORE
COMPILATION

TO_BAS:
*/

/*
*TODO*
DECLARE HERE THE MODULE OBJECT TYPE. THIS STRUCTURE SHOULD HOLD THE
DATA AVAILABLE FOR EACH INTERPRETER THREAD. USE THIS STRUCTURE TO
STORE GLOBAL VALUES INSTEAD OF USING GLOBAL VARIABLES.
*/
typedef struct _ModuleObject {
  char a; /* You may delete this. It is here to make the initial interface.c compilable. */
  }ModuleObject,*pModuleObject;

jsmntok_t sb_tok[2048];
long sb_tok_count;
char JSON_STRING[4096];

int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
    if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start && strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
        return 0;
    }
      return -1;
}
    
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
  return "Unknown json module error.";
besEND

/*
*TODO*
ALTER THE MODULE INITIALIZATION CODE
*/
besSUB_START
  pModuleObject p;

  besMODULEPOINTER = besALLOC(sizeof(ModuleObject));
  if( besMODULEPOINTER == NULL )return 0;

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

  return 0;
besEND


/*
*TODO*
WRITE YOUR MODULE INTERFACE FUNCTIONS FOLLOWING THIS SKELETON

NOTE THAT THIS IS A SAMPLE FUNCTION, YOU CAN ALSO DELETE
LINES FROM IT IF NEEDED
*/
/**
=section parse
=H title that goes into the BASIC documentation for this function

detail here what the function does so that the BASIC programmer
can understand how he/she can use it
*/

besFUNCTION(parse)
  pModuleObject p;
  jsmn_parser parser;
  int r;
  char *json_string;
  jsmntok_t jsmn_tok[2048];
  
  
  

// r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));
  memset(JSON_STRING,0,4096);

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("z")
  &json_string
  besARGEND

  r = jsmn_parse(&parser, json_string, strlen(json_string), jsmn_tok, sizeof(jsmn_tok)/sizeof(jsmn_tok[0]));

  if (r < 0) {
    printf("Failed to parse JSON: %d\n", r);
    return COMMAND_ERROR_MEMORY_LOW;
  }

  /* Assume the top-level element is an object */
  if (r < 1 || jsmn_tok[0].type != JSMN_OBJECT) {
      printf("Object expected\n");
      return COMMAND_ERROR_MEMORY_LOW;
      
  }
  memcpy( (void *)&sb_tok, (void *)&jsmn_tok, sizeof(jsmn_tok));
  strncpy(JSON_STRING,json_string,strlen(json_string));
  sb_tok_count = r;
  besRETURN_LONG(r);
besEND

/**
=section find
=H title that goes into the BASIC documentation for this function
*/
besFUNCTION(find)
  pModuleObject p;
  jsmn_parser parser;
  int r;
  char *key;
  char *tmpStr;

 besARGUMENTS("z")
  &key
  besARGEND
  
  if(sb_tok_count) {
    for (int i = 0; i < sb_tok_count; i++) {
      switch (sb_tok[i].type) {
        case JSMN_ARRAY:
          break;

        case JSMN_OBJECT:
          break;

        case JSMN_STRING:
          if (jsoneq(JSON_STRING, &sb_tok[i], key) == 0){
            tmpStr = strndup(JSON_STRING + sb_tok[i+1].start, sb_tok[i+1].end-sb_tok[i+1].start);
            besSET_RETURN_STRING(tmpStr)
            free(tmpStr);
            break;
          }
      }
      


    }
  }
besEND
/*
*TODO*
INSERT HERE THE NAME OF THE FUNCTION AND THE FUNCTION INTO THE
TABLE. THIS TABLE IS USED TO FIND THE FUNCTIONS WHEN THE MODULE
INTERFACE FILE IS COMPILED TO BE LINKED STATIC INTO A VARIATION
OF THE INTERPRETER.
*/

SLFST JSON_SLFST[] ={

{ "versmodu" , versmodu },
{ "bootmodu" , bootmodu },
{ "finimodu" , finimodu },
{ "emsgmodu" , emsgmodu },
{ "parse" , parse },
{ "find" , find },
{ NULL , NULL }
  };
