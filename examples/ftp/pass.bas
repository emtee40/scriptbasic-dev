import mt.bas
mt::SetSessionId environ("THREAD_INDEX")

Command$ = environ("FTP_COMMAND")
Command$ = left(Command$,len(Command$)-2)
print "230 OK >>",Command$,"<< user=",mt::GetSessionVariable("USER")," come in\r\n"
