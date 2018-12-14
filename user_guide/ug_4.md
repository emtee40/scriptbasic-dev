# Code caching

[\[\<\<\<\]](ug_3.8.md) [\[\>\>\>\]](ug_4.1.md)

The interpreter has to do several things before actually starting the
BASIC code. It has to read the file, split it into tokens, analyze the
program and build the internal executable format. This takes a lot of
time especially for programs longer than a few lines. This can be
skipped if the code built up is saved into a file and the file is loaded
and run without the recompilation.

To save the binary format file after the BASIC program was analyzed and
build the \``-o`' option can be used. To load and run the code the
binary file can be used instead of the text file containing the BASIC
code. The interpreter automatically recognizes the binary format and
does not try to interpret it as BASIC program source. To help the
interpreter you can also supply the option \``-b`' on the command-line
that tells the interpreter to believe without checking that the file is
binary format of the basic program. This is one solution to speed up
execution of the ScriptBasic programs and to avoid recompilation of the
code several times. The other method is caching.

The configuration file (see section [Installation
Instructions](ug_3.md)) may contain a value for the key `cache`. The
value for this key should specify a readily existing directory (do not
forget the trailing `/` or `\`) where the BASIC interpreter can store
the binary format of the code. If there is a valid value specified as
cache directory the interpreter checks the cache for an already existing
binary format file and if that is newer than the BASIC source it
neglects the BASIC source and loads the binary format from the cache.

On the other hand whenever a BASIC source code was analyzed and built
the resulting binary code is saved into the cache. This method is
transparent for the user and significantly speeds up program execution
especially for CGI programs that run many times.

To avoid cache using you can use the command-line option `-n`.

Caching has some limitation that can result unwanted behavior. Before
switching on program code cache, please read the following sections that
describe the shortages and the security issues that should be
considered.

-----

[\[\<\<\<\]](ug_3.8.md) [\[\>\>\>\]](ug_4.1.md)
