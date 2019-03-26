# Compiling BASIC programs to C

[\[\<\<\<\]](ug_6.1.md) [\[\>\>\>\]](ug_7.1.md)

Although ScriptBasic is an interpreted language it is possible to create
stand-alone executables from BASIC programs on any platform where
ScriptBasic can run. To get an executable standalone program first you
have to compile your BASIC program to C and the C code has to be
compiled to get the executable. (Unless you use the option \``-E`' that
can generate executable directly.)

To get the C version of the BASIC program you should use the command
line option C, for example:

    scriba -nCo myprogram.c myprogram.bas

This command will compile the BASIC program \``myprogram.bas`' and save
the code in C language format into the text file \``myprogram.c`'. You
have to compile this file using a C compiler and link it with the
library files.

When using this option the ScriptBasic interpreter will ignore any
cached precompiled code and will compile the BASIC program from source
code fresh. When compiling BASIC to C do not forget to specify the
output file using the option \``-o`'. Without this option ScriptBasic
does not perform the compilation, there is no default file name for the
output.

Note that this is not a real compilation. This methodology only creates
the intermediary code that the ScriptBasic execution module uses and
puts it into a C program. The final executable will contain the binary
code of the BASIC program and will execute the same way as it would
execute running the original file.

The achievements you can get compiling the code and generating
standalone executable file are:

  - Faster startup, because the executable does not need to compile or
    even load the BASIC program, but can execute it immediately. This is
    a bit even faster than the EXE file generated by directly compiled
    from BASIC.
  - Simplified setup of your program, because you only have to deliver a
    standalone exe to your users.
  - You can hide that your program was written in BASIC and can a bit
    protect your intellectual property.

Also note that you have to have a properly created configuration file
and the `dll` or `so` modules on the system your executable is going to
run in case you need some features that rely on configuration settings.

You may also consider recompiling the ScriptBasic interpreter to
statically link some of the external modules that your BASIC program
uses.

-----

[\[\<\<\<\]](ug_6.1.md) [\[\>\>\>\]](ug_7.1.md)