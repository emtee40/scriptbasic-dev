/*
ftpd.h
*/
#ifndef __FTPD_H__
#define __FTPD_H__ 1
#ifdef  __cplusplus
extern "C" {
#endif

#ifdef WIN32
typedef u_short port_t;
#else
#ifndef __DARWIN__
typedef int port_t;
#endif
#define closesocket close
#endif


#define FTPD_PORT 21


#define LISTEN_BACKLOG 200


#define CONCURRENT_SESSIONS 100
#define LINE_MAX_SIZE 1024

typedef struct _ThreadData {
  int                ThreadIndex;      
  int                SocketOpened;     
  SOCKET             msgsock;          
  int                NextFree;         
  void              *pThreadLocalData; 
  THREADHANDLE       T;
  struct sockaddr_in addr;
  char buffer[LINE_MAX_SIZE];
  unsigned char        ClientIP[4];

  unsigned int         cbAvailable;   
  unsigned char       *pszData;      
  
  void                *AppThreadData;
  struct _FtpdThread *pHT;
  } ThreadData, *pThreadData;

typedef struct _FtpdThread {

  
  pThreadData    threads;

  
  int            FirstFreeThread;

  
  MUTEX          mxFirstFreeThread;

  
  int            cThread;

  
  unsigned long  lWaitSec;

  
  unsigned long  lWaitCount;

  
  port_t         port;

  
  int            threadmax;

  
  int            listenmax;

  
  SOCKET         sock;

  int            iState; 
#define STATE_NORMAL 0
#define STATE_SHUT   1 

  MUTEX          mxState; 

  
  void          *AppData;
  } FtpdThread, *pFtpdThread;

/*FUNDEF*/

void InitSignalHandlers();
/*FEDNUF*/
/*FUNDEF*/

int ftpd(int argc,
         char *argv[]);
/*FEDNUF*/
/*FUNDEF*/

pThreadData GetFreeThread(pFtpdThread pHT);
/*FEDNUF*/
/*FUNDEF*/

void ReleaseThreadData(pFtpdThread pHT,
                       int index);
/*FEDNUF*/
/*FUNDEF*/

void HitHandler(void *t);
/*FEDNUF*/
#ifdef __cplusplus
}
#endif
#endif
