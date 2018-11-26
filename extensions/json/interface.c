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
  JSON_Value *tmpRoot;
  }ModuleObject,*pModuleObject;

static JSON_Value *jRoot;
static int jType;

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
  if (jRoot)
    json_value_free(jRoot);



  return 0;
besEND


/**
=section load
=H json::load(filename)

Loads filename, returns array of json objects
*/
besFUNCTION(load)
  pModuleObject p;
  char* filename;
  
  JSON_Array *items;
  JSON_Object *obj;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("z")
    &filename
  besARGEND
  
 jRoot = json_parse_file(filename);

  switch (json_value_get_type(jRoot)) {
    case JSONArray:
      items = json_value_get_array(jRoot);
      besRETURN_POINTER(items);
      break;
    case JSONObject:
      obj = json_value_get_object(jRoot);
      besRETURN_POINTER(obj);
      break;
  }


besEND

/**
=section save
=H json::save(filename)

Saves json to filename
*/
besFUNCTION(save)
  pModuleObject p;
  char* filename;
  JSON_Status result;
  
  JSON_Array *items;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("z")
    &filename
  besARGEND

  result = json_serialize_to_file_pretty(jRoot,filename);  
  if (result == JSONFailure)
    return COMMAND_ERROR_BAD_FILE_NUMBER;
  else
    besRETURN_LONG(result);

besEND

/**
=section count
=H json::count(X)

Returns number of json objects in X
*/
besFUNCTION(count)
  pModuleObject p;
  int cnt;
  void *items;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("p")
    &items
  besARGEND

  switch (json_type(jRoot)) {
    case JSONArray:
      cnt = json_array_get_count((JSON_Array*)items);
      break;
    case JSONObject:
      cnt = json_object_get_count((JSON_Object*)items);
      break;
  }  
  
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
  void *items;
  JSON_Object *obj;
  char * name;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pi")
    &items, &index
  besARGEND

  switch (json_type(jRoot)) {
    case JSONArray:  
      obj = json_array_get_object((JSON_Array*)items,index);
      break;
    case JSONObject:
      name = json_object_get_name((JSON_Object*)items, index);
      obj = json_object_get_object((JSON_Object*)items, name);
      break;
  }
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
  char *res;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pz")
    &obj, &key
  besARGEND

    if  (json_object_dotget_value(obj,key) != 0)
      res = strdup(json_object_dotget_string(obj, key));


  besSET_RETURN_STRING(res);
  free(res);

besEND

/**
=section new
=H json::text()

Returns new json root object
*/
besFUNCTION(new)
  pModuleObject p;
  JSON_Object *obj;



  p = (pModuleObject)besMODULEPOINTER;

  jRoot = json_value_init_object();
  obj  = json_value_get_object(jRoot);


  besRETURN_POINTER(obj);

besEND

/**
=section add
=H json::settext()

Creates new text json entry
*/
besFUNCTION(add)
  pModuleObject p;
  int index;
  JSON_Object *obj;
  char *key;
  char *value;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pzz")
    &obj, &key, &value
  besARGEND

  json_object_dotset_string(obj, key, value);

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
{ "new" , new },
{ "add" , add },
{ "save" , save },
{ NULL , NULL }
  };
