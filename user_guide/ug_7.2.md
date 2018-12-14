# Compilation under UNIX

[\[\<\<\<\]](ug_7.1.md) [\[\>\>\>\]](ug_8.md)

The UNIX installation puts \``libscriba.a`' in the directory
\``/usr/local/lib`'. This means that you can use the `gcc` option
\``-l`' to specify this library. Therefore the command line to compile
the generated C file is:

    $ gcc -o myprogram myprogram.c -lm -ldl -lpthread -lscriba

This will compile the ScriptBasic generated \``myprogram.c`' to the
executable \``myprogram`'.

-----

[\[\<\<\<\]](ug_7.1.md) [\[\>\>\>\]](ug_8.md)
