# Cache handling shortages

[\[\<\<\<\]](ug_4.1.md) [\[\>\>\>\]](ug_4.3.md)

The cache directory contains the cached binary format program codes for
the BASIC programs executed. For each BASIC program a new file is
generated when the BASIC source code is analyzed and built.

The file name for the cache file is calculated using the file name. This
file name includes the full path to the file under Windows NT but is the
bare file name as supplied on the command line under UNIX.

This means that if you have two different programs named \``hello.bas`'
in two different directories and you run one after the other from their
directory issuing the command line under UNIX

    scriba hello.bas

the second execution will erroneously think that the cache file created
when the first one was running belong to this program and will execute
the binary code.

On the other hand if you execute the program \``hello.bas`' from two
different directories and the supplied paths are different the caching
mechanism will not realize that the two execution refer to the same
file.

Also note that cache handling does not compare the modification time of
the files that basic program includes. If the program itself does not
change, but an included file did the caching it will still run the older
version.

Caching usually works and in case you experience mysterious problems you
can try to avoid caching using the option \``-n`' or commenting out the
configuration line `cache`. Web servers usually specify full path to the
executed code and in that case cache file name conversion is correct.
Especially Apache does start CGI programs passing the full path to
ScriptBasic as argument and thus caching works well with this web
server.

It is recommended to switch the caching totally off during development
and switch on at the start of the test phase. On test environment delete
the cache frequently whenever you experience mysterious errors that you
think you have already corrected.

-----

[\[\<\<\<\]](ug_4.1.md) [\[\>\>\>\]](ug_4.3.md)
