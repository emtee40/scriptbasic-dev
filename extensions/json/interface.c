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
#include <string.h>
#include "../../basext.h"
#include "parson.h"

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
  JSON_Value* root;
  }ModuleObject,*pModuleObject;


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
  json_value_free(p->root);

  return 0;
besEND


/**
=section load
=H json::load

Loads filename, returns array of json objects
*/
besFUNCTION(load)
  pModuleObject p;
  char* filename;
  
  JSON_Array *items;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("z")
    &filename
  besARGEND
  
  p->root = json_parse_file(filename);

  if (json_value_get_type(p->root) != JSONArray) {
    return COMMAND_ERROR_BAD_CALL;
  }
  items = json_value_get_array(p->root);
  besRETURN_POINTER(items);
besEND

/**
=section count
=H json::count(X)

Returns number of json objects in X
*/
besFUNCTION(count)
  pModuleObject p;
  int cnt;
  JSON_Array *items;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("p")
    &items
  besARGEND
  
  cnt = json_array_get_count(items);
  besRETURN_LONG(cnt);
besEND

/**
=section object
=H json::object(X, index)

Returns object at index in JSON object array X
*/
besFUNCTION(object)
  pModuleObject p;
  int index;
  JSON_Array *items;
  JSON_Object *obj;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pi")
    &items, &index
  besARGEND
  
  obj = json_array_get_object(items,index);
  besRETURN_POINTER(obj);
besEND

/**
=section text
=H json::text(X, KEY)

Returns object text at KEY path
*/
besFUNCTION(text)
  pModuleObject p;
  int index;
  JSON_Object *obj;
  char *key;
  char res[8192];

  memset(&res,0,8192);

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pz")
    &obj, &key
  besARGEND
  
  char* dot = strchr(key, '.');
  if (dot == NULL) {
    if  (json_object_get_value(obj,key) != 0)
      strcpy(res,json_object_get_string(obj,key));
  }else{
    if  (json_object_dotget_value(obj,key) != 0)
      strcpy(res,json_object_dotget_string(obj, key));
  }

  besRETURN_STRING(res);

besEND

SLFST JSON_SLFST[] ={

{ "versmodu" , versmodu },
{ "bootmodu" , bootmodu },
{ "finimodu" , finimodu },
{ "emsgmodu" , emsgmodu },
{ "load" , load },
{ "count" , count },
{ "object" , object },
{ "text" , text },
{ NULL , NULL }
  };
