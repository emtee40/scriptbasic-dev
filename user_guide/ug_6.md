# Compiling BASIC program to EXE

[\[\<\<\<\]](ug_5.1.md) [\[\>\>\>\]](ug_6.1.md)

ScriptBasic program can be "compiled" to executable directly under
Windows and Linux. To do this you should use the option \``-E`' and you
should also specify an output file using the option \``-o`'. For
example:

    scriba -Eo queens.exe queens.bas

will generate an executable file \``queens.exe`' that will run the BASIC
program \``queens.bas`'. When using this option the ScriptBasic
interpreter will ignore any cached precompiled code and will compile the
BASIC program from source code fresh.

Note that this kind of compilation works only on Linux and Windows and
the generated file is operating system specific, and can not run on any
other operating system. Beta test users reported that the feature works
on FreeBSD and on Solaris, but the developers lacking test resources can
not guarantee this.

Although the ScriptBasic interpreter compiled and installed on other
operating system (above Windows and Linux) will accept these options and
will generate a file it may not be usable. This feature uses the
specialties of the executable format of Windows and Linux.

The compilation to executable is not a real compilation, in the sense
that the program is not compiled into real machine code, and thus do not
expect it running faster or using less memory. This methodology only
creates the intermediary code that the ScriptBasic execution module uses
and puts it into an executable file that also contains the interpreter.
The final executable will contain the binary code of the BASIC program
and will execute the same way as it would execute running the original
file.

In the rest of this chapter we detail how the BASIC to EXE direct
compilation works.

-----

[\[\<\<\<\]](ug_5.1.md) [\[\>\>\>\]](ug_6.1.md)
