# Using external preprocessor

[\[\<\<\<\]](ug_9.15.md) [\[\>\>\>\]](ug_9.17.md)

An external preprocessor is a stand-alone program that lets the
programmer easily extend the language. The simplest available external
preprocessor is the HEB preprocessor that lets a programmer embed
ScriptBasic into HTML. This preprocessor is written in ScriptBasic and
converts HTML embedded ScriptBasic code into pure ScriptBasic.

When ScriptBasic recognizes that an external preprocessor is to be
started it does not read the source file but starts the external
preprocessor and uses the file created by that. The external
preprocessor should be an executable program that gets at least two
arguments: the name of the file to preprocess and the file name to
create; containing the preprocessed text.

The external preprocessor exits with the code zero in case it was
executing successfully and should exit with the code 1 if an error
occurred and the output file can not be used. This is the usual UNIX
exit code convention for processes.

There can be more than one external preprocessors applied to a program.
In case there are more than one preprocessors applied to a file then
ScriptBasic starts each of them one after the other each getting the
output file of the previous to work on.

The preprocessors should be configured in the configuration file before
ScriptBasic can execute any of them. Each preprocessor should have a
symbolic name. This is the choice of the person who configured the
ScriptBasic installation. You can name a preprocessor as you like, it
will not alter the behavior.

For example the HTML embedded basic preprocessor is named `heb` in the
sample configuration file. To use this preprocessor you can use the
option \``-p`' on the command line following with the name of the
preprocessor:

    # scriba -p heb myheb.bas

You can also assign file extensions to preprocessors. The sample
configuration file contains the line:

    epreproc$heb heb

This means that the extension `heb` is assigned to the preprocessor
`heb`. Well, this is a stupid example because the extension is the same
as the symbolic name of the preprocessor, but usually this is the
convention. The extension stands after the `$` sign and the symbolic
name of the preprocessor is the value of the configuration line. Thus

    epreproc$extension preprocessor_symbolic_name

You can assign the same preprocessor to many extensions, for example:

    epreproc$heb heb
    epreproc$htb heb
    epreproc$hb heb

can exist in the same configuration file. Whenever ScriptBasic processes
a source file with the extension `hb` it will start the HEB external
preprocessor.

A file may have multiple extensions. These are worked up from left to
right. For example the command:

    # scriba sample.heb.sql.bas

will start ScriptBasic starting first the preprocessor assigned to the
extension `heb`, then the preprocessor assigned to the extension `sql`
and finally the preprocessor assigned to the extension `bas`. If there
is no preprocessor assigned to some of the extensions then they
eventually will not be executed. This is not an error. (Note that there
is no `sql` preprocessor currently for ScriptBasic, this is an
artificial example.)

This behavior lets you to chain preprocessors.

External preprocessors have to be configured. You have to tell
ScriptBasic what program to use for the specific preprocessing. To do
this you have to use the configuration line:

    eprep$exe$heb /usr/bin/scriba heber.bas

This configuration line tells ScriptBasic that the executable of the
preprocessor having the symbolic name `heb` is `scriba heber.bas`. This
is not actually the name of an executable. This is the start of the
command line. The first element of it should be the name of the
executable. The next elements are the command line options that precede
the input and the output file name. Using this configuration line
ScriptBasic will start another issue of ScriptBasic with the command
line:

    #/usr/bin/scriba heber.bas sample.heb.bas outputfile

where `sample.heb.bas` is the HTML embedded BASIC code we actually want
to execute; \``outputfile`' is the file that the preprocessor has to
create. When this process finishes ScriptBasic reads the generated
output and executes the program.

Of course you can use any other executable as preprocessors. You can
write preprocessors in C, C++, Perl or in any other language that can be
started on the command line, is capable reading and writing file and is
able to signal error via exit code. Note that ScriptBasic exists with
the last non caught error code.

Before ScriptBasic is able to start the external preprocessor it has to
calculate the name of the output file that the preprocessor has to
write. Each preprocessor has to be configured to use a temporary
directory to store the preprocessed file. To specify the directory you
have to use the configuration line:

    eprep$dir$heb /etc/temp/heb/

This means that the temporary directory for the files created by the
preprocessor with the symbolic name "heb" is the directory
\``/etc/temp/heb/`'. When a file is to be preprocessed with this
preprocessor ScriptBasic calculates a unique file name based on the name
of the source file and asks the external preprocessor to put the result
into that file in this directory. Finally the command line that
ScriptBasic starts for the example above
    is:

    #/usr/bin/scriba heber.bas sample.heb.bas /etc/temp/heb/EACAPAOALAEAHAHAAANAJAOALAGAKAPA

The algorithm used to calculate the unique file name is the same as for
the cache file name.

-----

[\[\<\<\<\]](ug_9.15.md) [\[\>\>\>\]](ug_9.17.md)
