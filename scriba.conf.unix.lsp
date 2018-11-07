; scriba.conf.unix.lsp
; ScriptBasic sample configuration file
;
; This is the sample configuration file for ScriptBasic
; when it is installed on UNIX. The format of this file is
;
;                 key value
;
; where key is a case sensitive symbol and value is the value
; associated to it. The value can be string, integer, real or
; sub configuration. In this latter case the value is enclosed
; between ( and )
;
; subconfigurations are like the whole configuration file contain
; one or more 'key value' pairs.
;
; The configuration file should not be empty and no sub configuration
; is allowed to be empty.
;
; After the configuration file is altered it has to be compiled. This
; can be accomplished using ScriptBasic with the command line option -k
;
;    scriba -k scriba.conf.unix.lsp
;
; will compile the configuration and save it into the binary file
; which is the configuration file for ScriptBasic. This is usually
; /etc/scriba/basic.conf under UNIX
;
; Having the configuration in binary mode fastens up CGI scripts and
; gives some light security, but do not depent on that too much.


; this is the extension of the dynamic load libraries on this system
dll ".so"

; Specify here the directory where the module shared objects are.
; You can specify more than one directory. ScriptBasic will search these
; directories in the order as they are specified here.
; The configuration valéue SHOULD contain the trailing /
module "/usr/local/lib/scriba/"

; Specify here the directory where the module header include files are.
; You can specify more than one directory. ScriptBasic will search these
; directories in the order as they are specified here.
; The configuration valéue SHOULD contain the trailing /
include "/usr/share/scriba/include/"

; specify where documentation is to be stored under UNIX
docu "/usr/share/scriba/source/"

;
; define preprocessors
;
preproc (

  ; -- define internal preprocessors --
  internal (
    ; the key is the name of the preprocessor that the user uses on the command line,
    ; for example 'scriba -i dbg'
    ; the value should be the full path to the shared object implementing the
    ; preprocessor.
    ;
    ; This is the sample preprocesor that implements the command line
    ; version fo the debugger.
    dbg "/usr/local/lib/scriba/dbg.so"
    )

  ; -- define external preprocessors --

  ; external preprocessors are invoked in separate process based on
  ; command line option but also based on file extension

  ; define the extension for which there is a preprocessor to be started
  extensions (
     ; the key is the extension and the value is the symbolic name of the external preprocessor
     heb "heb"
     )

  ; define the external preprocessors
  external (
    ; here the key is the symbolic name of the preprocessor,
    ; which was specified in the string (e.g. "heb") above
    ; associated to the extension
    heb (
      ; define the command line of the preprocessor
      ; this command line will be appended with two arguments:
      ;  - the first argument is the source file to process
      ;  - the second argument is the preprocessed file that the
      ;    preprocessor should create (full path will be passed to
      ;    the preprocessor)
      executable "/usr/bin/scriba /usr/share/scriba/source/heber.bas"
      ; This is the directory where the preprocessor has to put the
      ; preprocessed file. The interpreter uses this parameter
      ; to create the second argument for the preprocessor.
      directory "$(HOME)/.scriba/hebtemp"
      )
    )
  )

;
; LIMIT VALUES TO STOP INIFINITE LOOP
;

; the maximal number of steps allowed for a program to run
; comment it out or set to zero to have no limit
maxstep 0

; the maximal number of steps allowed for a program to run
; inside a function.
; comment it out or set to zero to have no limit
maxlocalstep 0

; the maximal number of recursive function call deepness
; essentially this is the "stack" size
; When the sample configuration file is created by setup.pl
; this value is calculated. You may alter it to be smaller,
; but on this platform the safe value is 37328
; If you increase it 37328+100 you surely get into trouble.
; (do not) comment it out or set to zero to have no limit
maxlevel 37328


; the maximal memory in bytes that a basic program 
; is allowed to use for its variables
; comment it out or set to zero to have no limit
maxmem 0

; ScriptBasic loads a module when the first function
; implemented in the module is used by the BASIC program.
; Some modules (for example noprint sample module) has
; to be loaded before the BASIC program starts. Use this
; key zero or more times to specify the modules that has
; to be loaded before any BASIC program on your installation
; runs.
;
; The sample module 'noprint' prevents the BASIC programs to use
; the command 'print', which is not a wise choice, but it is just
; a demo code anyway. You can develop security modules that you can
; force the interpreter to preload.
;preload "ext_trial"

; This is the directory where we store the compiled code
; to automatically avoid recompilation
; You need only one of this directory, do not specify more than one.
; You can comment out this directive to prevent cache usage or
; point it to a directory that does not exist or can not be written
; by the BASIC programs. Using the cache gives some performance
; advance but also implies some security considerations.
cache "$(HOME)/.scriba/cache"

;
; berkeley db config
;
bdb (

 ; directories where to store the 
 dir (
   home "$(HOME)/.scriba/cache/berkeleydb/" ; the home directory of operation of the Berkerley DB
   data "db"  ; database files
   log  "log" ; log files
   temp "tmp" ; temporary files
   )

;  limits (
;    lg_max "1024000"
;    mp_mmapsize "0000"
;    mp_size "000"
;    tx_max "000"
;    lk_max "000"
;    )

  ; what lock strategy to use
  ; it can be any of the followings
  ; default oldest random youngest
  lockstrategy default

  flags (
    ; set the value to yes or no
    lock_default no
    init_lock yes
    init_log yes
    init_mpool yes
    init_txn yes
    create yes
    )
  )
;
; MySQL configuration
;
mysql (
  connections (
    test (        ; the name of the connection
	  host "127.0.0.1" ; the host for the connection
	  db "test"   ; database for the connection
	  user "root" ; user for the connection
	  password "" ; password for the connection
	  port 0      ; the port to use
	  socket ""   ; the name of the socket or ""
	  flag 0      ; the client flag
	  clients 10  ; how many clients to serve before really closing the connections
	  )
    auth  (
	  host "127.0.0.1" ; the host for the connection
	  db "auth"   ; database for the connection
	  user "root" ; user for the connection
	  password "" ; password for the connection
	  port 0      ; the port to use
	  socket ""   ; the name of the socket or ""
	  flag 0      ; the client flag
	  clients 10  ; how many clients to serve before really closing the connections
          )
    )
  )

;
; Configure the sample ScriptBasic httpd daemon
;
servers (
  server (
    port 8889
    ip "10.22.2.94"
    protocol http
    )
  server (
    port 21
    ip "127.0.0.1"
    protocol ftp
    salute """220 Eszter SB Application Engine salute text"""
    codebase "/usr/share/scriba/source\ftp\"
    programs (
      PASS "/usr/share/scriba/source\ftp\pass.bas"
      ACCT "/usr/share/scriba/source\ftp\acct.bas"
      )
    )
  threads 20
  listenbacklog 30
  home "/usr/share/scriba/source/"
  proxyip 0 ; set it true if you use Eszter engine behind Apache rewrite and proxy modules

  pid (
    file "$(HOME)/.scriba/pid.txt"
    delay 10 ; number of seconds to sleep between the examination of the pid file if that still exists
    wait ( 
      period 10 ; number of times to wait for the threads to stop before forcefully exiting
      length 1  ; number of seconds to wait for the threads to stop (total wait= period*length)
      )
    )

  vdirs (
    dir "/cgi-bin/:/usr/share/scriba/source/"
    )
  client (
;    allowed "127.0.0.1/255.255.255.255"
    allowed "0.0.0.0/0.0.0.0"

;    denied "127.0.0.1/0.0.0.0"
;    denied "16.192.0.0/255.255.0.0"
    )
  errmsgdest 3
  nolog 0 ; set this true not to use logs or ignore erroneouslog configuration
;  run (
;     start   "start.bas"
;     restart "restart.bas"
;      )
  log (
    panic ( file "$(HOME)/.scriba/panic.log" )
    app   ( file "$(HOME)/.scriba/app.log" )
    err   ( file "$(HOME)/.scriba/err.log" )
    hit   ( file "$(HOME)/.scriba/hit.log" )
    stat  ( file "$(HOME)/.scriba/stat.log" )
    )
  ; the error page when a page is not found
msg404 """
<HTML>
<HEAD>
<TITLE>Error 404 page not found</TITLE>
</HEAD>
<BODY>
<FONT FACE="Verdana" SIZE="2">
<H1>Page not found</H1>
We regretfully inform you that the page you have requested can not be found on this server.
<p>
In case you are sure that this is a server configuration error, please contact
<FONT SIZE="3"><TT>root@localhost</TT></FONT>
</FONT>
</BODY>
</HTML>
 """
  code404 "200 OK" ; the http error code for page not found. The default is 404
  ; the program to run when a page is not found
  ;run404 "/usr/share/scriba/source/run404.bas"
  )
