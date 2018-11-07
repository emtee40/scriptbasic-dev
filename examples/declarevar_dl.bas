REM """
FILE: declarevar_dg.bas
AUTHOR: Peter Verhas
DATE: 14:21 2003. 05. 20.

This program tests the behaviour of the interpreter when the
options 'DeclareVars' and 'DefaultLocal' are in effect 
regarding variable declarations:

You should define each variable and all variables are local
and should explicitely declared.

"""
declare option DeclareVars
declare option DefaultLocal

global testvarGlobal,testvarLocal

sub q
' both variables have to be declared
local testvarLocal
global testvarGlobal
 testvarGlobal = 3
 testvarLocal  = 4
end sub

testvarGlobal = 1
testvarLocal  = 2
q
print "this prints 32\n"
print testvarGlobal,testvarLocal
print
