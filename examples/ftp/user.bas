import mt.bas
' mt::NewSessionId environ("THREAD_INDEX")

mt::SetSessionId environ("THREAD_INDEX")

Command$ = environ("FTP_COMMAND")
Command$ = left(Command$,len(Command$)-2)
print "331 Password required for ",Command$," * ",environ(1),"\r\n"
mt::SetSessionVariable "USER",mid$(Command$,6)