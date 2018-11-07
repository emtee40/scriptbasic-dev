' port.bas
' """
This program is the sample implementation for handling
the FTP command 'PORT' in the Eszter SB Application Engine
FTP server implementation.
"""
import mt.bas

mt::SetSessionId environ("THREAD_INDEX")

Command$ = environ("FTP_COMMAND")
Command$ = MID$(Command$,6)
SPLITA Command$ BY "," TO digit

ClientAddress = digit[0] & "." & digit[1] & "." & digit[2] & "." & digit[3] & ":" & digit[4]*256+digit[5]

mt::SetSessionVariable "CLIENT_ADDRESS", ClientAddress
print "200 Command OK\r\n"