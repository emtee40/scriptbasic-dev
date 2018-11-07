/*
FILE: ftpd.c
HEADER: ftpd.h

TO_HEADER:

#ifdef WIN32
typedef u_short port_t;
#else
#ifndef __DARWIN__
typedef int port_t;
#endif
#define closesocket close
#endif

// the default port to listen
#define FTPD_PORT 21

// the listen backlog that we pass to the operating system
#define LISTEN_BACKLOG 200

// the maximum number of sessions that we handle
#define CONCURRENT_SESSIONS 100
#define LINE_MAX_SIZE 1024
// data that we maintain about each FtpProc thread
typedef struct _ThreadData {
  int                ThreadIndex;      // the index of this element
  int                SocketOpened;     // true when the socket is opened
  SOCKET             msgsock;          // the messaging socket
  int                NextFree;         // the next free thread data
  void              *pThreadLocalData; // pointer to local data that the thread may use
  THREADHANDLE       T;
  struct sockaddr_in addr;
  char buffer[LINE_MAX_SIZE];
  unsigned char        ClientIP[4];

  unsigned int         cbAvailable;   // Available number of bytes
  unsigned char       *pszData;      // Pointer to cbAvailable bytes
  // the application thread data pointer
  void                *AppThreadData;
  struct _FtpdThread *pHT;
  } ThreadData, *pThreadData;

typedef struct _FtpdThread {

  // This is an array of thread data. They are linked together so that we have a list of free threads.
  pThreadData    threads;

  // This variable indexes the first free thread or has the value -1 if there are no free threads
  int            FirstFreeThread;

  // Mutex to lock the variable FirstFreeThread
  MUTEX          mxFirstFreeThread;

  // The number of threads running
  int            cThread;

  // the number of seconds to wait for the threads to stop during shut down
  unsigned long  lWaitSec;

  // the number of times to wait lWaitSec seconds before forcefully exiting
  unsigned long  lWaitCount;

  // The port array that we are listening on
  port_t         port;

  // The maximum number of threads that we start.
  int            threadmax;

  // The listen backlog passed as parameter to listen.
  int            listenmax;

  // This is a global variable so that the ftpproc shutdown can close it.
  SOCKET         sock;// This is a global variable so that the ftpproc shutdown can close it.

  int            iState; // State of the server.
#define STATE_NORMAL 0
#define STATE_SHUT   1 // The server is shutting down.

  MUTEX          mxState; // mutex to lock the state

  // the application  data pointer
  void          *AppData;
  } FtpdThread, *pFtpdThread;

*/

#ifndef __NO_SOCKETS__

#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <winsock2.h>
#include <winbase.h>
#define SLEEPER 1000
#else
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#define Sleep sleep
#define SLEEPER 1
#endif

#include "thread.h"
#include "filesys.h"
#include "ftpd.h"
#include "getopt.h"

#define MAXBINDTRIAL 1200 /* so many times do we try the bind*/
#define BINDSLEEP    1   /* so many seconds we sleep after an unsuccessful bind */



#ifdef WIN32
/* This is a total DUMMY under Windows NT */
void InitSignalHandlers(){}
#else
void SEGV_handle(int i) {
    char fname[2000];
    int pid;
    pid=getpid();
    fclose(fopen(fname,"w+"));
    sleep(1000000);
}

/*POD
=section InitSignalHandlers
=H Initialize the signal handlers under UNIX

This function is called under UNIX to initialize the signal handlers.
This makes the application ignoring if the socket pipe is broken by the
client application.

Under Win32 there is a dummy function doing nothing in place of this function.

/*FUNCTION*/
void InitSignalHandlers(
  ){
/*noverbatim
CUT*/
  signal(SIGPIPE,SIG_IGN);
  signal(SIGSEGV,SEGV_handle); 
 
  }

#endif


/*POD
=section ftpd
=H ftpd

/*FUNCTION*/
int ftpd(int argc,
         char *argv[]
){
/*noverbatim
CUT*/
  int addr_size;
  int i;
  int length;
  struct sockaddr_in server;
  pThreadData ThisThread;
  FtpdThread HT;
  int iState;
  int cThread;
  unsigned long iL;
#ifdef WIN32
  WORD wVersionRequested;
  WSADATA wsaData;
  int err;
#else
  int cpid;
#endif


#ifdef WIN32
  wVersionRequested = MAKEWORD( 2, 2 );
  err = WSAStartup( wVersionRequested, &wsaData );
  if( err != 0 ){
    fprintf(stderr,"Error initializing the Windows Socket subsystem\n");
    exit(1);
    }
#endif
  HT.port = FTPD_PORT;
  HT.threadmax = CONCURRENT_SESSIONS;
  HT.listenmax = LISTEN_BACKLOG;

  /* init the signal handlerts to SIG_IGN so that a brokern pipe does not kill us */
  InitSignalHandlers();

//
//  /* This is just a pointer that we guarantee not to be altered. */
//  HT.AppData = NULL;
//  /* AppInit should return zero on success. */
//  if( i=AppInit(argc,argv,&HT,&(HT.AppData)) ){
//    fprintf(stderr,"AppInit returned %d\n",i);
//    exit(i);
//    }

  HT.sock = socket(AF_INET, SOCK_STREAM, 0);
  i=1;
  setsockopt(HT.sock, SOL_SOCKET, SO_REUSEADDR, (char *)(&i),
                   sizeof(i));
  if( HT.sock < 0 ){
    fprintf(stderr, "Error at socket");
    exit(1);
    }
  server.sin_family = AF_INET;   
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  server.sin_port = htons(HT.port);
  for( i=0 ; i<MAXBINDTRIAL ; i++ ){
    if( ! bind(HT.sock, (struct sockaddr *)&server, sizeof(server)) )break;
    if( i == MAXBINDTRIAL-1 ){
      fprintf(stderr, "\nError at bind.");
      exit(1);
      }
    if( i == 0 )fprintf(stderr,"Bind failed, retrying at most %d times\n.",MAXBINDTRIAL);
    else fprintf(stderr,".");
    if( i%40 == 39 )fprintf(stderr,"\n");
    Sleep(BINDSLEEP);
    }
  if( i )fprintf(stderr,"\nBind finally successful after %d trials\n",i);
  
  length = sizeof(server);
  if( getsockname(HT.sock, (struct sockaddr *)&server, &length) ){ 
    fprintf(stderr, "Error at getsockname.");
    exit(1);
    }
    
  listen(HT.sock, HT.listenmax);

  HT.iState = STATE_NORMAL;

//  if( i=AppStart(&(HT.AppData)) ){
//    fprintf(stderr,"Appstart returned %d\n",i);
//    exit(i);
//    }

  HT.threads = (pThreadData)malloc(HT.threadmax*sizeof(ThreadData));
  if( HT.threads == NULL ){
    fprintf(stderr,"Not enough memory\n");
    exit(1);
    }

  /* Initialize the list of thread data
  */
  for( i=0 ; i < HT.threadmax ; i++ ){
    HT.threads[i].ThreadIndex = i;
    HT.threads[i].NextFree   = i+1;
    HT.threads[i].pHT        = &HT;
    }
  HT.cThread = 0;
  /* make it dead end */
  HT.threads[HT.threadmax-1].NextFree = -1;
  HT.FirstFreeThread = 0;
  thread_InitMutex(&(HT.mxFirstFreeThread));

  while(1){
    ThisThread = GetFreeThread(&HT);
    do{
      addr_size=sizeof(struct sockaddr);
      ThisThread->msgsock = accept(HT.sock,
                                   (struct sockaddr *)&(ThisThread->addr),
                                   &addr_size);
       }while(
#ifdef WIN32
               ThisThread->msgsock == INVALID_SOCKET
#else
               ThisThread->msgsock <= 0
#endif
               );
    thread_LockMutex(&(HT.mxState));
    iState = HT.iState;
    thread_UnlockMutex(&(HT.mxState));
    if( iState == STATE_SHUT ){/* we have to stop */
      /* wait for all threads to stop */
      for( iL = 0 ; iL < HT.lWaitCount ; iL++ ){
        thread_LockMutex(&(HT.mxFirstFreeThread));
        cThread = HT.cThread;
        thread_UnlockMutex(&(HT.mxFirstFreeThread));
        if( cThread == 1 )break;
        Sleep(HT.lWaitSec*SLEEPER);
        }
      return 0;
      }
    ThisThread->SocketOpened = 1;
    thread_CreateThread(&(ThisThread->T),HitHandler,ThisThread);
    }
  /* we never get here */
  return 0;
  }

/*FUNCTION*/
pThreadData GetFreeThread(pFtpdThread pHT
  ){
  pThreadData t;
  /* get exclusive access to the first free thread index */
  thread_LockMutex(&(pHT->mxFirstFreeThread));
  /* while there is no free thread wait a second and try again */
  while( pHT->FirstFreeThread == -1 ){
    thread_UnlockMutex(&(pHT->mxFirstFreeThread));
    Sleep(1*SLEEPER);
    thread_LockMutex(&(pHT->mxFirstFreeThread));
    }
  t = pHT->threads+pHT->FirstFreeThread;
  pHT->FirstFreeThread = pHT->threads[pHT->FirstFreeThread].NextFree;
  pHT->cThread++;
  thread_UnlockMutex(&(pHT->mxFirstFreeThread));

  return t;
  }

/*FUNCTION*/
void ReleaseThreadData(pFtpdThread pHT,
                       int index
  ){
  thread_LockMutex(&(pHT->mxFirstFreeThread));
  pHT->threads[index].NextFree = pHT->FirstFreeThread;
  pHT->FirstFreeThread = index;
  pHT->cThread--;
  thread_UnlockMutex(&(pHT->mxFirstFreeThread));
  }

#define MSPACE(x) while( *x && isspace(*x)) x++
#define SSPACE(x) if( *x && isspace(*x)) x++


/*FUNCTION*/
void HitHandler(void *t
  ){
  pThreadData ThisThread;
  int i,cbBuffer,cbCharsRead,cbCharsReadTotal;
  char *Buffer;
  fd_set readfds;
  struct timeval timeout;

#define ABORT_CONNECTION goto FINISH_CONNECTION;

  ThisThread = (pThreadData)t;

  ThisThread->AppThreadData = NULL;

  Buffer = ThisThread->buffer;
  cbBuffer = LINE_MAX_SIZE;

#ifdef WIN32
  ThisThread->ClientIP[0] = ThisThread->addr.sin_addr.S_un.S_un_b.s_b1;
  ThisThread->ClientIP[1] = ThisThread->addr.sin_addr.S_un.S_un_b.s_b2;
  ThisThread->ClientIP[2] = ThisThread->addr.sin_addr.S_un.S_un_b.s_b3;
  ThisThread->ClientIP[3] = ThisThread->addr.sin_addr.S_un.S_un_b.s_b4;
#else
  memcpy(ThisThread->ClientIP,&(ThisThread->addr.sin_addr.s_addr),4);
#endif

  send(ThisThread->msgsock,"220 hello\r\n",strlen("220 hello\r\n"),0);

  cbCharsReadTotal = 0;
  while(1){
    FD_ZERO(&readfds);
    FD_SET(ThisThread->msgsock,&readfds);
    timeout.tv_sec=60;
    timeout.tv_usec=0;
    i = select(FD_SETSIZE,&readfds,NULL,NULL,&timeout);
    if( i == 0 )ABORT_CONNECTION;
    cbCharsRead = recv(ThisThread->msgsock,Buffer,cbBuffer,0);
    }
FINISH_CONNECTION:
  if( ThisThread->SocketOpened ){
    closesocket(ThisThread->msgsock);
    ThisThread->SocketOpened = 0;
    }
  ReleaseThreadData(ThisThread->pHT,ThisThread->ThreadIndex);
  thread_ExitThread();
  }

void main(int argc, char *argv[]){
  ftpd(argc,argv);
  }


#endif /* __NO_SOCKETS__ */
