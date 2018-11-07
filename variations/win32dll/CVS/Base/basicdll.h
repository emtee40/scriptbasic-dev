/*
basicdll.h
*/
#ifndef __BASICDLL_H__
#define __BASICDLL_H__ 1

#define BAFLG_BINARY 0x00000001
#ifdef WIN32
#define DLL_EXPORT __declspec(dllexport)
#endif

DLL_EXPORT 
int _stdcall basic(char *szInputFile,
                   void *StdinFunction,
                   void *StdouFunction,
                   void *EnvirFunction,
                   void *EmbedPointer,
                   char *CmdLineOptions,
                   unsigned long ulFlag);
#endif
