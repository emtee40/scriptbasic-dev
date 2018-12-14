# Trouble shooting installation

[\[\<\<\<\]](ug_3.7.md) [\[\>\>\>\]](ug_4.md)

Although installation is quite simple there can be some pitfalls that we
and our users have experienced during installing ScriptBasic. To help
you we list the possible error.

  - **Symptom** Some programs do not run, but claim that the binary
    version was created for a different build of ScriptBasic.
    
    **Cause and solution** There is binary cache file for the programs,
    which is younger than the source of the basic programs but was
    created by a previous installation. Delete the content of the cache
    directory.

  - **Symptom** Apache (or IIS) claims internal server error when
    running CGI scripts.
    
    **Cause and solution** There can be several causes. The most
    probable ones:
    
      - You forgot to start the program using `#! /usr/bin/scriba`
      - The basic program is not executable by `nobody` (or the web
        daemon user)
      - The code of ScriptBasic \``/usr/bin/scriba`' is owned by root
        and is not executable by the user `nobody`.
      - The configuration file contains invalid data.
      - The file names in the configuration miss the trailing `/`
    
    The Windows NT registry string `HKLM\Software\ScriptBasic\config` is
    missing or points to an invalid configuration file.

-----

[\[\<\<\<\]](ug_3.7.md) [\[\>\>\>\]](ug_4.md)
