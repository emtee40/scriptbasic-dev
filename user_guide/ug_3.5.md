# Configuration file location under Windows NT

[\[\<\<\<\]](ug_3.4.md) [\[\>\>\>\]](ug_3.6.md)

Win32 installation first tries to open the file \``scriba.conf`' if it
exists in the same directory as the executable file. This is a
convenient place to store the configuration file and does not require
registry editing to install ScriptBasic. This is also the ultimate place
for CD ROM products utilizing ScriptBasic that need running
instantaneously without any installation.

If the file \``scriba.conf`' does not exist in the directory of the
executable the configuration manager tries to open the file, which is
specified in the string value, named `config` under the registry key
`HKEY_LOCAL_MACHINE\Software\ScriptBasic`. If there is no name specified
in this registry value ScriptBasic tries to locate the configuration
file \``scriba.ini`' in the system directory. The system directory is
determined reading the environment variable `windir`. If this
environment variable does not exits ScriptBasic tries `systemroot`. It
should usually exist on normal Windows installation. If ScriptBasic can
not find even this environment variable it tries \``C:\WINDOWS`' as
final try. If no configuration file can be found ScriptBasic tries to
execute the program without configuration information.

Note that if for example \``C:\WINNT\scriba.ini`' exists and is valid,
but the registry defines a different and a non-existent or invalid file
ScriptBasic will fail to load the configuration file. It will try to
read the file specified in the registry. The other file options are
searched when the registry key does not exist or is empty.

If the command line uses the option \``-f`' then the argument of the
option is used as configuration file and this overrides all
configuration search algorithm. If the file specified in the option
\``-f`' does not exists then ScriptBasic runs without configuration.

-----

[\[\<\<\<\]](ug_3.4.md) [\[\>\>\>\]](ug_3.6.md)
