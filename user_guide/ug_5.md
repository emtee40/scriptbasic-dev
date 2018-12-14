# Compiling BASIC programs

[\[\<\<\<\]](ug_4.3.md) [\[\>\>\>\]](ug_5.1.md)

BASIC programs can be compiled to a tokenized form, to C code or to an
executable file.

The tokenized format is the internal format of ScriptBasic and this is
always generated before executing a BASIC program. To speed up execution
ScriptBasic is capable saving this code into cache files automatically.
However in some situation you may want to save this format into a
separate file. To do this you have to issue the command

    scriba -no myprogram.bbf myprogram.bas

This will save the code into the file \``myprogram.bbf`'. After having
this file you can execute the BASIC program issuing the command

    $ scriba -b myprogram.bbf

or

``` 




$ scriba myprogram.bbf
```

On UNIX you can make the compiled file to be executable setting the
permissions

    $ chmod u+x myprogram.bbf

and after that you can just write:

    $ ./myprogram.bbf

Please note that binary format files may not be executed on different
versions or builds of ScriptBasic and are not movable from one platform
to another. You may be lucky to execute Windows NT and Linux version
`bbf` files on the other platform, but this is not a guaranteed feature.
You surely can not run the binary format generated on a DEC OSF/1
(ooops, sorry Tru64 UNIX) on a 32 bit system.

-----

[\[\<\<\<\]](ug_4.3.md) [\[\>\>\>\]](ug_5.1.md)
