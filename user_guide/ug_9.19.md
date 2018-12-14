# \#\!/@goto

[\[\<\<\<\]](ug_9.18.md) [\[\>\>\>\]](ug_10.md)

After the previous two sections here is a small trick that allows you to
have a ScriptBasic program that can be executed under UNIX as well as
under Windows just typing the name of the BASIC program file and without
any modification.

    #! /usr/bin/scriba
    goto start
    start:
         
    scriptbasic program lines
    
    rem """
    :start
    @echo off
    scriba %0 %1 %2 %3 %4 %5 %6 %7 %8 %9
    rem """

Unfortunately under Windows NT the command interpreter will complain
about the very first line. However in addition to that there is no other
issue.

-----

[\[\<\<\<\]](ug_9.18.md) [\[\>\>\>\]](ug_10.md)
