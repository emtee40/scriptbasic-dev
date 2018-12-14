# Introduction

\[\<\<\<\] [\[\>\>\>\]](ug_2.md)

ScriptBasic is a BASIC language interpreter with several features that
makes it unique. First of all ScriptBasic itself is **free** and is
supported by the **GNU LGPL licence**. Note that the GNU LGPL
[licence](http://www.gnu.org/copyleft/lesser.txt) applies only to
ScriptBasic itself, while the modules interfacing 3rd party software may
apply different licenses. For example the module interface code for the
module T\<bdb\> is under LGPL, but the library it uses, namely the
Berkeley DB is NOT LGPL\!

ScriptBasic runs on **Windows NT, Windows95, Linux, Tru64 UNIX** and
probably on many other platforms. ScriptBasic the ideal tool to write
small scripts that gurus write in Perl. However you need not be a guru
to powerfully program in ScriptBasic.

This is not the only situation to consider ScriptBasic. ScriptBasic can
be a valuable tool for experts as well as a language interpreter ready
to be built into their application. Read the list of ScriptBasic
features and decide how you can use it.

  - **IT IS BASIC.** No question, this is the MOST important feature of
    ScriptBasic. There are a lot of people who can program BASIC and
    only BASIC. There are many people, who can not really program. Those
    who do not really know what programming is, and still: they write
    their five-liners in BASIC to solve their simple problems. They
    never write Perl, Tcl, Java or C. Therefore it is BASIC.
  - **SCRIPTING** language. There are no data types in the language. You
    can store real numbers, integer numbers and strings in any variable.
    You can mix them and conversion is done automatically. Therefore the
    language is very simple and easy to use.
  - **PORTABLE** Available in C source and can be compiled on UNIXes as
    well as on Windows NT.
  - **4E LANGUAGE**, which means easy to extend, easy to embed.
    ScriptBasic was developed to provide clean and clear interfaces
    around it, and inside it. It is easy to embed the language to an
    application and use it as a macro language just like TCL. It is also
    easy to implement new built-in function and new commands. You can
    develop dynamically loaded libraries that ScriptBasic may load at
    run time. The language source is clean, well documented and
    development guides are available.
  - **COMPILED CODE** ScriptBasic creates intermediate compiled code,
    which is interpreted afterwards. This can protect intellectual
    property for the BASIC programmer and faster code loading.
      - Syntax analysis is done at first and only syntactically perfect
        programs start to run.
      - The compiled code is put into a continuous memory space and
        compiled code can be saved and loaded again to run without
        recompilation. This is vital for CGI scripts and is not
        available for most scripting programming languages.
      - Compiled code is binary, not readable. Therefore you can develop
        and distribute programs and getting some help to protect your
        intellectual property. You need not give the source code.
  - **MULTI THREAD** aware. Although the current implementation is not
    multi thread, all the code was designed to be thread safe. You can
    embed the code into systems that run multiple interpreters in the
    same process. On the other hand the interpreter can run the same
    code in multiple threads and was designed to be capable handling
    call-back functions, and multithread programs in the future.

This documentation is the User's Guide for the so-called STANDARD
variation of the interpreter. This code runs on the command line,
accepts command line arguments and runs a single program in a single
process. Other variations exist, which are based on the same code but
exhibit different interfaces to the system. Some features for those
variations may be different, but most language features probably remain
the same. The variation Eszter SB Application Engine is shipped with the
ScriptBasic package and is embedding the interpreter into a
multi-thread, single process web server. Other embedded variations are
available from independent developers.

This document describes how to use the interpreter and the programming
language.

-----

\[\<\<\<\] [\[\>\>\>\]](ug_2.md)
