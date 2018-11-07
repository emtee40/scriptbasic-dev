/*
  FILE   : interface.c
  HEADER : interface.h
  BAS    : ftpd.bas
  AUTHOR : Peter Verhas

  DATE: March 25, 2003

  CONTENT:
  This is the interface.c file for the ScriptBasic module ftpd

This module delivers the functions that are neccessary to develop FTP server
programs that send/receive data asynchronous to/from the client via the
FTP protocol.

This module is linked statically to the sbhttp application.
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

/*
*TODO*
INSERT THE BASIC CODE THAT WILL GET INTO THE FILE ftpd.BAS
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
  return "Unknown ftpd module error.";
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
=section GET
=H send the data in an asynchronous thread to the client

=verbatim
connID = ftpD::GET(FileName,Client,Mode)
=noverbatim

This function should be used to start asynchronous data transfer to
the client. This means that the function will connect to the client
and return before the transfer is finished. The transfer goes on in
the background.

The arguments are the followings:

=itemize
=item T<FileName> the name of the file to send to the client.
=item T<Client> the address of the client in the form T<x.x.x.x:XX> where
T<x.x.x.x> is the IP address of the client and T<XX> is the port number.
=noitemize

The function returns a numerical ID that identifies the connection and
can be used later to check the state of the actual file sending.

If the function can not connect to the client it raises error.

*/
besFUNCTION(ftpget)
  pModuleObject p;
  VARIABLE Argument;

  p = (pModuleObject)besMODULEPOINTER;

  Argument = besARGUMENT(1);
  besDEREFERENCE(Argument);

  /* if argument is undef then return undef */
  if( Argument == NULL ){
    besRETURNVALUE = NULL;
    return COMMAND_ERROR_SUCCESS;
    }

  return COMMAND_ERROR_SUCCESS;
besEND

/*
*TODO*
INSERT HERE THE NAME OF THE FUNCTION AND THE FUNCTION INTO THE
TABLE. THIS TABLE IS USED TO FIND THE FUNCTIONS WHEN THE MODULE
INTERFACE FILE IS COMPILED TO BE LINKED STATIC INTO A VARIATION
OF THE INTERPRETER.
*/

SLFST FTPD_SLFST[] ={

{ "versmodu" , versmodu },
{ "bootmodu" , bootmodu },
{ "finimodu" , finimodu },
{ "emsgmodu" , emsgmodu },
{ "functionname" , functionname },
{ NULL , NULL }
  };
