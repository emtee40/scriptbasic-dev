# Compiling ScriptBasic with modules

[\[\<\<\<\]](ug_7.2.md) [\[\>\>\>\]](ug_9.md)

This section is rather technical and not for the BASIC programmer. This
section details how to compile the ScriptBasic interpreter so that it
already includes some of the external modules. This requires knowledge
how to compile C programs and some programming practice of C is also
helpful. If you just want to program in BASIC do not read this section
and get distracted by this, skip to the next section.

ScriptBasic supports external modules that are usually delivered as DLL
or SO files and using them do not require the recompilation of the
interpreter. However in some cases there is a need to compile the
ScriptBasic interpreter and some of the external modules into a single
executable image. This may be the case when you deliver a solution to a
customer and want to build a special version of the interpreter
lessening the possibility of misconfiguration or you just simply want to
protect your intellectual property implemented in the external module
and do not want to deliver it as DLL or SO file. Linking some modules
static into the interpreter also provides some speed improvement.

To link some modules into the interpreter you have to create a file
named \``lmt_XXX.def`'. This file should list the names of the modules
that you want to statically link. There can be empty lines and lines
starting with the character `#` as comment. You can use the characters
`XXX` (not necessarily three character, but try to avoid the word
`httpd` and `none` as we have already have those) to distinguish your
compilation.

After the file is created issue the command:

    perl lmt_make.pl lmt_XXX.def

This will create the file `lmt_XXX.c`.

**THIS IS CHANGED TOTALLY FOR v1.0BUILD30 and ABOVE. TO BE REWRITTEN
ALTER. ACTUALLY ALL THESE THINGS SHOULD GO INTO THE DEVELOPERS
GUIDE\!\!**

If you look into the file \``lmt_XXX.c`' you will see that the module
tables are referenced by the global table `StaticallyLinkedModules`. You
have to give the name of the function as a string as well as the
function as well. This table will be searched by ScriptBasic when the
module is "loaded". When a module is loaded from a DLL or SO file such a
table is provided by the operating system and is searched by operating
system functions.

The next step is to compile the modules for the static linking. This is
a bit different from compiling for DLL or SO file as result. When the
module is compiled to be linked into a DLL or SO file all interface
functions should be exported so that the operating system can access
their name and entry point. When the module is compiled to be linked
together with the interpreter all functions should be static. If we
compiled the module the same way as for targeting DLL or SO file we were
not able to link more than one module into the interpreter because the
linker would complain about multiple defined `versmodu` and other
functions that are defined in each module.

To compile a module for static linking you should use the compilation
option \``-DSTATIC_LINK=1`' that tells the C preprocessor to define some
macros differently than normal. If you look into the \``Makefile`' or
\``Makefile.nt`' you will see that these compilation options are already
there and all module interface files can be compiled using the tool make
to its static version which is named \``s_module.o[bj]`'. The prefix
`s_` is used to denote that this version of the object file was compiled
from the same C source using the options that are required for static
linking of the interpreter.

Choose an appropriate executable name `XXX` for your version and edit
the `Makefile`. Create the rule that compiles your version. Your version
will eventually use \``lmt_XXX.c`' and \``lmt_XXX.o[bj]`' instead of
\``lmt_none.*`' and the executable will depend on the source and should
be linked with the compiled object files and libraries of the modules.
As an example you can look at the variation `sbhttpd` that includes the
CGI and the MT module linked into it.

Type

    make XXX

And you should get your executable.

-----

[\[\<\<\<\]](ug_7.2.md) [\[\>\>\>\]](ug_9.md)
