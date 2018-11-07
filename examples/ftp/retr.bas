' retr.bas
' """
This program is the sample implementation for handling
the FTP command 'RETR' in the Eszter SB Application Engine
FTP server implementation.
"""
' use dbg
import mt.bas

mt::SetSessionId environ("THREAD_INDEX")

ClientAddress = mt::GetSessionVariable("CLIENT_ADDRESS")

if not IsDefined(ClientAddress) then
  print "503 Bad sequence of commands, PORT is needed before RETR\r\n"
else
  print "150 File status okay; about to open data connection.\r\n"
  on error goto SocketDoesNotOpen
  open ClientAddress for socket as 3
  print "125 Data connection already open; transfer starting.\r\n"
  print#3, "hey, here is the content of the downloaded file...\r\n"
  print "226 Closing data connection.\r\n"
  close 3
  print "250 Requested file action okay, completed.\r\n"
end if

stop

SocketDoesNotOpen:
print "425 Can't open data connection\r\n"
