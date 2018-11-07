/*
winisapi.h
*/
#ifndef __WINISAPI_H__
#define __WINISAPI_H__ 1
#ifdef  __cplusplus
extern "C" {
#endif
/*FUNDEF*/

static void IsapiStdOutFunction(char Character,
                                LPEXTENSION_CONTROL_BLOCK lpECB);
/*FEDNUF*/
/*FUNDEF*/

DWORD WINAPI HttpExtensionProc(LPEXTENSION_CONTROL_BLOCK lpECB);
/*FEDNUF*/
/*FUNDEF*/

BOOL WINAPI TerminateExtension(DWORD dwFlags);
/*FEDNUF*/
/*FUNDEF*/

BOOL WINAPI  GetExtensionVersion(HSE_VERSION_INFO *pVer);
/*FEDNUF*/
#ifdef __cplusplus
}
#endif
#endif
