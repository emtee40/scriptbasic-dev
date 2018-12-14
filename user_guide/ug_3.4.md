# Configuration

[\[\<\<\<\]](ug_3.3.md) [\[\>\>\>\]](ug_3.5.md)

To reach advanced features, like using system include files from
predefined directories or using dynamic modules you have to create a
configuration file. This configuration file is probably different for
most installation and reflects the directory structure, networking
environment and other specialties of your setup.

The format of the configuration file is binary. This is to speed up
configuration information reading. To create this binary format, you
have to edit the text format of the configuration file usually named
\``scriba.conf.lsp`' and have to convert it to binary format using the
command line

    scriba -k scriba.conf.lsp

The ScriptBasic executable using the option \``-D`' dumps binary
configuration files into text format. Note that this dump program will
not restore the comments of the original configuration file nor the line
breaks or spaces (except those in strings).

The format of the text file version of the configuration information is
simple. It contains the keys and the corresponding values separated by
one or more spaces and new lines. Usually a key and the assigned value
are written on a line. Lines starting with the character `;` are
comment.

The values can be integer numbers, real numbers, strings and
sub-configurations. Strings can either be single line started and
terminated by a single `"` character or multi-line strings starting and
ending with three `"""` characters, just like in the language
ScriptBasic.

Sub-configurations start with the character `(` and are closed with the
character `)`. The lists between the parentheses are keys and
corresponding values.

\[Former versions of ScriptBasic preceding version 2.0.0 did not allow a
configuration to have empty sub configuration. Version 2.0.0 and later
allow such a configuration part. This may happen in case the
configuration file is edited and all the keys in a subconfiguration is
commented out. This was a bug that was hard to spot. The later version
executed a clean up procedure when reading the text version of the
configuration file during configuration compilation and removes the sub
tree.\]

The keywords of the current version are:

  - `dll` defines the extension used for dynamic load libraries. This
    extension is used when a module is loaded and full path file name is
    not specified. If there are more than one extension specified only
    the first one is used.
    
    The string defined in this key is appended to the file name when
    ScriptBasic is loading a module. ScriptBasic does NOT insert the dot
    before the extension; therefore the key value should contain it.
    Thus the correct configuration is
    
        dll ".dll"

  - `module` defines the directory for dynamically loadable modules. You
    should define the full path to the dynamic load libraries. In the
    path name you can use forward or back slashes.
    
    ScriptBasic does not insert a slash between the file name and the
    directory path, therefore the key value should contain the trailing
    slash.
    
    If there are more than one values defined for this key ScriptBasic
    will search for the module in each directory defined in the order
    they are defined. The search finishes when the module is found and
    successfully loaded or if there are no more directories.

  - `include` defines the directory for system or module-include files.
    These files are included in the include statement specifying the
    file name as bare word without double quotes. You should define the
    full path to the files. In the path name you can use forward or back
    slashes.
    
    ScriptBasic does not insert a slash between the file name and the
    directory path, therefore the key value should contain the trailing
    slash.
    
    If there are more than one values defined for this key ScriptBasic
    will search for the module in each directory defined in the order
    they are defined. The search finishes when the module is found and
    successfully loaded or if there are no more directories.

  - `maxstep` defines the number of instructions to be executed before
    the program stops with error. This can be useful to limit CGI
    programs to run too long and consume too much memory and processor.
    That can happen either by error or because your programmer (customer
    in case you provide web hosting service) wants to degrade your
    service.
    
    Note that this limit is compared against the number of steps, which
    is more than the number of lines. For example the line
    
        a = b+3
    
    executed by two steps: an addition and an assignment command.
    
    If the value of this parameter is zero or if the parameter is not
    defined in the configuration file no limit is effective.

  - `maxlocalstep` defines the number of instructions allowed to be
    executed inside a function or subroutine before the program stops
    with error. This is limit is similar to `maxstep` and can serve the
    same purpose. This may help you fine tune program behavior. Usually
    setting `maxstep` is enough.
    
    If the value of this parameter is zero or if the parameter is not
    defined in the configuration file no limit is effective.

  - `maxlevel` defines the maximal level of recursive call deepness.
    Programs usually get into infinite loop because of incorrect
    recursive loop. This value can limit the maximum number of function
    calls nested. The binary version of ScriptBasic is shipped with a
    value appropriately set for this value. If you compile the program
    from source the installation process sets this value.
    
    If the value of this parameter is zero or if the parameter is not
    defined in the configuration file no limit is effective.

  - `maxmem` defines the maximum number of bytes that a basic program is
    allowed to use for its variables. The actual memory allocated by the
    process or thread running the interpreter may exceed this value
    because memory for the reader, lexical analyzer, syntax analyzer,
    code builder and external modules are not limited. This limits only
    the memory allocated for the ScriptBasic variables.
    
    If this value is zero or is missing then there is no limit except
    the limits of the operating system and the hardware.

  - `preload` defines the external modules that are always to be loaded
    before starting the basic program. There can be more than one
    modules defined. In this case the modules are loaded in the order
    they are specified.
    
    The name of the module should be specified the same way as in the
    ScriptBasic statement `declare sub`: either with full path including
    file extension or without path and extension. If only the name of
    the module is specified the module directories are searched by
    ScriptBasic to load the module defined by the configuration key
    module.

  - `cache` defines the directory where the program cache is stored.
    This should be an existing directory name including the final `\` or
    `/`. At each run the interpreter will check in this directory if the
    file was already compiled and a precompiled version is used if that
    is newer than the file.

  - `preproc` defines the external and internal preprocessors.
    
      - `extensions` Defines the extensions that external preprocessors
        are assigned to. Each key has to mach an extension and the value
        string has to be the symbolic name of the external preprocessor
        assigned to that extension.
      - `external` Each key in the sub-configuration is the symbolic
        name of an external preprocessor and the sub-configuration
        assigned to that key defines the directory where to store the
        result of the preprocessor and the command to start the
        preprocessor. Note that a space and the source file name are
        automatically appended after the command line.
      - `internal` Defines internal preprocessors. Each key in this list
        defines the name of the preprocessor and the value defines the
        DLL or SO file that implements the internal preprocessor. The
        key name should be used following the option \``-i`' or after
        the BASIC source program command `USE`.

ScriptBasic ignores all lines containing a key that it does not
understand. This is dangerous on one hand because it makes typing errors
less recognizable. On the other hand it allows different variations
share common configuration file. The external modules implemented as
dynamic load library functions can also access any configuration data.

An example configuration file from a Windows NT installation:

    ; scriba.conf
    ; ScriptBasic sample configuration file
    ;
    ; Note that this configuration file format is from v2.0b1 or later and has to be compiled
    ; to internal binary format before starting ScriptBasic
    
    ; this is the extension of the dynamic load libraries on this system
    dll ".dll"
    
    ; where the modules are to be loaded from
    module "d:\\MyProjects\\sb\\modules\\"
    module "d:\\MyProjects\\sb\\sysmodules\\"
    module "c:\\ScriptBasic\\modules\\"
    
    ; where to search system and module include files
    ; trailing / or \\ is needed
    include "d:\\MyProjects\\sb\\source\\include\\"
    include "c:\\ScriptBasic\\source\\include\\"
    
    
    ;
    ; define external preprocessors
    ;
    preproc (
    ; extensions that preprocessors are to be applied on
      extensions (
    ; here the key is the extension and the value is the symbolic name of the external
    ; preprocessor
         heb "heb"
         )
    ; the external preprocessors
      external (
        heb (
          executable "D:\\MyProjects\\sb\\Release\\scriba.exe d:\\MyProjects\\sb\\source\\heber.bas"
          directory "d:\\MyProjects\\sb\\hebtemp\\"
    
          )
        )
      )
    
    ;
    ; LIMIT VALUES TO STOP INIFINITE LOOP
    ;
    
    ; the maximal number of steps allowed for a program to run
    ; comment it out or set to zero to have no limit
    maxstep 30000
    
    ; the maximal number of steps allowed for a program to run
    ; inside a function.
    ; comment it out or set to zero to have no limit
    maxlocalstep 0
    
    ; the maximal number of recursive function call deepness
    ; essentially this is the "stack" size
    maxlevel 300
    
    
    ; the maximal memory in bytes that a basic program is allowed to use
    ; for its variables
    maxmem 1000000
    
    ;
    
    
    
    ; ScriptBasic loads the modules before starting the code
    ; in the order they are specified here
    ;
    ;preload "ext_trial"
    
    ;
    ; This is the directory where we store the compiled code
    ; to automatically avoid recompilation
    ;
    cache "d:\\MyProjects\\sb\\cache\\"
    
    cgi (
    ;
    
    ; These are the keys used by the CGI module
    ;
      debugfile "d:\\MyProjects\\sb\\cgidebug.txt"
      )

Although Windows NT programs are usually configured using the registry
or active directory services ScriptBasic uses a text file to ease and
maintain compatibility with UNIX versions.

To ease the compatibility even more the file names are allowed to use
the UNIX style forward slash `/` as directory separator character.

When the program starts one of its first action is to search the
configuration file. The search for the configuration file is different
on Windows NT and under UNIX operating system.

-----

[\[\<\<\<\]](ug_3.3.md) [\[\>\>\>\]](ug_3.5.md)
