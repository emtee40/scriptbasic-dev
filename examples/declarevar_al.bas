REM """
FILE: declarevar_al.bas
AUTHOR: Peter Verhas
DATE: 14:13 2003. 05. 20.

This program tests the behaviour of the interpreter when the
option 'AutoVars' is in effect regarding variable declarations:

You need not define any variable and all variables are local
unless explicitely declared to be global.

"""
declare option AutoVars
declare option DefaultLocal


sub q
 global testvarGlobal
 ' this is not declared and therefore this is local
 testvarLocal = 3
 ' this is declared to be global
 testvarGlobal = 4
end sub

testvarLocal = 1
testvarGlobal = 2
q

print "this prints 14\n"
print testvarLocal,testvarGlobal
print
