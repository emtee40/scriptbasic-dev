# Running CGI programs

[\[\<\<\<\]](ug_2.1.md) [\[\>\>\>\]](ug_2.3.md)

Although this topic should have been out of the scope of this
documentation it is described here in detail because of its importance.
Several users want to run ScriptBasic programs as CGI scripts.

Running CGI programs is just the same as running command line programs
if you are experienced configuring your web server. The major difference
is that it is the web server that starts the command line program and
not the shell (or command.exe).

Under UNIX you can start a ScriptBasic program the same way as any other
CGI scripts. The very first line of BASIC program should be

    #! /usr/bin/scriba

assuming that the executable code is called scriba and it is placed in
the directory /usr/bin. The text file containing the code should also be
executable for the user who runs the CGI scripts. This user is usually
called nobody. You may say

    $ chmod a+x hello.bas

to give all users execute permission. This may impose security questions
that we do not discuss here. You should really know what you are doing.

On Windows NT using Internet Information Server the situation is
different. Here you have to associate the extension with the executable
of ScriptBasic. Note that this is not the same association as the one
that allows the explorer to run the program when you double click on it.
You have to configure the association in the Internet Service Manager
configuration program.

You can also execute BASIC programs in the Eszter SB Application Engine
to generate web applications. In this case the Eszter SB Application
Engine has to be started from the command line or as a daemon under UNIX
or installed as a service under Windows NT. The BASIC programs are
executed inside the engine without starting a new process unlike in CGI
and thus execution is faster. Nevertheless the programs on the BASIC
programming level feel as if they were CGI programs, thus CGI programs
can be executed this way without any modification.

-----

[\[\<\<\<\]](ug_2.1.md) [\[\>\>\>\]](ug_2.3.md)
