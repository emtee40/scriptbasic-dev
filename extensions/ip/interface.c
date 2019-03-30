/*
READ THIS FILE AND CHANGE THE SOURCE WHEREVER YOU SEE COMMENTS STARTING
WITH THE WORD *TODO*

WHEN YOU ARE FINISHED YOU CAN 

  FILE   : interface.c
  HEADER : interface.h
  BAS    : ip.bas
  AUTHOR : *TODO*

  DATE: 

  CONTENT:
  This is the interface.c file for the ScriptBasic module ip
----------------------------------------------------------------------------

Remove the two characters // from following line(s) if this module is supposed to
be compiled under specific OS's. If there is a need for some library to successfully
compile the module under Windows specify the names of the libraries on the line
as it is listed for the linker application. This is usually something like

WINDOWS: libname1.lib libname2.lib ... libnameX.lib
LINUX/MACOS: -lm -ldl

If there are no libraries, but still the module is to be compiled under Windows
do remove the // characters so that the program setup.pl will know that the
module is meant for Windows.

//NTLIBS:
UXLIBS: -lresolv
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
#include <stdlib.h>
#include <string.h>
#include "../../basext.h"
#include "iptools.h"

/*
*TODO*
INSERT THE BASIC CODE THAT WILL GET INTO THE FILE ip.BAS
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
  return "Unknown ip module error.";
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
=section Public
=H IP::Public

Returns the Public (WAN) IP Address
Requires NO Arguments
*/
besFUNCTION(Public)
  pModuleObject p;
  char *pubIP,*iface;

  p = (pModuleObject)besMODULEPOINTER;

  pubIP = publicIP();

  besSET_RETURN_STRING(pubIP);
  free(pubIP);
besEND

/*
=section Local
=H IP::Local

Returns the Local (LAN) IP Address
Requires name of interface

IP::Local("eth0")
*/
besFUNCTION(Local)
  pModuleObject p;
  char *locIP,*iface;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("z")
    &iface
  besARGEND

  locIP = localIP(iface);

  besSET_RETURN_STRING(locIP);
  free(locIP);
besEND

/*
=section MacAddress
=H IP::MacAddress

Returns the interface MAC Address
Requires name of interface

IP::MacAddress("eth0")
*/
besFUNCTION(MacAddress)
  pModuleObject p;
  char *mAddr,*iface;

  p = (pModuleObject)besMODULEPOINTER;

  besARGUMENTS("z")
    &iface
  besARGEND

  mAddr = getMac(iface);

  besSET_RETURN_STRING(mAddr);
  free(mAddr);
besEND
/*
/*
*TODO*
INSERT HERE THE NAME OF THE FUNCTION AND THE FUNCTION INTO THE
TABLE. THIS TABLE IS USED TO FIND THE FUNCTIONS WHEN THE MODULE
INTERFACE FILE IS COMPILED.
*/

SLFST IP_SLFST[] ={

{ "versmodu" , versmodu },
{ "bootmodu" , bootmodu },
{ "finimodu" , finimodu },
{ "emsgmodu" , emsgmodu },
{ "Public" , Public },
{ NULL , NULL }
  };
