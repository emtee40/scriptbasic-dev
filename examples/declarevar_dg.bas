REM """
FILE: declarevar_dg.bas
AUTHOR: Peter Verhas
DATE: 14:17 2003. 05. 20.

This program tests the behaviour of the interpreter when the
option 'DeclareVars' is in effect regarding variable declarations:

You should define each variable and all variables are global
unless explicitely declared to be local.

"""
declare option DeclareVars
declare option DefaultGlobal

' we need to declare the variable
global testvarGlobal, testvarLocal

sub q
local testvar
 local testvarLocal
 ' we need not declare it, because it was already declared
 testvarGlobal = 3
 testvarLocal  = 4
end sub

testvarGlobal = 1
testvarLocal  = 2
q
print "this prints 32\n"
print testvarGlobal,testvarLocal
print
