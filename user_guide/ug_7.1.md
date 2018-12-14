# Compilation under Windows NT

[\[\<\<\<\]](ug_7.md) [\[\>\>\>\]](ug_7.2.md)

Currently Visual C command line `cl` and Borland command line `bcc32`
compilers are supported.

There are two command files that you can find in the `bin` directory
under the installation directory. These are \``bascl.cmd`' to automate
the compilation using the Microsoft compiler and \``basbcc32`' to
automate the compilation using the Borland compiler.

The \``bin`' directory also contains the files \``libscriba.lib`' and
\``libscriba.obj`' to be used by the Microsoft compiler and linker, as
well as \``libscriba_omg.lib`' and \``libscriba_omg.obj`' to be used by
the Borland compiler and linker.

The content of the file \``bascl.cmd`':

    scriba -n -Co %1.c %1.bas
    cl /Ox /GA6s /DWIN32 /MT /nologo /W0 /c /Fo%1.obj %1.c
    cl /Ox /GA6s /DWIN32 /MT /nologo /W0 /Fe%1.exe %1.obj \ScriptBasic\bin\libscriba.obj \ScriptBasic\bin\libscriba.lib ws2_32.lib advapi32.lib

The content of the file \``bascbcc32.cmd`':

    scriba -n -Co %1.c %1.bas
    bcc32 -5 -c -o%1.obj %1.c
    bcc32 %1.obj \ScriptBasic\bin\libscriba_omg.obj \ScriptBasic\bin\libscriba_omg.lib

This is the content as the files are installed. In case you have more
than one disk, or the installation directory is not \``\ScriptBasic`'
you may need to edit the file you intend to use replacing the
`\ScriptBasic\bin\` with the actual directory where the object and
library files are. It is recommended that you also edit the disk drive
letter into the full path so that the command script works in case the
actual working directory is on a different disk than the one where
ScriptBasic is installed.

The reason that there are two different object and library files for the
two different compilers is that these compilers support different object
and library format. Microsoft supports the COFF format, while the free
compiler available from Borland supports only OMG format. Although there
is a `coff2omg` converter available from Borland that works only for
library files that are DLL wrapper libraries and not for object files or
for library files containing actual code.

These object and the library files contain the same code with the
exception that they were created using different compilers.

-----

[\[\<\<\<\]](ug_7.md) [\[\>\>\>\]](ug_7.2.md)
