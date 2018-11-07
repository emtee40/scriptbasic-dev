REM """
FILE: declarevar_ag.bas
AUTHOR: Peter Verhas
DATE: 14:11 2003. 05. 20.

This program tests the behaviour of the interpreter when the
default options are in effect regarding variable declarations:

You need not define any variable and all variables are global
unless explicitely declared to be local.

"""
declare option AutoVars
declare option DefaultGlobal

sub q
 ' this is changing the global variable testvar
global testvar
 testvar = 3
end sub

' set it to one
testvar = 1
' this changes the value of testvar to 3
q
print "this prints 3\n"
print testvar
print
