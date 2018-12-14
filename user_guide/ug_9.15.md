# Internal preprocessors

[\[\<\<\<\]](ug_9.14.md) [\[\>\>\>\]](ug_9.16.md)

ScriptBasic does not have a built-in macro preprocessor, like language
C. However it has an open interface that third party developers can use
to develop preprocessors. A ScriptBasic program may have one or more
`USE` commands in it. This command should stand alone on a line being a
preprocessor command.

The format of the command is:

    USE preprocessor_name

After ScriptBasic has loaded the source code and has included all the
files specified by the include statements it scans the lines containing
a `USE` statement. When it finds one it loads the external preprocessor
module compiled by the third party developer into a DLL or SO file and
calls the preprocessor function. The preprocessors get total control
over the source file loaded into memory and are free to alter the source
code.

The preprocessor DLL or SO file should be specified in the configuration
file. For example the line

    preproc (
      internal (
        dbg "E:\\MyProjects\\sb\\Debug\\dbg.dll"
        )
    ...

from the default Win32 \``scriba.conf`' file defines what DLL file to
load when the source file uses the preprocessor called `dbg` that
actually happens to be the debugger preprocessor.

Internal preprocessors can also be loaded using the command line option
\``-i`'. For example in case you want to start a ScriptBasic program
from the command line using the command line debugger you can type:

    # scriba -i dbg mybugous_program.bas

For more information on how to use a preprocessor see the documentation
of the preprocessor.

-----

[\[\<\<\<\]](ug_9.14.md) [\[\>\>\>\]](ug_9.16.md)
