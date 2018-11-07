/*
setup.h
*/
#ifndef __SETUP_H__
#define __SETUP_H__ 1
#ifdef  __cplusplus
extern "C" {
#endif
/*FUNDEF*/

static int DeleteRegistryKey(HKEY start,
                             char *keyname,
                             char *subkey);
/*FEDNUF*/
/*FUNDEF*/

char *GetSBRegString(char *name);
/*FEDNUF*/
/*FUNDEF*/

DWORD GetSBRegDW(char *name,
                 DWORD *DW);
/*FEDNUF*/
/*FUNDEF*/

int PutRegistryKey(HKEY start,
                   char *keyname,
                   char *name,
                   char *content);
/*FEDNUF*/
/*FUNDEF*/

int PutRegistryEKey(HKEY start,
                   char *keyname,
                   char *name,
                   char *content);
/*FEDNUF*/
/*FUNDEF*/

int PutSBRegString(HKEY start,
                   char *keyname,
                   char *name,
                   char *content);
/*FEDNUF*/
/*FUNDEF*/

int PutSBRegDW(HKEY start,
               char *keyname,
               char *name,
               DWORD DW);
/*FEDNUF*/
/*FUNDEF*/

char *GetRegistryKey(char *keyname,
                     char *name);
/*FEDNUF*/
#ifdef __cplusplus
}
#endif
#endif
