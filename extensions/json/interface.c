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
TO_BAS:

' JSON TYPES
CONST TYPEError   = -1
CONST TYPENull    = 1
CONST TYPEString  = 2
CONST TYPENumber  = 3
CONST TYPEObject  = 4
CONST TYPEArray   = 5
CONST TYPEBoolean = 6
 

*/
/*
*TODO*
DECLARE HERE THE MODULE OBJECT TYPE. THIS STRUCTURE SHOULD HOLD THE
DATA AVAILABLE FOR EACH INTERPRETER THREAD. USE THIS STRUCTURE TO
STORE GLOBAL VALUES INSTEAD OF USING GLOBAL VARIABLES.
*/
typedef struct _ModuleObject {
  int blah;
  }ModuleObject,*pModuleObject;

typedef struct _JOBJECT {
  JSON_Value *root[256];
  JSON_Value *current;
  int index;
}JOBJECT, *pJOBJECT;

static pJOBJECT z;

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

  z = besALLOC(sizeof(JOBJECT));
  if (z == NULL) return 0;

/*
*TODO*
INSERT HERE ANY CODE THAT YOU NEED TO INITIALIZE THE MODULE FOR THE
ACTUAL INTERPRETER THREAD
*/
  z->index = 0;
besEND

/*
*TODO*
ALTER THE MODULE FINISH CODE IF NEEDED
*/
besSUB_FINISH
  pModuleObject p;
  pJOBJECT z;

  /*
    YOU CERTAINLY NEED THIS POINTER TO FREE ALL RESOURCES THAT YOU ALLOCATED
    YOU NEED NOT CALL besFREE TO FREE THE MEMORY ALLOCATED USING besALLOC
    CLOSE ANY FILE THAT REMAINED OPEN, RELEASE DATABASE HANDLES AND ALL
    OTHER RESOURCES INCLUDING MEMORY *NOT* ALLOCATED CALLING besALLOC
  */
  p = (pModuleObject)besMODULEPOINTER;
  if( p == NULL )return 0;
  // if (jRoot)
  //   json_value_free(jRoot);

  // for (int x = 0; x < z->index; x++) {
  //     if (z->root[x])
  //       json_value_free(z->root[x]);
  // }

  return 0;
besEND


/**
=section loadfile
=H json::loadfile(filename)

Loads filename, returns array of json objects
*/
besFUNCTION(loadfile)
  pModuleObject p;
  char* filename;

  JSON_Array *items;
  JSON_Object *obj;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("z")
    &filename
  besARGEND

  if (z->index != 0) z->index += 1;
  z->root[z->index] = json_parse_file(filename);
  z->current = z->root[z->index];

  switch (json_value_get_type(z->root[z->index])) {
    case JSONArray:
      items = json_value_get_array(z->root[z->index]);
      besRETURN_POINTER(items);
      break;
    case JSONObject:
      obj = json_value_get_object(z->root[z->index]);
      besRETURN_POINTER(obj);
      break;
  }


besEND


/**
=section loadstr
=H json::loadstr(json_str)

Loads json string, returns array of json objects
*/
besFUNCTION(loadstr)
  pModuleObject p;
  char* json_str;

  JSON_Array *items;
  JSON_Object *obj;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("z")
    &json_str
  besARGEND

  if (z->index != 0) z->index += 1;
  z->root[z->index] = json_parse_string(json_str);
  z->current = z->root[z->index];

  switch (json_value_get_type(z->root[z->index])) {
    case JSONArray:
      items = json_value_get_array(z->root[z->index]);
      besRETURN_POINTER(items);
      break;
    case JSONObject:
      obj = json_value_get_object(z->root[z->index]);
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

  JSON_Value *obj;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pz")
    &obj, &filename
  besARGEND

  result = json_serialize_to_file_pretty(obj,filename);
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
  void *item;
  JSON_Value *parent;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("p")
    &item
  besARGEND

  parent = json_value_get_parent( (JSON_Value*) item);

  switch (json_type(parent)) {
    case JSONArray:
      cnt = json_array_get_count((JSON_Array*)item);
      break;
    case JSONObject:
      cnt = json_object_get_count((JSON_Object*)item);
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
  JSON_Object *items;
  JSON_Array *arr;
  JSON_Object *obj;
  char * name;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pi")
    &items, &index
  besARGEND

  switch (json_type(items)) {
    case JSONArray:
      obj = json_array_get_object(items,index);
      besRETURN_POINTER(obj);
      break;
    case JSONObject:
      name = json_object_get_name(items, index);
      obj = json_object_get_object(items, name);
      besRETURN_POINTER(obj);
      break;
  }
  
besEND

/**
=section getObject
=H json::getObject(X, KEY)

Returns array of data at KEY path
*/

besFUNCTION(getobject)
  pModuleObject p;
  int index;
  JSON_Value *tmpVal, *tmpValArray;
  JSON_Array *arr;
  JSON_Object *obj, *tmpObj;
  char *key;
  char *res;
  double result;
  char * name;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pi")
    &obj, &index
  besARGEND

  tmpVal = json_object_get_wrapping_value(obj);
  
  switch (json_type(tmpVal)) {	
	  case JSONArray:
      arr = json_array_get_object(obj,index);
      besRETURN_POINTER(arr);
      break;
		
      case JSONObject:
        tmpVal = json_object_get_value_at(obj,index);
        tmpObj = json_value_get_object(tmpVal);
        besRETURN_POINTER(tmpObj); 
        break;  
	}  
   
besEND

/**
=section get
=H json::get(X, KEY)

Returns object data at KEY path
*/
besFUNCTION(get)
  pModuleObject p;
  int index;
  JSON_Value  *tmpObj;
  JSON_Object *obj;
  JSON_Array *arr;
  char *key;
  char *res; 
  double result;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pz")
    &obj, &key
  besARGEND

    tmpObj = json_object_dotget_value(obj,key);

    switch (json_value_get_type(tmpObj)) {
      case JSONString:
        res = strdup(json_object_dotget_string(obj, key));
        besSET_RETURN_STRING(res);
        free(res);
        break;

      case JSONNumber:
        result = json_object_dotget_number(obj,key);
        besRETURN_DOUBLE(result);
        break;
        
      case JSONArray:
        arr = json_object_dotget_array(obj, key);
        besRETURN_POINTER(arr);
        break;
      
      case JSONBoolean:
        besRETURN_LONG(json_object_dotget_boolean(obj,key))
        break;
    }
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

  if (z->index != 0) z->index += 1;
  z->root[z->index] = json_value_init_object();
  z->current = z->root[z->index];

  obj  = json_value_get_object(z->root[z->index]);


  besRETURN_POINTER(obj);

besEND

/**
=section newObject
=H json::newObject()

Returns new json  object
*/
besFUNCTION(newobject)
  pModuleObject p;
  JSON_Value *obj;
  JSON_Value *tmp;



  p = (pModuleObject)besMODULEPOINTER;

  tmp = json_value_init_object();
  obj  = json_value_get_object(tmp);




  besRETURN_POINTER(obj);

besEND

/**
=section newArray
=H json::newArray()

Returns new json array object
*/
besFUNCTION(newArray)
  pModuleObject p;
  JSON_Value *obj;



  p = (pModuleObject)besMODULEPOINTER;

  obj  = json_value_init_array();


  besRETURN_POINTER(obj);

besEND

/**
=section getArray
=H json::getArray()

Returns json array object converted from a json array
*/
besFUNCTION(getArray)
  pModuleObject p;
  JSON_Object *obj,*tmpObj;
  JSON_Array *array;
  JSON_Value *tmp;



  p = (pModuleObject)besMODULEPOINTER;
  
  besARGUMENTS("p")
    &obj
  besARGEND

  tmp = json_object_get_wrapping_value(obj);
  tmpObj  = json_value_get_array(tmp);


  besRETURN_POINTER(tmpObj);

besEND

/**
=section getArrayObject
=H json::getArrayObject(x)

Returns json object
*/
besFUNCTION(getArrayobject)
  pModuleObject p;
  JSON_Object *obj;
  JSON_Value *tmp;



  p = (pModuleObject)besMODULEPOINTER;
  
  besARGUMENTS("p")
    &tmp
  besARGEND

  obj  = json_value_get_object(tmp);


  besRETURN_POINTER(obj);

besEND

/**
=section getArrayItem
=H json::getArrayItem(object,index)

Returns json object from array
*/
besFUNCTION(getArrayItem)
  pModuleObject p;
  JSON_Object  *tmpObj;
  JSON_Array *obj;
  JSON_Value *tmpVal, *arr, *valArray;
  int index;
  size_t c, arrCount;



  p = (pModuleObject)besMODULEPOINTER;
  
  besARGUMENTS("pi")
    &obj,&index
  besARGEND

   if (tmpVal = json_array_get_value(obj,index)) {
      tmpObj = json_value_get_object(tmpVal);

      besRETURN_POINTER(tmpObj);
   }

besEND


/**
=section addArray
=H json::addArray(src_array, array_to_add)

Returns json array object converted from a json array
*/
besFUNCTION(addarray)
  pModuleObject p;
  JSON_Object *obj, *avalue;
  JSON_Array *arr, *arr2;
  JSON_Value  *tmpVal, *tmpArrVal;



  p = (pModuleObject)besMODULEPOINTER;
  
  besARGUMENTS("pp")
    &arr, &avalue
  besARGEND

  arr2 = json_value_get_array(arr);
  
  tmpArrVal = json_object_get_wrapping_value(avalue);
  //~ printf("%d\n", json_value_get_type(tmpArrVal));
  if (arr2){
	json_array_append_value(arr2,tmpArrVal);
  }else{
	json_array_append_value(arr,tmpArrVal);
  }


  //~ besRETURN_POINTER(obj);

besEND

/**
=section setValue
=H json::setValue(object, key, value)

Creates/Updates value for OBJECT
*/
besFUNCTION(setvalue)
  pModuleObject p;
  int index;
  JSON_Object *obj;
  char *key;
  JSON_Value *value;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pzp")
    &obj, &key, &value
  besARGEND

  json_object_dotset_value(obj, key, value);

besEND

/**
=section settext
=H json::settext(object, key, value)

Creates/Updates STRING value for OBJECT
*/
besFUNCTION(settext)
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

/**
=section setnum
=H json::setnum(object, key, value)

Creates/Updates NUMERIC value for OBJECT
*/
besFUNCTION(setnum)
  pModuleObject p;
  int index;
  JSON_Object *obj;
  char *key;
  long value;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pzi")
    &obj, &key, &value
  besARGEND

  json_object_dotset_number(obj, key, value);

besEND

/**
=section setBool
=H json::setBool(object, key, value)

Creates/Updates BOOLEAN  value for OBJECT
*/
besFUNCTION(setbool)
  pModuleObject p;
  int index;
  JSON_Object *obj;
  char *key;
  long value;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pzi")
    &obj, &key, &value
  besARGEND

  json_object_dotset_boolean(obj, key, value);

besEND



/**
=section prettyPrint
=H json::prettyPrint(object)

*/
besFUNCTION(prettyprint)
  pModuleObject p;
  int index;
  JSON_Object *obj;
  JSON_Value *tmp;
  char *key;
  long value;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("p")
    &obj
  besARGEND

  tmp = json_object_get_wrapping_value(obj);
  besSET_RETURN_STRING(json_serialize_to_string_pretty(tmp));

besEND

/**
=section Print
=H json::Print(object)

*/
besFUNCTION(print)
  pModuleObject p;
  int index;
  JSON_Object *obj;
  JSON_Value *tmp;
  char *key;
  long value;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("p")
    &obj
  besARGEND

  tmp = json_object_get_wrapping_value(obj);
  besSET_RETURN_STRING(json_serialize_to_string(tmp));

besEND
/**
=section getName
=H json::getName(JSONObject)

Retrieves the name (key) for the provided
JSONObject
*/
besFUNCTION(getName)
  pModuleObject p;
  JSON_Object *obj;
  const char *key;
  int index;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pi")
    &obj, &index
  besARGEND

  key = json_object_get_name(obj,index);
  besSET_RETURN_STRING(key);
  

besEND

/**
=section type
=H json::type(JSONObject)

Retrieves the type of the provided JSONObject
*/
besFUNCTION(type)
  pModuleObject p;
  JSON_Object *obj;
  JSON_Value * val;
  long object_type;
  int index;


  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("pi")
    &obj,&index
  besARGEND

  val = json_object_get_value_at(obj, index);
  object_type = json_value_get_type(val);
  besRETURN_LONG(object_type);
  

besEND

/**
=section getParent
=H json::getParent(JSONObject)

Retrieves the PARENT of the provided JSONObject
*/
besFUNCTION(getparent)
  pModuleObject p;
  JSON_Object *obj,*res;
  JSON_Value *val, *parent;
  long object_type;
  int index;


  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("p")
    &obj
  besARGEND

  val = json_object_get_wrapping_value(obj);
  parent = json_value_get_parent(val);
  res = json_value_get_object(parent);
  besRETURN_POINTER(res);
  

besEND


SLFST JSON_SLFST[] ={

{ "versmodu" , versmodu },
{ "bootmodu" , bootmodu },
{ "finimodu" , finimodu },
{ "emsgmodu" , emsgmodu },
{ "loadfile" , loadfile },
{ "loadstr" , loadstr },
{ "count" , count },
{ "object" , object },
{ "get" , get },
{ "new" , new },
{ "settext" , settext },
{ "setnum" , setnum },
{ "save" , save },
{ NULL , NULL }
  };
