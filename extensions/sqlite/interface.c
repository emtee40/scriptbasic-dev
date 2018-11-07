/*


  FILE   : interface.c
  HEADER : interface.h
  BAS    : sqlite.bas
  AUTHOR : Armando I. Rivera

  DATE:

  CONTENT:
  This is the interface.c file for the ScriptBasic module sqlite3

  DWLIBS: -lsqlite3 -lpthread
  UXLIBS: -lsqlite3 -lpthread
*/

/*
TO_BAS:
SQLITE3_OK          =   0
SQLITE3_ERROR       =   1
SQLITE3_INTERNAL    =   2
SQLITE3_PERM        =   3
SQLITE3_ABORT       =   4
SQLITE3_BUSY        =   5
SQLITE3_LOCKED      =   6
SQLITE3_NOMEM       =   7
SQLITE3_READONLY    =   8
SQLITE3_INTERRUPT   =   9
SQLITE3_IOERR       =  10
SQLITE3_CORRUPT     =  11
SQLITE3_NOTFOUND    =  12  
SQLITE3_FULL        =  13
SQLITE3_CANTOPEN    =  14  
SQLITE3_PROTOCOL    =  15  
SQLITE3_EMPTY       =  16  
SQLITE3_SCHEMA      =  17
SQLITE3_TOOBIG      =  18
SQLITE3_CONStraint  =  19
SQLITE3_MISMATCH    =  20
SQLITE3_MISUSE      =  21
SQLITE3_NOLFS       =  22
SQLITE3_AUTH        =  23
SQLITE3_ROW         = 100
SQLITE3_DONE        = 101

SQLITE3_STATIC      =   0
SQLITE_TRANSIENT    =  -1

SQLITE_INTEGER      =   1
SQLITE_FLOAT        =   2
SQLITE_TEXT         =   3
SQLITE_BLOB         =   4
SQLITE_NULL         =   5
    
*/

#include <stdio.h>
#include <string.h>

#include "../../basext.h"
#include <sqlite3.h>

besVERSION_NEGOTIATE
  return (int)INTERFACE_VERSION;
besEND

besSUB_START
  long *p;

  besMODULEPOINTER = besALLOC(sizeof(long));
  if( besMODULEPOINTER == NULL )return 0;

  p = (long*)besMODULEPOINTER;
  return 0;
besEND

besSUB_FINISH
  long *p;

  p = (long*)besMODULEPOINTER;
  if( p == NULL )return 0;
  return 0;
besEND

/**
=section OPEN
=H Open/Create an sqlite3 database file
*/

besFUNCTION(sql3_open)
     sqlite3 *db;
     const char *fileName;
     int i;

     besARGUMENTS("s")
          &fileName
     besARGEND

     i = sqlite3_open(fileName, &db);
     besRETURN_POINTER(db)
besEND

/**
=section CLOSE
=H Close an sqlite3 database file
*/
besFUNCTION(sql3_close)
     sqlite3 *db;
     int i;

     besARGUMENTS("p")
          &db
     besARGEND

     i = sqlite3_close(db);
     besRETURN_LONG(i)
besEND

/**
=section EXECUTE
=H Execute an SQL statement/command
*/
besFUNCTION(sql3_execute)
    sqlite3 *db;
    char *sqlcmd;
    int ret;

    besARGUMENTS("ps")
        &db,&sqlcmd
    besARGEND
    ret = sqlite3_exec(db,sqlcmd,NULL,NULL,NULL);
    besRETURN_LONG(ret)
besEND

/**
=section QUERY
=H Pass a Query to an sqlite3 database file
*/
besFUNCTION(sql3_query)
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *sqlcmd;
    int ret;

    besARGUMENTS("ps")
        &db,&sqlcmd
    besARGEND
    ret = sqlite3_prepare_v2(db,sqlcmd,strlen(sqlcmd)+1,&stmt,NULL);
    besRETURN_POINTER(stmt)
besEND

/**
=section ROW
=H Retrieve the next Row from a database file
*/
besFUNCTION(sql3_row)
     sqlite3_stmt *stmt;
     int i;

     besARGUMENTS("p")
          &stmt
     besARGEND

     i = sqlite3_step(stmt);
     besRETURN_LONG(i)

besEND

/**
=section ROW_VALUE
=H Retrieve the value at position y in database row
*/
besFUNCTION(sql3_row_value)
     sqlite3_stmt *stmt;
     const char* cur_column_text;
     int i;

     besARGUMENTS("pi")
          &stmt,&i
     besARGEND

     cur_column_text = sqlite3_column_text(stmt,i);
     besRETURN_STRING(cur_column_text)

besEND

/**
=section COLUMN_COUNT
=H Retrieve number of columns in table
*/
besFUNCTION(sql3_column_count)
     sqlite3_stmt *stmt;
     int i;

     besARGUMENTS("p")
          &stmt
     besARGEND

     i = sqlite3_column_count(stmt);
     besRETURN_LONG(i)

besEND

/**
=section COLUMN_NAME
=H Retrieve column name at pos i in table
*/
besFUNCTION(sql3_column_name)
     sqlite3_stmt *stmt;
     const char* cur_column_name;
     int i;

     besARGUMENTS("pi")
          &stmt,&i
     besARGEND

     cur_column_name = sqlite3_column_name(stmt,i);
     besRETURN_STRING(cur_column_name)

besEND

/**
=section FINALIZE
=H Finalize an sqlite3 database file
*/
besFUNCTION(sql3_finalize)
     sqlite3_stmt *stmt;
     int i;

     besARGUMENTS("p")
          &stmt
     besARGEND

     i = sqlite3_finalize(stmt);
     besRETURN_LONG(i)
besEND

/**
=section VERSION
=H Retrieve sqlite3 version string
*/
besFUNCTION(sql3_version)
    const char *ver = sqlite3_libversion();
    besRETURN_STRING(ver)
besEND

/**
=section ErrorCode
=H Returns status code for sqlite function call
*/
besFUNCTION(sql3_errorcode)
     sqlite3 *db;
     int i;

     besARGUMENTS("p")
          &db
     besARGEND

     i = sqlite3_errcode(db);
     besRETURN_LONG(i)
besEND

/**
=section ErrorMsg
=H Returns text that describes the error
*/
besFUNCTION(sql3_errormsg)
     sqlite3 *db;
     const char *errString;

     besARGUMENTS("p")
          &db
     besARGEND

     errString = sqlite3_errmsg(db);
     besRETURN_STRING(errString)
besEND

/**
=section FETCHHASH
=H Returns Hash containing row contents in Key/Value pair
*/
besFUNCTION(sql3_fetchhash)
    VARIABLE Argument;
    unsigned long __refcount_;
    sqlite3_stmt *stmt;
    LEFTVALUE Lval;
    unsigned int numfields;
    int i;
    const char* cur_column_name;
    const char* cur_column_text;
    
     besARGUMENTS("p")
          &stmt
     besARGEND
    
     Argument = besARGUMENT(2);

     besLEFTVALUE(Argument,Lval);
     if( ! Lval )return 0x00081001;
    
     besRELEASE(*Lval);
     *Lval = NULL;
    
    
     numfields = sqlite3_column_count(stmt);
     if( numfields == 0 ){
        besRETURNVALUE = NULL;
        return COMMAND_ERROR_SUCCESS;
     }
    
     *Lval = besNEWARRAY(0,2*numfields-1);
     if( *Lval == NULL )return COMMAND_ERROR_MEMORY_LOW;
    
     for( i= 0 ; ((unsigned)i) < numfields ; i++ ) {
        cur_column_name = sqlite3_column_name(stmt,i);
        cur_column_text = sqlite3_column_text(stmt,i);
        ARRAYVALUE(*Lval,2*i) = besNEWSTRING(strlen(cur_column_name));
        if( ARRAYVALUE(*Lval,2*i) == NULL )return COMMAND_ERROR_MEMORY_LOW;
        memcpy(STRINGVALUE(ARRAYVALUE(*Lval,2*i)),cur_column_name, strlen(cur_column_name));
        
        ARRAYVALUE(*Lval,2*i+1) = besNEWSTRING(strlen(cur_column_text));
        if( ARRAYVALUE(*Lval,2*i+1) == NULL )return COMMAND_ERROR_MEMORY_LOW;
        memcpy(STRINGVALUE(ARRAYVALUE(*Lval,2*i+1)),cur_column_text,strlen(cur_column_text));
     }
    
     besALLOC_RETURN_LONG;
     LONGVALUE(besRETURNVALUE) = -1;
besEND

/**
=section FETCHARRAY
=H Returns Array containing row contents
*/
besFUNCTION(sql3_fetcharray)
    VARIABLE Argument;
    unsigned long __refcount_;
    sqlite3_stmt *stmt;
    LEFTVALUE Lval;
    unsigned int numfields;
    int i;
    const char* cur_column_text;
    
     besARGUMENTS("p")
          &stmt
     besARGEND

     Argument = besARGUMENT(2);

     besLEFTVALUE(Argument,Lval);
     if( ! Lval )return 0x00081001;
    
     besRELEASE(*Lval);
     *Lval = NULL;

     numfields = sqlite3_column_count(stmt);
     if( numfields == 0 ){
        besRETURNVALUE = NULL;
        return COMMAND_ERROR_SUCCESS;
     }
    
     *Lval = besNEWARRAY(0,numfields-1);
     if( *Lval == NULL )return COMMAND_ERROR_MEMORY_LOW;
    
     for( i= 0 ; ((unsigned)i) < numfields ; i++ ) {
        cur_column_text = sqlite3_column_text(stmt,i);
        
        ARRAYVALUE(*Lval,i) = besNEWSTRING(strlen(cur_column_text));
        if( ARRAYVALUE(*Lval,i) == NULL )return COMMAND_ERROR_MEMORY_LOW;
        memcpy(STRINGVALUE(ARRAYVALUE(*Lval,i)),cur_column_text,strlen(cur_column_text));
     }
    
     besALLOC_RETURN_LONG;
     LONGVALUE(besRETURNVALUE) = -1;
besEND

START_FUNCTION_TABLE(SQLITE_SLFST)
// Ext. module
  EXPORT_MODULE_FUNCTION(versmodu)
  EXPORT_MODULE_FUNCTION(bootmodu)
  EXPORT_MODULE_FUNCTION(finimodu)

// MOUDLE FUNCTIONS
  EXPORT_MODULE_FUNCTION(sql3_open)
  EXPORT_MODULE_FUNCTION(sql3_close)
  EXPORT_MODULE_FUNCTION(sql3_execute)
  EXPORT_MODULE_FUNCTION(sql3_query)
  EXPORT_MODULE_FUNCTION(sql3_row)
  EXPORT_MODULE_FUNCTION(sql3_row_value)
  EXPORT_MODULE_FUNCTION(sql3_column_count)
  EXPORT_MODULE_FUNCTION(sql3_column_name)
  EXPORT_MODULE_FUNCTION(sql3_version)
  EXPORT_MODULE_FUNCTION(sql3_finalize)
  EXPORT_MODULE_FUNCTION(sql3_version)
  EXPORT_MODULE_FUNCTION(sql3_errorcode)
  EXPORT_MODULE_FUNCTION(sql3_errormsg)
  EXPORT_MODULE_FUNCTION(sql3_fetchhash)
  EXPORT_MODULE_FUNCTION(sql3_fetcharray)
END_FUNCTION_TABLE
