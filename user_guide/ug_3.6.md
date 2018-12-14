# Configuration file location under UNIX

[\[\<\<\<\]](ug_3.5.md) [\[\>\>\>\]](ug_3.7.md)

UNIX installations try to locate the configuration file from the
environment variable `SCRIBACONF`. This environment variable should
contain the configuration file name. If this environment variable does
not exist ScriptBasic tries to load the configuration data from the file
\``/etc/scriba/basic.conf`'.

Note that if the file defined in the environment variable `SCRIBACONF`
is non-existent or is invalid ScriptBasic does not try to load the
configuration from the default configuration file.

If you can not configure ScriptBasic configuration file name using
environment variables or the system registry under Windows NT you can
modify the source file \``scriba.c`'. You have to alter the function
`scriba_LoadConfiguration`.

If the command line uses the option \``-f`' then the argument of the
option is used as configuration file and this overrides all
configuration search algorithm. If the file specified in the option
\``-f`' does not exists then ScriptBasic runs without configuration.

-----

[\[\<\<\<\]](ug_3.5.md) [\[\>\>\>\]](ug_3.7.md)
