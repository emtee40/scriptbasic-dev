/*

Mini-XML Support code for Scriptbasic

Copyright 2010, Armando I. Rivera, Recursive Media Group.

Released under the terms of the Mini-Xml Licence.

The Mini-XML library and included programs are provided under the terms of the
GNU Library General Public License (LGPL) with the following exceptions:

  1. Static linking of applications to the Mini-XML library does not constitute
    a derivative work and does not require the author to provide source code for
    the application, use the shared Mini-XML libraries, or link their applications
    against a user-supplied version of Mini-XML.

  If you link the application to a modified version of Mini-XML, then the
    changes to Mini-XML must be provided under the terms of the LGPL in sections
    1, 2, and 4.
    
  2. You do not have to provide a copy of the Mini-XML license with programs
    that are linked to the Mini-XML library, nor do you have to identify the
    Mini-XML license in your program or documentation as required by section 6
    of the LGPL.

  FILE   : interface.c


  CONTENT:
  This is the interface.c file for the ScriptBasic module xml


 DWLIBS:-lmxml
 UXLIBS:-lmxml

*/

/*

TOBAS:
declare sub     ::LoadDoc      alias "LoadDoc"      lib "mxml"
declare sub     ::GetNext      alias "GetNext"      lib "mxml"
declare sub     ::GetChild     alias "GetChild"     lib "mxml"
declare sub     ::GetNodeValue alias "GetNodeValue" lib "mxml"
declare sub     ::GetProperty  alias "GetProperty"  lib "mxml"
declare sub     ::GetNode      alias "GetNode"      lib "mxml"
declare sub     ::SaveDoc      alias "SaveDoc"      lib "mxml"
declare sub     ::NewDoc       alias "NewDoc"       lib "mxml"
declare sub     ::FreeDoc      alias "FreeDoc"      lib "mxml"
*/

#include "mxml_src/mxml.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../basext.h"

typedef struct _ModuleObject {
  void *HandleArray;
}ModuleObject,*pModuleObject;

#define _MAX_PATH 4096

#define GET_ARGUMENT_POINTER(X,Y) \
  if( besARGNR < Y )return COMMAND_ERROR_ARGUMENT_RANGE;\
  Argument = besARGUMENT(Y);\
  besDEREFERENCE(Argument);\
  if( Argument == NULL )X=NULL; else { \
      if( Argument->vType != VTYPE_STRING ||\
          STRLEN(Argument) != sizeof(void *) ){\
    return COMMAND_ERROR_ARGUMENT_RANGE;\
    }\
  memcpy(&(X),STRINGVALUE(Argument),sizeof(void *));\
  }

#define RETURN_POINTER(X) \
  besALLOC_RETURN_STRING( sizeof( void *) );\
  memcpy(STRINGVALUE(besRETURNVALUE),&(X),sizeof(void *));

    
    
besVERSION_NEGOTIATE
  return (int)INTERFACE_VERSION;
besEND

besSUB_START
  pModuleObject p;

  besMODULEPOINTER = besALLOC(sizeof(ModuleObject));
  if( besMODULEPOINTER == NULL )return 0;

  p = (pModuleObject)besMODULEPOINTER;
  return 0;

besEND

besSUB_FINISH
  pModuleObject p;

  p = (pModuleObject)besMODULEPOINTER;
  if( p == NULL )return 0;
  return 0;
besEND

/**
=section LoadDoc
=H Load an XML file and read into memory

You should use this function to read the content of an XML file into memory.
The argument of the function is the name of the file to be read. The function
will return a handle to the structure created during the parsing of the file
content.

=verbatim
 DOC = mxml::LoadDoc("my_file.xml")
=noverbatim

*/
besFUNCTION(LoadDoc)
    mxml_node_t *tree;
    FILE *fp;
    char *pszFileName;
    
    besARGUMENTS("z")
    &pszFileName
  besARGEND
    
    fp = fopen(pszFileName, "r");
  // check if file exists
  if(fp == NULL) {
      return 0;
  }
   
  tree = mxmlLoadFile(NULL, fp, MXML_OPAQUE_CALLBACK);
    fclose(fp);    

  //besFREE(pszFileName);

  besRETURN_POINTER(tree);
besEND

/**
=section GetNext
=H Get the next node of a document node

This function should be used to get the handle to the  next node in a
document node

=verbatim
 node = mxml::GetNext(<node pointer>)
=noverbatim
*/
besFUNCTION(GetNext)
    mxml_node_t *rootNode;

    besARGUMENTS("p")
    &rootNode
  besARGEND    
    
    besRETURN_POINTER(rootNode->next);
besEND

/**
=section GetChild
=H Get the next Child node of a document node

This function should be used to get the handle to the next Childe node of a
document node

=verbatim
 node = mxml::GetChild(<node pointer>)
=noverbatim
*/
besFUNCTION(GetChild)
    mxml_node_t *rootNode;

    besARGUMENTS("p")
    &rootNode
  besARGEND    
    
    besRETURN_POINTER(rootNode->child);
besEND

/**
=section GetNodeValue
=H Get the value of a document node

This function should be used to get the value (text) of a node

=verbatim
 text = mxml::GetNodeValue(<node pointer>)
=noverbatim
*/
besFUNCTION(GetNodeValue)
    mxml_node_t *rootNode;

    besARGUMENTS("p")
    &rootNode
  besARGEND    
    
    besSET_RETURN_STRING(rootNode->child->value.opaque);
besEND

/**
=section GetProperty
=H Get the a property value of a document node

This function should be used to get the
value of a property of a document node

=verbatim
 text = mxml:: mxml::GetProperty(<node pointer>,<string identifier>)
=noverbatim
*/
besFUNCTION(GetProperty)
    mxml_node_t* node;
    const char* attr;
    char* pszValue;
    
    besARGUMENTS("pz")
    &node,&attr
  besARGEND    
    
    pszValue = strdup(mxmlElementGetAttr(node, attr));

    besSET_RETURN_STRING(pszValue);
    free(pszValue);
besEND

/**
=section GetNode
=H Get a handle to a specified node

This function should be used to get the handle of a specific node.
It uses XPATH syntax, which resembles a UNIX path.

Ex, node = mxml::GetNode(doc, "/stufflist/stuff_test3/painting/img")

=verbatim
 node = mxml::GetNode(<node pointer>,<path-like string>)
=noverbatim
*/    
besFUNCTION(GetNode)
    mxml_node_t *rootNode, *node;
    char *pszValue;
    char *token, tmpStr[_MAX_PATH];

    besARGUMENTS("pz")
    &rootNode,&pszValue
  besARGEND    
    
    node = rootNode;

    memset(tmpStr,0,sizeof(tmpStr));
    strncpy(tmpStr, pszValue, strlen(pszValue));
    

    token = strtok(tmpStr, "/");
  while ( token  ) {
        node = mxmlFindElement(node,node,token,NULL,NULL,MXML_DESCEND);
    token = strtok( NULL, "/" );
  }
        
    besRETURN_POINTER(node);
besEND

/**
=section SaveDoc
=H Save to an XML file

This function should be used to save the contents of an XML tree
to a disk file

=verbatim
 mxml::SaveDoc(<DOC (root) node pointer>,<string filename>)
=noverbatim
*/
besFUNCTION(SaveDoc)
    mxml_node_t* node;
    const char* fileName;
    FILE *fp;
    int retVal;
    
    besARGUMENTS("pz")
    &node,&fileName
  besARGEND    

    fp = fopen(fileName, "w");
  if(fp == NULL) {
    besRETURN_LONG(-1);
  }
    
    retVal = mxmlSaveFile(node, fp, MXML_NO_CALLBACK);
    fclose(fp);
    besRETURN_LONG(retVal);
besEND

/**
=section NewDoc
=H Create a new XML document in memory

This function should be used to create a new XML document in memory.

The second parameter (xml version) is optional.  If not provided,
it defaults to version="1.0"

It would create a header that looks like:
    <?xml version="1.0">

=verbatim
 doc = mxml::NewDoc(<string version>)
=noverbatim
*/
besFUNCTION(NewDoc)
    mxml_node_t* node;
    char* pszVersion;
    
    
    besARGUMENTS("[z]")
    &pszVersion
  besARGEND    
    
    node = mxmlNewXML(pszVersion);
    besRETURN_POINTER(node);
    
besEND

/**
=section FreeDoc
=H Releases/Destroys an XML tree in memory

This function should be used to delete an new XML document in memory.

=verbatim
 mxml::FreeDoc(<doc pointer>)
=noverbatim
*/
besFUNCTION(FreeDoc)
    mxml_node_t* node;
    
    besARGUMENTS("p")
    &node
  besARGEND    
    
    if (node) mxmlDelete(node);
besEND


/*
    Exported Function List
*/    

START_FUNCTION_TABLE(MXML_SLFST)
// Ext. module
  EXPORT_MODULE_FUNCTION(versmodu)
  EXPORT_MODULE_FUNCTION(bootmodu)
  EXPORT_MODULE_FUNCTION(finimodu)

// Module Functions
  EXPORT_MODULE_FUNCTION(LoadDoc)
  EXPORT_MODULE_FUNCTION(GetNext)
  EXPORT_MODULE_FUNCTION(GetChild)
  EXPORT_MODULE_FUNCTION(GetNodeValue)
  EXPORT_MODULE_FUNCTION(GetNode)
  EXPORT_MODULE_FUNCTION(SaveDoc)
  EXPORT_MODULE_FUNCTION(NewDoc)
  EXPORT_MODULE_FUNCTION(FreeDoc)
  EXPORT_MODULE_FUNCTION(GetProperty)
END_FUNCTION_TABLE
// SLFST XML_SLFST[] ={

// { "versmodu"    , versmodu },
// { "bootmodu"    , bootmodu },
// { "finimodu"    , finimodu },
// { "LoadDoc"        , LoadDoc },
// { "GetNext"        , GetNext },
// { "GetChild"    , GetChild },
// { "GetNodeValue", GetNodeValue },
// { "GetNode"        , GetNode },
// { "SaveDoc"        , SaveDoc },
// { "NewDoc"        , NewDoc },
// { "FreeDoc"        , FreeDoc },
// { "GetProperty", GetProperty },
// { NULL , NULL }
//   };
