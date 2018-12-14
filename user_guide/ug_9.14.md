# Including Files

[\[\<\<\<\]](ug_9.13.md) [\[\>\>\>\]](ug_9.15.md)

You prepare your BASIC programs for ScriptBasic using some text editor.
This is usually NOTEPAD under Windows operating systems and it is emacs
or vi under UNIX. You enter the program line by line, but sometimes you
may want to include other files into your program. One way is to use the
copy and paste functionality of the editor. However this will lead
unnecessary big text files and unmanageable projects. Instead you can
use the `INCLUDE` command of ScriptBasic.

Whenever you want to include the file named \``myinclude.bas`' you
should write

    INCLUDE "myinclude.bas"

into your program. Although statements are not case sensitive, file
names are on UNIX systems. On Windows systems the operating system
preserves the case of the file names, but you can reference the file
using any case letters.

If you want to maintain portability of your programs (and you usually
should) use always lower case file names and reference them using lower
case letters.

When you specify file names that reside in a different directory you can
specify relative file names, or absolute file names including the path
of the file. If \``myinclude.bas`' is in a subdirectory you should
write:

    INCLUDE "sudir/myinclude.bas"

Here we can mention another point of portability. UNIX uses the forward
slash as file separator character. Windows command line interpreter use
the back slash. In ScriptBasic you can use both separators on Windows
and on UNIX as well. You can even mix them in a single path. We
recommend that you use the forward slash character for the purpose.

If you use the back-slash characters in file names in ordinary BASIC
strings like in the statement `OPEN` you usually have to double the
character because this character plays the role of the escape character
in strings. **This is not the case for the include statement.** You
should write

    REM a correct include statement
    INCLUDE "subdir\myinclude.bas"

but

    REM bad include statement
    INCLUDE "subdir\\myinclude.bas"

will eventually fail to include the file.

Whenever you specify a relative directory, which is above the directory
of the including file use the double dot notation of the parent
directory, like

    INCLUDE "../parentel.bas"

Whenever a relative file name is specified in an include statement the
file name should be relative to the file that contains the include
statement. For example you may have the three files:

    C:\BASIC\INCLUDE\myinclude.bas
    
    C:\BASIC\myprog.bas
    C:\BASIC\INCLUDE\SYS\system.bas

The program \``myprog.bas`' includes the file \``myinclude.bas`' using
the statement

    INCLUDE "include/myinclude.bas"

The program \``myinclude.bas`' includes the file \``system.bas`' using
the statement

    INCLUDE "sys/system.bas"

The INCLUDE statement has another form:

    INCLUDE mymodule.inc

This is similar to the format discussed above with the exception that
there is no quote character around the file name. In this case
ScriptBasic tries to locate the named file in one of the configured
include directories. The file name in this case should not contain
space. Such include files usually belong to binary modules that
ScriptBasic can dynamically load, and the included files declare the
function implemented in the binary module.

The statement `INCLUDE` is processed before the variables, numbers,
string and other lexical elements are recognized. This may result some
strange behavior. For example the code:

    T$ = """this is a multi-line string that 
    Include "otherfile.txt"
    includes another file."""

is correct and results a string that contains the content of the file
otherfile.txt. This may seem strange but it is the way ScriptBasic
preprocessing handles the include directive.

Be aware of this feature as this may lead to strange errors when a
multi-line string contains lines that start with the word `include`,
`import` or `use`. Because nor the character `i` neither the character
`u` has a special meaning back-slashed you can easily overcome the
situation prepending a backslash `\` character before the special word.
For example:

    T$ = """this is a multi-line string that 
    \Include "otherfile.txt"
    does not include another file."""

As your program goes larger and larger you split it up into included
files. The code that includes them may include one file, including
another file and so on. It may finally result some file included more
than once. To avoid redefinition of thing and unnecessary code
repetition ScriptBasic has another preprocessor statement named
`IMPORT`.

`IMPORT` behaves the same way as `INCLUDE` does with the exception that
it does not include the file if the file was already included by a
previous `INCLUDE` or `IMPORT` preprocessor statement.

-----

[\[\<\<\<\]](ug_9.13.md) [\[\>\>\>\]](ug_9.15.md)
