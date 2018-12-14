# @goto start

[\[\<\<\<\]](ug_9.17.md) [\[\>\>\>\]](ug_9.19.md)

Your basic program may contain a first line that looks like the title of
this section. This may seem strange for UNIX users, but this is usual
under Windows. On Windows systems such a first line is used to transfer
the execution of the Windows command interpreter to the end of the
command file, where the interpreter is invoked for the same file.

This looks like:

    @goto start
    
       scriptbasic program lines
    
    rem """
    :start
    @echo off
    scriba %0 %1 %2 %3 %4 %5 %6 %7 %8 %9
    rem """

assuming that `scriba` is in the path this file named something
`xxxx.cmd` can be started from the command line and will execute the
BASIC program. The first line is ignored by the ScriptBasic interpreter,
but the Windows command processor will jump to the line containing
`:start`. On this line the ScriptBasic interpreter is started and reads
and interprets the lines. The first line is ignored by ScriptBasic, the
last few lines are comment at least for ScriptBasic.

To ease portability such a first line is ignored when executing a BASIC
program under UNIX.

-----

[\[\<\<\<\]](ug_9.17.md) [\[\>\>\>\]](ug_9.19.md)
