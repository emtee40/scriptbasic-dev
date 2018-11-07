/* 

FILE:    setup.c
DATE:    Aug 2002
AUTHOR:  Peter Verhas
LICENCE: GPL

CONTENT:
 Install-Program for ScriptBasic

This program was written using the setup code of yabasic
at http://www.yabasic.de

*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <shlobj.h>
#include <shellapi.h>
#include <commctrl.h>
#include <ole2.h>
#include <direct.h>
#include <sys/stat.h>
#include <process.h>

#include <zlib.h>
#include "../filesys.h"

#include "resource.h"

#define VERSION_TEXT "2.0.0"
#define MAJOR 2
#define MINOR 0
#define BUILD 0

// the number of KB free disk space needed to install ScriptBasic
#define KBNEEDED 8000

#define DEFAULT_PATH "C:\\ScriptBasic\\"
/* headings for messageboxes */
#define INSTALL_HEADING " Install ScriptBasic !"
#define REMOVE_HEADING " Remove ScriptBasic !"
#define SOFT              "SOFTWARE\\"

/* shortcuts for registry */
#define LOCAL             HKEY_LOCAL_MACHINE
#define ROOT              HKEY_CLASSES_ROOT
#define SOFT              "SOFTWARE\\"
#define UNINSTALL         "SOFTWARE\\MICROSOFT\\WINDOWS\\CURRENTVERSION\\UNINSTALL\\"

/* the compressed file that contains all the files to install */
#define GZFILE            "sbcab.bin"

/* operationmodes for My...() functions */
#define INSTALL 1
#define REMOVE  2

/* defines for files() */
#define RESET 1
#define NEXT  2

#define BASIC_NAME "ScriptBasic"
#define BASIC_EXE "scriba.exe"
#define BASIC_EXTENSION ".sb"
#define BASIC_VERSION "2.0"
#define BASIC_BUILD "0"
#define BASIC_ICON "scriba.ico"
#define BASDOC_ICON "scribadoc.ico"
#define BASIC_README "readme.txt"
#define BASIC_LICENSE "copying.txt"
#define BASIC_SETUP "setup.exe"
#define BASIC_LOG "scriba.log"

#define DEFAULTFONT "swiss13"
#define DEFAULTGEOMETRY "+10+10"

/* shortcut for standard Message Box Style */
#define MB_STYLE     MB_OK|MB_SYSTEMMODAL|MB_ICONINFORMATION

// standard buffer length that should be enough
#define SSLEN 1024
int total_progress;      /* number of steps to advance progress counter */

int GlobalSuccessFlag = 1;

void progress(char *msg);

char *pszInstallPath;
HINSTANCE this_instance; /* instance */
char *temppath;          /* path to store temporary files */
char logs[10000];        /* string to compose log-message */
int install;
char *currentpath;       /* current path */
int cancel;
char string[SSLEN];
char logfilename[SSLEN];
int progress_wait;

DWORD dwMajor,dwMinor,dwBuild;


char *app(char *trail) /* append trail to pszInstallPath */
{
  char *result;
  int i,t;
  
  i=(int)strlen(pszInstallPath);
  t=(int)strlen(trail);
  
  result=malloc(i+t+1);
  memcpy(result,pszInstallPath,i);
  memcpy(result+i,trail,t);
  result[t+i]='\0';
  
  return result;
}


int failReport(char *key,
                      char *action){
  char logs[SSLEN];
  int Q;
  void logit();

  sprintf(logs,"--Fail: SETUP was not able to %s the registry value \"%s\"\n",action,key);
  logit(logs);
  sprintf(logs,

"SETUP was not able to %s the registry value\n\n%s\n\n"
"Did you start SETUP.EXE with Administrator privilege?\n\n"
"If you started SETUP.EXE as a normal user the installation\n"
"will be partial, without modifying the system parameters.\n"
"If you started setup as an administrator and you still see\n"
"this message, then check that the registry key exists,\n"
"and the user account you use to run setup has read and\n"
"write access to it.\n"
"\n"
"Press \"Cancel\" if you want to stop the installation.\n"
"Press \"Try Again\" after you modified security seetings to retry.\n"
"Press \"Continue\" to ignore this error and skip this step.\n" 
             ,action,key);
  Q =
  MessageBoxEx(NULL,
                logs,
                "WARNING: Registry access error",
                MB_CANCELTRYCONTINUE | MB_ICONWARNING,
                0);
  if( Q == IDCANCEL ){
    sprintf(logs,"--Fail: Installation was aborted on user request.\n");
    return Q;
    }
  return Q;
  }

/*POD
=H Delete keys from the registry

This function deletes keys from the registry

Arguments:

=itemize
=item T<start> one of the predefined key (e.g. HKEY_CLASSES_ROOT)
=item T<keyname> path to the key to delete
=item T<subkey> subkey to delete 
=noitemize
/*FUNCTION*/
static int DeleteRegistryKey(HKEY start,
                             char *keyname,
                             char *subkey
  ){
/*noverbatim
CUT*/
  HKEY key;
  
  char logs[SSLEN];
  int Q;

RETRY:
  if (RegOpenKeyEx(start,keyname,0,KEY_ALL_ACCESS,&key)!=ERROR_SUCCESS) 
    goto FAIL_1;
  
  if(RegDeleteKey(key,subkey)!=ERROR_SUCCESS){
    RegCloseKey(key);
FAIL_1:
    sprintf(logs, "%s\\%s\\%s",
               (start == LOCAL ? "HKEY_LOCAL_MACHINE" : "HKEY_CLASSES_ROOT"),keyname,subkey
           ); 
    Q = failReport(logs,"delete");
    if( Q == IDTRYAGAIN )goto RETRY;
    if( Q == IDCONTINUE ){
      GlobalSuccessFlag = 0;
      return TRUE;
      }
    return FALSE;
    }
  RegCloseKey(key);
  return TRUE;
}

/*POD
=H Get string value from the ScriptBasic registry key

This function gets a string value from the registry

=verbatim
HKEY_LOCAL_MACHINE\SOFTWARE\ScriptBasic\'name'
=noverbatim

If the value is non existent or is not a string then it returns T<NULL>.
/*FUNCTION*/
char *GetSBRegString(char *name
  ){
/*noverbatim
CUT*/
  static char *keyname="SOFTWARE\\ScriptBasic";
  HKEY  hkey;
  DWORD cbData,dwType;
  char  sData[SSLEN];
  char  xData[SSLEN];

  if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,keyname,0,KEY_READ,&hkey) != ERROR_SUCCESS) return NULL;

  cbData = SSLEN;
  *sData = (char)0;
  if (RegQueryValueEx(hkey,name,NULL,&dwType,sData,&cbData) != ERROR_SUCCESS) return NULL;

  if( dwType != REG_SZ && dwType != REG_EXPAND_SZ )return NULL;

  if( dwType == REG_EXPAND_SZ ){
    ExpandEnvironmentStrings(sData,xData,cbData);
    strcpy(sData,xData);
    dwType = REG_SZ;
    }
  RegCloseKey(hkey);
  return strdup(sData);
  }

/*POD
=H Get DWORD value from the ScriptBasic registry key

This function gets a DWORD value from the registry

=verbatim
HKEY_LOCAL_MACHINE\SOFTWARE\ScriptBasic\'name'
=noverbatim

If the value is non existent or is not a DWORD then the function returns -1 otherwise
it returns zero. The DWORD value is returned in the second argument.

If error happens T<DW> is set to be zero. This also can be used to check error.
/*FUNCTION*/
DWORD GetSBRegDW(char *name,
                 DWORD *DW
  ){
/*noverbatim
CUT*/
  static char *keyname="SOFTWARE\\ScriptBasic";
  HKEY  hkey;
  DWORD cbData,dwType;
  DWORD dwDW;

  *DW = 0;

  if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,keyname,0,KEY_READ,&hkey) != ERROR_SUCCESS) return -1;

  cbData = sizeof(DWORD);
  if (RegQueryValueEx(hkey,name,NULL,&dwType,(LPBYTE)&dwDW,&cbData) != ERROR_SUCCESS) return -1;

  if( dwType != REG_DWORD )return -1;
  RegCloseKey(hkey);

  *DW = dwDW;
  return 0;
  }

/*POD
=H Put keys into registry

put keys into Registry 

Arguments:

=itemize
=item T<start>   : one of the predefined key (e.g. HKEY_CLASSES_ROOT)
=item T<keyname> : path to the key to create
=item T<name>    : subkey to create
=item T<content> : it's content
=noitemize
/*FUNCTION*/
int PutRegistryKey(HKEY start,
                   char *keyname,
                   char *name,
                   char *content
){
/*noverbatim
CUT*/
  HKEY key;
  DWORD status;
  char logs[SSLEN];
  int Q;

RETRY:
  RegCreateKeyEx(start,keyname,0,"",
    0,KEY_ALL_ACCESS,NULL,&key,&status);
  if (RegSetValueEx(key,name,0,REG_SZ,
    content,(DWORD)strlen(content)+1)!=ERROR_SUCCESS) {
    sprintf(logs, "%s\\%s\\%s",
               (start == LOCAL ? "HKEY_LOCAL_MACHINE" : "HKEY_CLASSES_ROOT"),keyname,name
           ); 
    Q = failReport(logs,"write");
    if( Q == IDTRYAGAIN )goto RETRY;
    if( Q == IDCONTINUE ){
      GlobalSuccessFlag = 0;
      return TRUE;
      }
    return FALSE;
  }
  return TRUE;
}

/*POD
=H Put expandable keys into registry

put keys into Registry 

Arguments:

=itemize
=item T<start>   : one of the predefined key (e.g. HKEY_CLASSES_ROOT)
=item T<keyname> : path to the key to create
=item T<name>    : subkey to create
=item T<content> : it's content
=noitemize
/*FUNCTION*/
int PutRegistryEKey(HKEY start,
                   char *keyname,
                   char *name,
                   char *content
){
/*noverbatim

This function puts the string into the registry as 
CUT*/
  HKEY key;
  DWORD status;
  char logs[SSLEN];
  int Q;

RETRY:
  RegCreateKeyEx(start,keyname,0,"",
    0,KEY_ALL_ACCESS,NULL,&key,&status);
  if (RegSetValueEx(key,name,0,REG_EXPAND_SZ,
    content,(DWORD)strlen(content)+1)!=ERROR_SUCCESS) {
    sprintf(logs, "%s\\%s\\%s",
               (start == LOCAL ? "HKEY_LOCAL_MACHINE" : "HKEY_CLASSES_ROOT"),keyname,name
           ); 
    Q = failReport(logs,"write");
    if( Q == IDTRYAGAIN )goto RETRY;
    if( Q == IDCONTINUE ){
      GlobalSuccessFlag = 0;
      return TRUE;
      }
    return FALSE;
  }
  return TRUE;
}

/*POD
=H Put keys into registry

put keys into Registry 

Arguments:

=itemize
=item T<start>   : one of the predefined key (e.g. HKEY_CLASSES_ROOT)
=item T<keyname> : path to the key to create
=item T<name>    : subkey to create
=item T<content> : it's content
=noitemize
/*FUNCTION*/
int PutSBRegString(HKEY start,
                   char *keyname,
                   char *name,
                   char *content
){
/*noverbatim
CUT*/
  HKEY key;
  DWORD status;
  char logs[SSLEN];
  int Q;

RETRY:
  RegCreateKeyEx(start,keyname,0,"",
    0,KEY_ALL_ACCESS,NULL,&key,&status);
  if (RegSetValueEx(key,name,0,REG_SZ,
    content,(DWORD)strlen(content)+1)!=ERROR_SUCCESS) {
    sprintf(logs, "%s\\%s\\%s",
               (start == LOCAL ? "HKEY_LOCAL_MACHINE" : "HKEY_CLASSES_ROOT"),keyname,name
           ); 
    Q = failReport(logs,"write");
    if( Q == IDTRYAGAIN )goto RETRY;
    if( Q == IDCONTINUE ){
      GlobalSuccessFlag = 0;
      return TRUE;
      }
    return FALSE;
  }
  return TRUE;
}

/*POD
=H Put keys into registry

put keys into Registry 

Arguments:

=itemize
=item T<start>   : one of the predefined key (e.g. HKEY_CLASSES_ROOT)
=item T<keyname> : path to the key to create
=item T<name>    : subkey to create
=item T<content> : it's content
=noitemize
/*FUNCTION*/
int PutSBRegDW(HKEY start,
               char *keyname,
               char *name,
               DWORD DW
){
/*noverbatim
CUT*/
  HKEY key;
  DWORD status;
  char logs[SSLEN];
  int Q;

RETRY:
  RegCreateKeyEx(start,keyname,0,"",
    0,KEY_ALL_ACCESS,NULL,&key,&status);
  if (RegSetValueEx(key,name,0,REG_DWORD,
    (BYTE *)&DW,sizeof(DWORD))!=ERROR_SUCCESS) {
    sprintf(logs, "%s\\%s\\%s",
               (start == LOCAL ? "HKEY_LOCAL_MACHINE" : "HKEY_CLASSES_ROOT"),keyname,name
           ); 
    Q = failReport(logs,"write");
    if( Q == IDTRYAGAIN )goto RETRY;
    if( Q == IDCONTINUE ){
      GlobalSuccessFlag = 0;
      return TRUE;
      }
    return FALSE;
  }
  return TRUE;
}
/*POD
=H Get keys from registry
/*FUNCTION*/
char *GetRegistryKey(char *keyname,
                     char *name
  ){
/*noverbatim
CUT*/
  HKEY key;
  char value[SSLEN];
  DWORD n;
  
  char logs[SSLEN];
  int Q;

RETRY:
  if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,keyname,0,KEY_ALL_ACCESS,&key)!=ERROR_SUCCESS)goto FAIL_1;
  n=SSLEN;
  value[0]='\0';
  if (RegQueryValueEx(key,name,NULL,NULL,value,&n)!=ERROR_SUCCESS) goto FAIL_1;
  value[n]='\0';
  RegCloseKey(key);
  return strdup(value);

FAIL_1:
    sprintf(logs, "%s\\%s",keyname,name); 
    Q = failReport(logs,"write");
    if( Q == IDTRYAGAIN )goto RETRY;
    if( Q == IDCONTINUE ){
      GlobalSuccessFlag = 0;
      return strdup("");
      }
    return NULL;

}

int InstallQuestionYN(char *pszText)
/* wrapper for MessageBox() */
{
  
  return MessageBoxEx(NULL,
                      pszText,
                      "ScriptBasic Install",
                      MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL,
                      MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US)) == IDYES;
}

char *brushup(char *path) /* change to lower case, add slash */
{
  int i;
  char buf[SSLEN];
  
  if (path==NULL) return NULL;
  
  i=0;
  do {
    buf[i]=tolower(path[i]); 
    if (buf[i]=='/') buf[i]='\\';
    i++;
  }while(path[i]!='\0' && isprint(path[i]));
  
  buf[i]='\0';
  
  if (buf[i-1]!='\\') {
    buf[i]='\\';
    buf[i+1]='\0';
  }
  
  return strdup(buf);
}      

void brushupinline(char *path) /* change to lower case, add slash */
{
  int i,j,pch;
  
  if (path==NULL) return;
  
  i=j=0;
  pch=0;
  do {
    path[i]=tolower(path[j]); 
    if (path[i]=='/')path[i]='\\';
    if( pch != '\\' || path[i] != '\\' )i++;
    pch = path[j];
    j++;
  }while( path[j] != '\0' && isprint(path[j]) );
  
  path[i]='\0';
  return ;
}      

void logit(char *text) 
/* 
write text to log-file 
text : text to write
*/
{
  static FILE *log=NULL;   /* file for logging */
  SYSTEMTIME time;         /* time */
  static int oldtime;
  
  /* open log-file */
  if (!log) {
    sprintf(logfilename,"%s%s",temppath,"scriba.log");
    log=fopen(logfilename,"w");
    GetSystemTime(&time);
    if (log) {
      fprintf(log,"\n\n\n---------------------------------------------------\n"
        "Starting installation-log, "
        "hr=%d, min=%d, sec=%d, msec=%d.\n",
        time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
      oldtime=GetCurrentTime();
    }
  }
  
  if (log) {
    GetSystemTime(&time);
    if (GetCurrentTime()-oldtime>10000) {
      fprintf(log,"--Timestamp: hr=%d, min=%d, sec=%d, msec=%d\n",
        time.wHour,time.wMinute,time.wSecond,time.wMilliseconds);
      oldtime=GetCurrentTime();
    }
    if (text) {
      if (strncmp(text,"--",2)) fprintf(log,"  ");
      while(*text!='\0') {
        fputc(*text,log);
        if (*text=='\n' && *(text+1)!='\0') fprintf(log,"  ");
        text++;
      }
    }
    else {  /* not text ... */
      fprintf(log,"Closing installation-log.");
      fflush(log);
      fclose(log);
      log = NULL; // not to close it twice
    }
  }
  if (log) fflush(log);
}

int MyMessage(HWND handle,LPCSTR text,LPCSTR title,UINT style)
/* wrapper for MessageBox() */
{
  
  sprintf(logs,"--Message box: '%s'\n",text);
  logit(logs);
  
  return MessageBoxEx(handle,text,title,style,
    MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US));
}

/* shortcuts for end-message */
#define INSTALL_CANCELLED 1
#define INSTALL_ABORTED   2
#define INSTALL_SUCCESS   3
#define INSTALL_FAILURE   4
#define REMOVE_SUCCESS    6
#define REMOVE_FAILURE    7
#define REMOVE_CANCELLED  8
#define SILENT            9
#define INSTALL_PARTIAL  10

void end(int m) { /* display message and terminate */
  char *msg;
  int ret;
  
  switch(m) {
  case INSTALL_CANCELLED:
    msg="Okay, installation cancelled.\n"
      "No garbage has been left.";
    ret=FALSE;
    break;
  case INSTALL_FAILURE:
    msg="Installation failed.\n"
      "Some garbage has been left in the system.\n"
      "To clean it up, you better remove ScriptBasic.";
    ret=FALSE;
    break;
  case INSTALL_ABORTED:
    msg="Installation aborted.\n"
      "Some garbage has been left in the system !\n"
      "To clean it up, you better remove ScriptBasic.";
    ret=FALSE;
    break;
  case INSTALL_SUCCESS:
    progress("Install complete");
    msg="Installation completed successfully !\n\n"
        "You may now start writing ScriptBasic programs.\n\n"
        "Note that the PATH was altered to contain the\n"
        "ScriptBasic binary directory, thus you can start\n"
        "any BASIC program from the command line typing:\n\n"
        "    scriba program_name\n\n"
        "or just typing:\n\n"
        "    program_name.sb\n\n"
        "or just\n\n"
        "    program_name\n\n"
        "To have this effect first you have to log out and\n"
        "log in again. There is no need to reboot the machine.\n"
       
    ;
    ret=TRUE;
    break;
  case INSTALL_PARTIAL:
    progress("Install complete");
    msg="Installation completed with some errors!\n\n"
        "You may now start writing ScriptBasic programs.\n\n"
        "Note that the PATH may have been altered to contain the\n"
        "ScriptBasic binary directory, thus you may be successful starting\n"
        "any BASIC program from the command line typing:\n\n"
        "    scriba program_name\n\n"
        "or just typing:\n\n"
        "    program_name.sb\n\n"
        "or just\n\n"
        "    program_name\n\n"
        "To have this effect first you have to log out and\n"
        "log in again. There is no need to reboot the machine.\n\n"
        "The install was partial, thus some features of the install or\n"
        "ScriptBasic itself may not work. It is recommended to run\n"
        "setup.exe from an administrative account.\n"
       
    ;
    ret=TRUE;
    break;
  case REMOVE_SUCCESS:
    msg="ScriptBasic has been removed properly !";
    ret=TRUE;
    break;
  case REMOVE_CANCELLED:
    msg="Cancelled. ScriptBasic has been left intact.";
    ret=FALSE;
    break;
  case REMOVE_FAILURE:
    msg="Couldn't remove ScriptBasic properly !";
    ret=FALSE;
    break;
  case SILENT:
    ret=TRUE;
    goto silent;
  default:
    break;
  }
  MyMessage(NULL,msg,"ScriptBasic Install",MB_OK|MB_SYSTEMMODAL|MB_ICONINFORMATION);
  
silent:
  
  /* close log-file */
  logit(NULL); 
  exit(ret);
  
  return;
}

UINT CALLBACK HookProc(HWND hdl,UINT msg,WPARAM wparam,LPARAM lparam) /* hook for save as */
{
  if (msg==WM_INITDIALOG) {
    RECT rc;
    /* center dialog box */
    GetWindowRect(GetParent(hdl),&rc);
    SetWindowPos(GetParent(hdl),HWND_TOP,
      ((GetSystemMetrics(SM_CXSCREEN)-(rc.right-rc.left))/2),
      ((GetSystemMetrics(SM_CYSCREEN)-(rc.bottom-rc.top))/2),
      0,0,SWP_NOSIZE|SWP_NOACTIVATE|SWP_SHOWWINDOW);
    CommDlg_OpenSave_HideControl(GetParent(hdl),cmb1);
    CommDlg_OpenSave_HideControl(GetParent(hdl),edt1);
    CommDlg_OpenSave_SetControlText(GetParent(hdl),IDOK,"OK");
    CommDlg_OpenSave_SetControlText(GetParent(hdl),IDCANCEL,"Cancel");
    CommDlg_OpenSave_SetControlText(GetParent(hdl),stc4,"Install in: ");
    CommDlg_OpenSave_HideControl(GetParent(hdl),stc3);
    CommDlg_OpenSave_HideControl(GetParent(hdl),stc2);
    return FALSE;
  }		
  return FALSE;
}

BOOL CALLBACK pathdialog(HWND handle,UINT message,
                         WPARAM wparam,LPARAM lparam)
                         /* callback for choice of installation path */
{
  int cmdid;           /* id of command */
  char buf[SSLEN];       /* buffer for installation-path */
  int offset=0;
  char name[SSLEN];       /* buffer for filename */
  OPENFILENAME fname; /* for common dialog */
  int ret;
  
  switch(message) {
  case WM_INITDIALOG:
    { /* center dialog box */
      RECT rc;
      
      GetWindowRect(handle,&rc);
      SetWindowPos(handle,HWND_TOP,
        ((GetSystemMetrics(SM_CXSCREEN)-(rc.right-rc.left))/2),
        ((GetSystemMetrics(SM_CYSCREEN)-(rc.bottom-rc.top))/2),
        0,0,SWP_NOSIZE|SWP_NOACTIVATE|SWP_SHOWWINDOW);
    }
    SetDlgItemText(handle,IDINSTPATH,pszInstallPath);
    return TRUE;
    
  case WM_COMMAND:
    cmdid=LOWORD(wparam);
    switch(cmdid) {
    case IDOK:
      EndDialog(handle,TRUE);
      GetDlgItemText(handle,IDINSTPATH,buf,SSLEN);
      pszInstallPath=strdup(buf);
      return TRUE;
    case IDCANCEL:
      EndDialog(handle,FALSE);
      return TRUE;
    case IDC_BROWSE:
      fname.lStructSize=sizeof(fname);
      fname.hwndOwner=handle;
      fname.hInstance=this_instance;
      fname.lpstrFilter="None\0+.+++\0\0";
      fname.lpstrCustomFilter=NULL; 
      fname.nMaxCustFilter=0;    
      fname.nFilterIndex=0; 
      fname.nMaxFile=SSLEN;
      fname.lpstrFileTitle=NULL;
      fname.nMaxFileTitle=0;
      offset=0;
      GetDlgItemText(handle,IDINSTPATH,buf,SSLEN);
      ret=GetFileAttributes(buf);
      if (ret==0xFFFFFFFF || !(ret & FILE_ATTRIBUTE_DIRECTORY)) {
        GetLogicalDriveStrings(SSLEN,buf);
        offset=(int)strlen(buf)+1;
      }
      fname.lpstrInitialDir=buf+offset;
      strcpy(name,"dummy");
      fname.lpstrFile=name;
      fname.lpstrTitle="Select ScriptBasic's directory"; 
      fname.Flags=OFN_HIDEREADONLY | OFN_EXPLORER | 
        OFN_ENABLEHOOK | OFN_ENABLETEMPLATE | OFN_NOVALIDATE;
      fname.lpstrDefExt=NULL; 
      fname.lCustData=0;
      fname.lpfnHook=(void *)HookProc; 
      fname.lpTemplateName=MAKEINTRESOURCE(IDD_EXPLANATION);
      if (GetOpenFileName(&fname)) {
        name[fname.nFileOffset]='\0';
        SetDlgItemText(handle,IDINSTPATH,name);
      }
      return TRUE;
    default:
      break;
    }
    default:
      break;
  }
  return FALSE;
}

void DeleteFromPath(char *Path){
  char *s;
  int i,j,k;
  char **PathArr;
  char szIDIR[SSLEN];
  char szFullPath[SSLEN];
  int slen;

  sprintf(logs,"--State: Current PATH=%s\n",Path);
  logit(logs);
  /* count the elements in the path */
  i= 0;
  for( s = Path ; *s ; s++ )if( *s == ';' )i++;
  i++; //count the last one
  PathArr = malloc(i*sizeof(char*));
  if( PathArr == NULL )return;

  /* split the path into an array */
  PathArr[0] = Path;
  j = 0;
  for( s = Path ; *s ; s++ ){
    if( *s == ';' ){
      *s = (char)0;
      j++;
      if( j < i )PathArr[j] = s+1;
      }
    }

  /* search for the actual path, it may already be in the path */
  sprintf(string,"%sbin\\",pszInstallPath);
  slen = (int)strlen(string)-1;
  GetFullPathName(string,SSLEN,szIDIR,&s);
  for( j = 0 ; j < i ; j++ ){
    GetFullPathName(PathArr[j],SSLEN,szFullPath,&s);
    // compare the path with and without the terminating backslash
    if( ! stricmp(szFullPath,szIDIR) || !strnicmp(szFullPath,szIDIR,slen) ){
      sprintf(logs,"--Progress: removing >>%s<< from the path\n",PathArr[j]);
      logit(logs);
      PathArr[j] = NULL;
      }
    }
  *szFullPath = (char)0;
  k = 0;
  for( j = 0 ; j < i ; j++ ){
    if( PathArr[j] ){
      if( k )strcat(szFullPath,";");
      k = 1;
      strcat(szFullPath,PathArr[j]);
      }
    }
  strcpy(Path,szFullPath);

  }

void DeleteFromPathEx(char *Path,
                      char *Ext){
  char *s;
  int i,j,k;
  char **PathArr;
  char szFullPath[SSLEN];

  sprintf(logs,"--State: Current PATHEXT=%s\n",Path);
  logit(logs);
  /* count the elements in the path */
  i= 0;
  for( s = Path ; *s ; s++ )if( *s == ';' )i++;
  i++; //count the last one
  PathArr = malloc(i*sizeof(char*));
  if( PathArr == NULL )return;

  /* split the path into an array */
  PathArr[0] = Path;
  j = 0;
  for( s = Path ; *s ; s++ ){
    if( *s == ';' ){
      *s = (char)0;
      j++;
      if( j < i )PathArr[j] = s+1;
      }
    }

  /* search for the actual path, it may already be in the path */
  for( j = 0 ; j < i ; j++ ){
    // compare the path with and without the terminating backslash
    if( ! stricmp(PathArr[j],Ext) ){
      sprintf(logs,"--Progress: removing >>%s<< from the path ext\n",PathArr[j]);
      logit(logs);
      PathArr[j] = NULL;
      }
    }
  *szFullPath = (char)0;
  k = 0;
  for( j = 0 ; j < i ; j++ ){
    if( PathArr[j] ){
      if( k )strcat(szFullPath,";");
      k = 1;
      strcat(szFullPath,PathArr[j]);
      }
    }
  strcpy(Path,szFullPath);

  }

int MyRegs(int mode) /* add or delete entries to or from registry */
{
  int success=TRUE;
  char string[SSLEN];   /* multi-purpose-string */
  char windir[SSLEN];   /* windows-directory */
  char *Path,*PathEx;

  switch(mode) {
  case INSTALL:
    /* registering uninstall program */
    progress("Registering uninstall-program");
    if( ! PutSBRegString(LOCAL,UNINSTALL BASIC_NAME,"DisplayName",BASIC_NAME) ) return 0;
    sprintf(string,"%s%s %s",pszInstallPath,BASIC_SETUP,"remove");
    if( ! PutSBRegString(LOCAL,UNINSTALL BASIC_NAME,"UninstallString",string) ) return 0;
    progress("Adding defaults to registry.");
    /* make changes in registry, put in defaults */
    if( ! PutSBRegString(LOCAL,SOFT BASIC_NAME,"path",pszInstallPath) ) return 0;
    sprintf(string,"%s%s",pszInstallPath,"bin\\scriba.conf");
    if( ! PutSBRegString(LOCAL,SOFT BASIC_NAME,"config",string) ) return 0;
    progress("Registering version in registry");
    if( ! PutSBRegDW(LOCAL,SOFT BASIC_NAME,"major",MAJOR) ) return 0;
    if( ! PutSBRegDW(LOCAL,SOFT BASIC_NAME,"minor",MINOR) ) return 0;
    progress("Registering build number in registry");
    if( ! PutSBRegDW(LOCAL,SOFT BASIC_NAME,"build",BUILD) )return 0;
    
    progress("Registering file extension.");
    /* change context-menu */
    if( ! PutRegistryKey(ROOT,BASIC_EXTENSION,"",BASIC_NAME) ) return 0;
    progress("Registering application type");
    if(  ! PutRegistryKey(ROOT,BASIC_NAME,"","ScriptBasic Program") ) return 0;
    progress("Registering application name");
    if(  ! PutRegistryKey(ROOT,BASIC_NAME"\\DefaultIcon","",app("bin\\"BASIC_ICON)) ) return 0;
    progress("Registering icon");
    if( ! PutRegistryKey(ROOT,BASIC_EXTENSION"\\ShellNew","NullFile","") )return 0;
    if( ! PutRegistryKey(ROOT,BASIC_NAME"\\shell\\open","","&Execute") )return 0;
    if( ! PutRegistryKey(ROOT,BASIC_NAME"\\shell\\open\\command","", app("BIN\\"BASIC_EXE" \"%1 %*\"")) ) return 0;

    Path = GetRegistryKey("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment","Path");
    if( Path == NULL )return 0;
    if( *Path ){
      /* Delete the actual directory from the path if this is there */
      DeleteFromPath(Path);
      // create the new path where the new directory is the first one
      sprintf(string,"%sbin\\;%s",pszInstallPath,Path);
      sprintf(logs,"--Progress: Setting PATH=%s\n",string);
      logit(logs);
      // put the new path into the registry. Note that this comes alive only after logout-login
      if( ! PutRegistryEKey(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment","Path",string) )return 0;
      }
    PathEx = GetRegistryKey("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment","PATHEXT");
    if( *PathEx ){
      /* Delete the actual directory from the path if this is there */
      DeleteFromPathEx(PathEx,".SB");
      // create the new path extension
      sprintf(string,"%s;.SB",PathEx);
      sprintf(logs,"--Progress: Setting PATHEXT=%s\n",string);
      logit(logs);
      // put the new path extension
      PutRegistryKey(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment","PATHEXT",string);
      }
    progress("Linking to root-Menu");
    if( ! PutRegistryKey(ROOT,BASIC_NAME"\\shell\\New","","&Edit") ) return 0;
    GetWindowsDirectory(string,SSLEN);
    sprintf(windir,"%s%s",brushup(string),"Notepad.exe \"%1\"");
    if( ! PutRegistryKey(ROOT,BASIC_NAME"\\shell\\New\\command","",windir)  ) return 0;
    
    return TRUE;
  case REMOVE:
    /* registering uninstall program */
    progress("Removing uninstall registering");
    success=DeleteRegistryKey(LOCAL,UNINSTALL,BASIC_NAME);
    progress("Removing defaults from registry.");
    /* make changes in registry, put in defaults */
    success=DeleteRegistryKey(LOCAL,SOFT, BASIC_NAME) && success;
    
    progress("Deregistering file extension.");
    /* change context-menu */
    success=DeleteRegistryKey(ROOT,BASIC_EXTENSION,"ShellNew") && success;
    success=DeleteRegistryKey(ROOT,BASIC_EXTENSION,"") && success;
    progress("Shell extensions deregistering");
    success=DeleteRegistryKey(ROOT,BASIC_NAME"\\shell\\open","command")&& success;
    success=DeleteRegistryKey(ROOT,BASIC_NAME"\\shell","open") && success;
    success=DeleteRegistryKey(ROOT,BASIC_NAME"\\shell\\new","command")&& success;
    success=DeleteRegistryKey(ROOT,BASIC_NAME"\\shell","new") && success;
    success=DeleteRegistryKey(ROOT,BASIC_NAME,"shell") && success;
    success=DeleteRegistryKey(ROOT,BASIC_NAME,"DefaultIcon") && success;
    success=DeleteRegistryKey(ROOT,BASIC_NAME,"") && success;
    progress("Shell extensions deregistered");

    Path = GetRegistryKey("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment","Path");
    /* Delete the actual directory from the path if this is there */
    DeleteFromPath(Path);
    // create the new path where the new directory is the first one
    sprintf(logs,"--Progress: Setting PATH=%s\n",string);
    logit(logs);
    // put the new path into the registry. Note that this comes alive only after logout-login
    PutRegistryEKey(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment","Path",Path);

    PathEx = GetRegistryKey("SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment","PATHEXT");
    /* Delete the actual directory from the path if this is there */
    DeleteFromPathEx(PathEx,".SB");
    // create the new path where the new directory is the first one
    sprintf(logs,"--Progress: Setting PATHEXT=%s\n",string);
    logit(logs);
    // put the new path into the registry. Note that this comes alive only after logout-login
    PutRegistryKey(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment","PATHEXT",PathEx);
    progress("Unlinking to root-Menu");
    
    return success;
  }
  return success;
}


BOOL CALLBACK progressdialog(HWND handle,UINT message,
                             WPARAM wparam,LPARAM lparam)
                             /* callback for cprogress dialog */
{
  
  switch(message) {
  case WM_INITDIALOG:
    { /* center dialog box */
      RECT rc;
      
      GetWindowRect(handle,&rc);
      SetWindowPos(handle,HWND_TOP,
        ((GetSystemMetrics(SM_CXSCREEN)-(rc.right-rc.left))/2),
        ((GetSystemMetrics(SM_CYSCREEN)-(rc.bottom-rc.top))/2),
        0,0,SWP_NOSIZE|SWP_NOACTIVATE|SWP_SHOWWINDOW);
    }
    return TRUE;
  default:
    break;
  }
  return FALSE;
}


int timerid;
MSG timermsg;
RECT rc;
static int count=0;
static HWND progressbox=NULL;   /* handle of progress dialog */
static HWND hwndPB=NULL; /* handle of progress bar */
char string[SSLEN];             /* multi-purpose string */
int thumb;  // height of scroll bar arrow 

void progress(char *msg) /* show progress */
{
  int i;
  int millsec = 5;
  count++;
  
  /* create progress dialog */
  if (progressbox==NULL) {
    InitCommonControls();
    progressbox=CreateDialog((HANDLE)this_instance,
      MAKEINTRESOURCE(IDD_PROGRESSDIALOG),
      (HANDLE)NULL,
      (DLGPROC)progressdialog);
    GetClientRect(progressbox,&rc); 
    thumb= 8 ;//GetSystemMetrics(SM_CYVSCROLL); 
    hwndPB=CreateWindowEx(WS_EX_TOPMOST,       // extended window style
                          PROGRESS_CLASS,      // registered class name
                          (LPSTR)NULL,         // window name
                          WS_CHILD|WS_VISIBLE|PBS_SMOOTH, // window style
                          rc.left+thumb,       // horizontal position of window
                          rc.bottom- 3*thumb,  // vertical position of window
                          rc.right-2*thumb,    // window width
                          2*thumb,             // window height
                          progressbox,         // handle to parent or owner window
                          (HMENU) 0,           // menu handler
                          this_instance,       // handle to application instance
                          NULL                 // window creation data
                          );
    SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0,total_progress*progress_wait/millsec)); 
    SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0);
    /* actually display the window */
    ShowWindow(progressbox,SW_SHOW);
  }
  
  /* change text */
  if (msg) SetDlgItemText(progressbox,IDC_PROGRESSTEXT,msg);
  
  /* write to logfile */
  if (msg) {
    sprintf(logs,"--Progress: '%s'\n",msg);
    logit(logs);
  }
  
  /* set heading of progress window */
  sprintf(string,"Work in progress ... step %d of %d",count,total_progress);
  SendMessage((HWND)progressbox,(UINT)WM_SETTEXT,0,(LPARAM)(LPCTSTR)string);

  for( i=0 ; i < progress_wait ; i+= millsec ){
    /* advance progress count */
    SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
    /* wait a bit ... */
    timerid=(int)SetTimer(NULL,0,millsec,(TIMERPROC) NULL);
    GetMessage((LPMSG)&timermsg,NULL,WM_TIMER,WM_TIMER);
    KillTimer(NULL,timerid);
    }
}

void noprogress(char *msg){
  /* change text */
  if (msg) SetDlgItemText(progressbox,IDC_PROGRESSTEXT,msg);
  
  /* write to logfile */
  if (msg) {
    sprintf(logs,"--Progress: '%s'\n",msg);
    logit(logs);
  }
  
  /* wait a bit ... */
  timerid=(int)SetTimer(NULL,0,progress_wait,(TIMERPROC) NULL);
  GetMessage((LPMSG)&timermsg,NULL,WM_TIMER,WM_TIMER);
  KillTimer(NULL,timerid);
  }

typedef struct linkinfo {
  int folder; /* registry key */
  char *link; /* name of link */
  char *file; /* name of file */
  char *desc; /* description of link */
  char *icon; /* name of icon for link */
  int removeonly; /* true, if icon should be removed but not installed */
  char *relative_path; /* relative path beneath the install path */
} LINKINFO;


HRESULT CreateShellLink(LINKINFO *li,char *path)
/* 
stolen from win32 SDK Help: Create a shell-link 
li    : points to LINKINFO structure containing all infos about link 
path  : Full pathname for objects
*/
{ 
  HRESULT hres;                /* return value */
  IShellLink* psl;             /* pointer to new shell-link */
  LPITEMIDLIST pidl;           /* path id */
  char PathLink[MAX_PATH];     /* path name */
  char string[SSLEN];          /* multi-purpose string */
  static int first=TRUE;
  
  /* make filename from registry folder constant */
  hres=SHGetSpecialFolderLocation(NULL,li->folder,&pidl);
  if (!SUCCEEDED(hres)) return hres;
  SHGetPathFromIDList(pidl,PathLink);
  strcat(PathLink,"\\");
  strcat(PathLink,li->link);
  
  /* initialize COM-library */
  if (first) {
    CoInitialize(NULL);
    first=FALSE;
  }
  
  /* Get a pointer to the IShellLink interface. */
  hres=CoCreateInstance(&CLSID_ShellLink,NULL, 
    CLSCTX_INPROC_SERVER,&IID_IShellLink,&psl); 
  if (SUCCEEDED(hres)) { 
    IPersistFile* ppf; 
    
    /* Set the path to the shortcut target */
    sprintf(string,"%s%s",path,li->file);
    psl->lpVtbl->SetPath(psl,string); 
    
    /* add description */
    psl->lpVtbl->SetDescription(psl,li->desc); 
    
    /* set working directory */
    psl->lpVtbl->SetWorkingDirectory(psl,path);
    
    /* set icon */
    if (li->icon[1]) {
      sprintf(string,"%s%s",path,li->icon);
      psl->lpVtbl->SetIconLocation(psl,string,0);
    } else {
      GetSystemDirectory(string,SSLEN);
      strcat(string,"\\shell32.dll");
      psl->lpVtbl->SetIconLocation(psl,string,li->icon[0]);
    }
    
    /* Query IShellLink for the IPersistFile interface for saving the 
    shortcut in persistent storage. */
    hres=psl->lpVtbl->QueryInterface(psl,&IID_IPersistFile,&ppf); 
    
    if (SUCCEEDED(hres)) { 
      WORD wsz[MAX_PATH]; 
      
      /* Ensure that the string is ANSI. */
      MultiByteToWideChar(CP_ACP,0,PathLink,-1,wsz,MAX_PATH); 
      
      /* Save the link by calling IPersistFile::Save. */
      hres=ppf->lpVtbl->Save(ppf,wsz,TRUE);
      ppf->lpVtbl->Release(ppf); 
    } 
    psl->lpVtbl->Release(psl); 
  } 
  return hres; 
} 


HRESULT DeleteShellLink(LINKINFO *li)
/* 
Delete a shell-link 
li    : points to LINKINFO structure containing all infos about link 
*/
{ 
  HRESULT hres;                /* return value */
  LPITEMIDLIST pidl;           /* path id */
  char PathLink[MAX_PATH];     /* path name */
  
  /* make filename from folder constant */
  hres=SHGetSpecialFolderLocation(NULL,li->folder,&pidl);
  if (!SUCCEEDED(hres)) return hres;
  SHGetPathFromIDList(pidl,PathLink);
  strcat(PathLink,"\\");
  strcat(PathLink,li->link);
  
  sprintf(logs,"--Deleting '%s'\n",PathLink);
  logit(logs);
  return DeleteFile(PathLink);
} 


int MyLinks(int mode) /* add or remove shell links */
{
  int success=TRUE;
  char string[SSLEN];
  LPITEMIDLIST pidl;           /* path id */
  char PathLink[MAX_PATH];     /* path name */
  int res;
  static LINKINFO li[]={
//    {CSIDL_PROGRAMS        ,BASIC_NAME"\\"BASIC_NAME".LNK",BASIC_EXE       ,"Link to "BASIC_NAME      ,BASIC_ICON,FALSE,"BIN\\"},
//    {CSIDL_PROGRAMS        ,BASIC_NAME".LNK"              ,BASIC_EXE       ,"Link to "BASIC_NAME      ,BASIC_ICON,FALSE,"BIN\\"},
    {CSIDL_PROGRAMS        ,BASIC_NAME"\\Users' Guide.LNK","ug.chm"        ,"Link to Users' Guide"    ,BASDOC_ICON    ,FALSE,"DOC\\"},
    {CSIDL_PROGRAMS        ,BASIC_NAME"\\Readme.LNK"      ,"readme.txt"    ,"Link to README.TXT"      ,"\026"    ,FALSE,""      },
    {CSIDL_PROGRAMS        ,BASIC_NAME"\\Install log.LNK" ,"install.log"    ,"Link to install.log"      ,"\026"    ,FALSE,""      },
    {CSIDL_DESKTOPDIRECTORY,"Users' Guide.LNK"            ,"ug.chm"        ,"Link to Users' Guide"    ,BASDOC_ICON    ,FALSE,"DOC\\"},

    {CSIDL_PROGRAMS,BASIC_NAME"\\Configure\\Configuration File.LNK"  ,"scriba.conf.txt","Configuration File"    ,"\026"    ,FALSE,"\\"},
    {CSIDL_PROGRAMS,BASIC_NAME"\\Configure\\Compile Configuration.LNK", "compconf.sb","Compile the configuration.sb", BASIC_ICON,FALSE,"EXAMPLES\\"},

#define MODUDOC(X,Y) \
    {CSIDL_PROGRAMS,BASIC_NAME"\\Documentation\\" X ".LNK", "mod_" Y ".chm","Link to mod_" X ".chm", "\027",FALSE,"DOC\\"},\

MODUDOC("Debugging BASIC programs","dbg")
MODUDOC("Berkeley Database Module","bdb")
MODUDOC("Writing Cgi","cgi")
MODUDOC("Console IO","cio")
MODUDOC("CURL Handling URLs","curl")
MODUDOC("Creating PNG Graphics","gd")
MODUDOC("Hash Module","hash")
MODUDOC("Multi-thread Module","mt")
MODUDOC("MySQL Module","mysql")
MODUDOC("Windows NT Functions","nt")
MODUDOC("ODBC Module","odbc")
MODUDOC("Regular Expressions","re")
MODUDOC("Extra Tools","t")
MODUDOC("Compressing Files","zlib")
MODUDOC("Handling XML Data","xml")
#undef MODUDOC

#include "examples.c"

    { 0                    , NULL                         ,NULL            ,NULL                      ,NULL      ,FALSE, ""    }
  };
  int i;  
  
  if (mode==INSTALL) {
    /* make filename from registry folder constant */
    SHGetSpecialFolderLocation(NULL,CSIDL_PROGRAMS,&pidl);
    SHGetPathFromIDList(pidl,PathLink);
    strcat(PathLink,"\\"BASIC_NAME);
    res=CreateDirectory(PathLink,NULL);
    strcat(PathLink,"\\Documentation");
    res=CreateDirectory(PathLink,NULL);

    SHGetSpecialFolderLocation(NULL,CSIDL_PROGRAMS,&pidl);
    SHGetPathFromIDList(pidl,PathLink);
    strcat(PathLink,"\\"BASIC_NAME);
    strcat(PathLink,"\\Examples");
    res=CreateDirectory(PathLink,NULL);

    SHGetSpecialFolderLocation(NULL,CSIDL_PROGRAMS,&pidl);
    SHGetPathFromIDList(pidl,PathLink);
    strcat(PathLink,"\\"BASIC_NAME);
    strcat(PathLink,"\\Configure");
    res=CreateDirectory(PathLink,NULL);
  }


  for( i=0 ; li[i].link ; i++ ) {
    if (mode==INSTALL && ! li[i].removeonly) {
      sprintf(string,"Adding %s",li[i].desc);
      progress(string);
      DeleteShellLink(li+i);/* just in case it was already there from a previous installation */
      if( *li[i].relative_path )sprintf(string,"%s%s",pszInstallPath,li[i].relative_path);else strcpy(string,pszInstallPath);
      success=SUCCEEDED(CreateShellLink(li+i,string)) && success;
    }
    else {
      sprintf(string,"removing %s",li[i].desc);
      progress(string);
      success=SUCCEEDED(DeleteShellLink(li+i)) && success;
    }
  }
  if (mode!=INSTALL) {
    /* make filename from registry folder constant */
    SHGetSpecialFolderLocation(NULL,CSIDL_PROGRAMS,&pidl);
    SHGetPathFromIDList(pidl,PathLink);
    strcat(PathLink,"\\"BASIC_NAME);
    file_deltree(PathLink);
  }
  return success;
}

int MyFiles(int mode) /* copy or delete files */
{

  gzFile fp;
  FILE *fo;
  char *s;
  int success=TRUE;
  char buf[SSLEN];
  char dirbuf[SSLEN];
  unsigned char *fbuf;
  long flen;
  int save_pw;

  switch(mode) {
    
  case INSTALL:
    strcpy(string,_pgmptr);
    s = string + strlen(string);
    while( *s != '\\' )s--;
    s++;
    *s = (char)0;
    strcat(string,GZFILE);

    fp = gzopen(string,"rb");
    if( fp == NULL ){
      sprintf(string,"Failed to open the installation file \"%s\"!\n"
              "This file has to be in the same directory as the program setup.exe!",GZFILE);
      MyMessage(NULL,string,INSTALL_HEADING,MB_STYLE);
      end(INSTALL_FAILURE);
      }
    progress("Installing files");
    save_pw = progress_wait;
    progress_wait = 2;
    do{
      gzgets(fp,buf,SSLEN);
      buf[strlen(buf)-1] = (char)0;
      sprintf(string,"Installing %s",buf);
      noprogress(string);
      sprintf(string,"%s/%s",pszInstallPath,buf);
      strcpy(dirbuf,string);
      s = dirbuf + strlen(dirbuf);
      while( *s != '\\' && *s != '/' )s--;
      *s = (char)0;
      file_MakeDirectory(dirbuf);
      brushupinline(string);
      while( file_exists(string) && ! DeleteFile(string) ){
        sprintf(buf,"The file %s exists and I can not overwrite it. If you want to go on with\n"
                    "the installation of ScriptBasic close all applications that may use this file\n\n"
                    "Do you want to continue the installation?\n",string);
        if( ! InstallQuestionYN(buf) ){
          end(INSTALL_CANCELLED);
          }
        
        }
      fo = fopen(string,"wb");
      gzgets(fp,buf,SSLEN);
      flen = atoi(buf);
      fbuf = malloc(flen);
      if( fbuf == NULL ){
        sprintf(string,"Memory allocation failed during installation.");
        MyMessage(NULL,string,INSTALL_HEADING,MB_STYLE);
        end(INSTALL_FAILURE);
        }
      if( gzread(fp,fbuf,flen) < flen ){
        sprintf(string,"The installation file \"%s\" is corrupt!\n",GZFILE);
        MyMessage(NULL,string,INSTALL_HEADING,MB_STYLE);
        end(INSTALL_FAILURE);
        }
      fwrite(fbuf,1,flen,fo);
      fclose(fo);
      }while( ! gzeof(fp) );
    gzclose(fp);
    sprintf(string,"%s\\setup.exe",pszInstallPath);
    logit("Copying the setup.exe into the install directory in case uninstall is needed.\n");
    CopyFile(_pgmptr,string,FALSE);
    progress_wait = save_pw;
    break;
  case REMOVE:
    file_deltree(pszInstallPath);
    break;
  default: 
    break;
  }
  return success;
}    

void InstallScriptBasic(){
  char *pszStartMessage;
  int success;
  char execvarg[SSLEN];
  STARTUPINFO SupInfo;
  PROCESS_INFORMATION ProcInfo;
  FILE *fp;
  char *s;

  GlobalSuccessFlag = 1;

  SupInfo.cb = sizeof(SupInfo);
  SupInfo.lpReserved = NULL;
  SupInfo.lpDesktop = NULL;
  SupInfo.lpTitle = NULL;
  SupInfo.dwFlags = 0;
  SupInfo.cbReserved2 = 0;
  SupInfo.lpReserved2 = NULL;

  // before doing anything else, check that the cab file is in place
  strcpy(string,_pgmptr);
  s = string + strlen(string);
  while( *s != '\\' )s--;
  s++;
  *s = (char)0;
  strcat(string,GZFILE);
     
  fp = fopen(string,"rb");
  if( fp == NULL ){
    sprintf(string,"Failed to open the installation file \"%s\"!\n"
            "This file has to be in the directory where the program 'setup.exe' is!",GZFILE);
    MyMessage(NULL,string,INSTALL_HEADING,MB_STYLE);
    end(INSTALL_FAILURE);
    }
  fclose(fp);
  /* set advance for progresscount */
  total_progress=40;

  if( dwMajor ){//minor and build can be zero
    if( dwMajor > MAJOR ||
        (dwMajor == MAJOR &&
          (dwMinor > MINOR || (dwMinor == MINOR && dwBuild > BUILD)))){
      pszStartMessage = "This program will install ScriptBasic " VERSION_TEXT "\n\n"
                        "There is a newer version of ScriptBasic installed on this system.\n"
                        "It is recommended that you use the newer version.\n"
                        "If you want to downgrade your installation it is recommended that you\n"
                        "first uninstall the newer version using the uninstaller of that\n"
                        "version and install ScriptBasic " VERSION_TEXT " only after the\n"
                        "newer version was removed.\n\n"
                        "This install process will install ScriptBasic but will not remove\n"
                        "the newer version. The newer version may remain on the system\n"
                        "unusable and uninstallable by automatic remover program.\n\n"
                        "If you decide to go on with the installation exit all programs\n"
                        "that may access and lock any ScriptBasic files. This also means to\n"
                        "stop the Eszter SB Application Engine in case it is running.\n\n"
                        "Do you want to perform the installation without removing the newer version?";
      }else{
      if( dwMajor == MAJOR && dwMinor == MINOR && dwBuild == BUILD ){
        pszStartMessage = "This program will install ScriptBasic " VERSION_TEXT "\n\n"
                          "The same version is already installed on this system.\n"
                          "If that version was corrupted and you want to reinstall\n"
                          "ScriptBasic you can, however you may loose changes to the\n"
                          "configuration you made since last setup.\n\n"
                          "It is recommended that you save your old configuration file\n"
                          "before continuing the installation.\n\n"
                          "If you decide to go on with the installation exit all programs\n"
                          "that may access and lock any ScriptBasic files. This also means to\n"
                          "stop the Eszter SB Application Engine in case it is running.\n\n"
                          "Do you want to perform the installation?";
        }else{
        pszStartMessage = "This program will install ScriptBasic " VERSION_TEXT "\n\n"
                          "There is an older version already installed on this system.\n"
                          "You can upgrade the older version of \n"
                          "ScriptBasic, however you may loose changes to the\n"
                          "configuration you made since last setup.\n\n"
                          "It is recommended that you save your old configuration file\n"
                          "before continuing the installation\n\n"
                        "If you decide to go on with the installation exit all programs\n"
                        "that may access and lock any ScriptBasic files. This also means to\n"
                        "stop the Eszter SB Application Engine in case it is running.\n\n"
                          "Do you want to perform the installation?";
        }
      }
    }else{
    pszStartMessage = "This program will install ScriptBasic " VERSION_TEXT "\n\n"
                      "If you decide to go on with the installation exit all other programs.\n\n"
                      "Do you want to perform the installation?";
    }
  if( ! InstallQuestionYN(pszStartMessage) ){
    end(INSTALL_CANCELLED);
    }

RETRY_INSTALL_PATH:
  if( pszInstallPath == NULL )pszInstallPath = DEFAULT_PATH;

  cancel=!DialogBox((HANDLE)this_instance,MAKEINTRESOURCE(IDD_PATHDIALOG),(HWND)NULL,(DLGPROC)pathdialog);
    
  if( cancel )end(INSTALL_CANCELLED);

  pszInstallPath = brushup(pszInstallPath);
  sprintf(logs,"--Install path='%s'",pszInstallPath);
  logit(logs);
   
  /* check for disk-space */
  {
    DWORD spc,bps,frcl,tncl;
    float total;
    int answer;
      
    sprintf(string,"%c:\\",*pszInstallPath);
    GetDiskFreeSpace(string,&spc,&bps,&frcl,&tncl);
    total=(float)frcl*spc*bps/1024;
    if (total<KBNEEDED) {
      sprintf(string,"Free disk space is only %g kB!\n"
        "Proceed anyway?\n\n"
"Press \"Yes\" if you want to install ScriptBasic into the selected\n"
"directory even though there is not enough space on the disk.\n"
"It is recommended to press \"No\" to return to the directory\n"
"selection dialog and select a directory on a different disk\n"
"with more space or to select the same directory again after\n"
"you deleted some unwanted files to make more room.\n"
"In the latter case SETUP will examine the available space again.\n"
"To install ScriptBasic you need approximately %dMB free space.\n"
        ,total,KBNEEDED / 1024 + 1);
      answer=MyMessage(NULL,string,INSTALL_HEADING,
        MB_YESNO | MB_SYSTEMMODAL | MB_ICONINFORMATION);
      if (answer==IDNO) goto RETRY_INSTALL_PATH;
    }
  } 
   
  success = MyRegs(INSTALL);
  if (!success) {
    MyMessage(NULL,"Failed to make entries in the Registry !",
      INSTALL_HEADING,MB_STYLE);
    end(INSTALL_FAILURE);
  }

  /* create directories */
  progress("Creating directories and copying files.");
  CreateDirectory(pszInstallPath,NULL);
  success=MyFiles(INSTALL);
  if (!success) {
    MyMessage(NULL,"Couldn't copy files !", INSTALL_HEADING,MB_STYLE);
    end(INSTALL_FAILURE);
    }
    
  /* create shell links */
  success=MyLinks(INSTALL);
  if (!success) {
    MyMessage(NULL,"Failed to add entry to the start-Menu !",
      INSTALL_HEADING,MB_STYLE);
    end(INSTALL_FAILURE);
  }

  // edit the configuration file and then compile it
  sprintf(string,"%sbin\\scriba.exe",pszInstallPath);
  sprintf(execvarg,"%sbin\\scriba.exe %sbin\\configurer.sb %s",pszInstallPath,pszInstallPath,pszInstallPath);

  CreateProcess(string,
                execvarg,
                NULL,
                NULL,
                FALSE,
                CREATE_NO_WINDOW,
                NULL,
                pszInstallPath,
                &SupInfo,
                &ProcInfo
               );
  Sleep(2000);
  CloseHandle(ProcInfo.hProcess);

  logit(NULL); // close the log file
  sprintf(string,"%sinstall.log",pszInstallPath);
  CopyFile(logfilename,string,FALSE);

  /* installation successfull ! */
  if( GlobalSuccessFlag )
    end(INSTALL_SUCCESS);
  end(INSTALL_PARTIAL);

  }

void RemoveScriptBasic(){
  char *pszStartMessage;
  STARTUPINFO SupInfo;
  PROCESS_INFORMATION ProcInfo;
  char execvarg[SSLEN];

  total_progress = 33;
  SupInfo.cb = sizeof(SupInfo);
  SupInfo.lpReserved = NULL;
  SupInfo.lpDesktop = NULL;
  SupInfo.lpTitle = NULL;
  SupInfo.dwFlags = 0;
  SupInfo.cbReserved2 = 0;
  SupInfo.lpReserved2 = NULL;

  if( dwMajor == MAJOR && dwMinor == MINOR && dwBuild == BUILD ){
    pszStartMessage = "This program will uninstall ScriptBasic " VERSION_TEXT "\n\n"
                      "Do you want to remove ScriptBasic?";
    if( ! InstallQuestionYN(pszStartMessage) ){
      end(INSTALL_CANCELLED);
      }
    }else{
    pszStartMessage = "This program should be used to remove ScriptBasic " VERSION_TEXT "\n"
                      "The currently installed version is not the one that this program\n"
                      "can uninstall. Use the appropriate version of the SETUP.EXE that\n"
                      "was used to install ScriptBasic.";
    MyMessage(NULL,pszStartMessage,"ScriptBasic Install",MB_OK|MB_SYSTEMMODAL|MB_ICONINFORMATION);

    end(INSTALL_CANCELLED);
    }
  pszInstallPath = GetSBRegString("path");

  // remove the sbhttpd service
  sprintf(string,"%sbin\\sbhttpd.exe",pszInstallPath);
  sprintf(execvarg,"%sbin\\sbhttpd.exe -remove",pszInstallPath);

  CreateProcess(string,
                execvarg,
                NULL,
                NULL,
                FALSE,
                CREATE_NO_WINDOW,
                NULL,
                pszInstallPath,
                &SupInfo,
                &ProcInfo
               );

  MyFiles(REMOVE);
  MyLinks(REMOVE);
  MyRegs(REMOVE);
  end(REMOVE_SUCCESS);
  }

int WINAPI WinMain(HINSTANCE _this_instance,   
                   HINSTANCE prev_instance,
                   LPSTR commandline,
                   int win_state){
  char execvarg[SSLEN];
  STARTUPINFO SupInfo;
  PROCESS_INFORMATION ProcInfo;
  BOOL bCrP;
  DWORD Gle;

  SupInfo.cb = sizeof(SupInfo);
  SupInfo.lpReserved = NULL;
  SupInfo.lpDesktop = NULL;
  SupInfo.lpTitle = NULL;
  SupInfo.dwFlags = 0;
  SupInfo.cbReserved2 = 0;
  SupInfo.lpReserved2 = NULL;
  this_instance=_this_instance;
  progress_wait = 400;
  pszInstallPath = GetSBRegString("path");

  GetTempPath(SSLEN,string);
  temppath=brushup(string);
  // if the setup.exe is executed from the install path, then this is remove
  // in this case we do nothing but copy the executable and start it from the
  // temp directory in a new process. This will let uninstall remove the whole
  // directory, even the setup.exe
  // the only thing that remains is the copy of SETUP.EXE in the temp directory
  // That is scheduled to be deleted on the next reboot calling MoveFileEx
  if( pszInstallPath && ! strnicmp(_pgmptr,pszInstallPath,strlen(pszInstallPath)) ){
    sprintf(string,"%s\\setup.exe",temppath);
    CopyFile(_pgmptr,string,FALSE);
    sprintf(execvarg,"%s remove",string);

    bCrP =
    CreateProcess(string,
                  execvarg,
                  NULL,
                  NULL,
                  FALSE,
                  CREATE_NO_WINDOW,
                  NULL,
                  temppath,
                  &SupInfo,
                  &ProcInfo
                 );

    Gle = GetLastError();    
    exit(0);
    }

  logit("ScriptBasic installation was started");

  sprintf(logs,"--Commandline='%s'\n",commandline);
  logit(logs);

  /* write to log */
  sprintf(logs,"--Temppath: '%s'\n",temppath);
  logit(logs);

  /* get current path */
  GetCurrentDirectory(SSLEN,string);
  currentpath=brushup(string);

  /* write to log */
  sprintf(logs,"--Currentpath: '%s'\n",currentpath);
  logit(logs);
  
  
  /* 'parse' commandline */
  install=TRUE;
  if (!strcmp(commandline,"remove")) install=FALSE;

  // get the version that is already installed
  GetSBRegDW("major",&dwMajor);
  GetSBRegDW("minor",&dwMinor);
  GetSBRegDW("build",&dwBuild);

  sprintf(logs,"--Installed: ScriptBasic version is %d.%db%d\n",dwMajor,dwMinor,dwBuild);
  logit(logs);

  if( install )InstallScriptBasic();
  else RemoveScriptBasic();

  }
