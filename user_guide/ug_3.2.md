# Installation under Linux

[\[\<\<\<\]](ug_3.1.1.md) [\[\>\>\>\]](ug_3.3.md)

To install ScriptBasic under Debian Linux is as simple as typing

    dpkg --install scriba-v2.0b1-1_i386.deb

If you happen to install ScriptBasic on a RedHat Linux then you can
download the RPM version of the program and say

    rpm -i scriba-2.0b1-1.i386.rpm

This will install and configure ScriptBasic form most of the systems. In
case the directory structure of the standard installation does not fit
your needs then you can edit the configuration file scriba.conf.unix.lsp
and convert it to binary version using the command line:

    #/usr/bin/scriba -k scriba.conf.unix.lsp 

This is the default configuration file that ScriptBasic reads and all
other directories and locations are taken from this file.

In case you want to create a version of ScriptBasic that links some
external modules statically or want to play around with the source then
you have to recompile the source. Because this is the standard
installation mode for any operating system that is not Windows nor
Linux, read on in the next section how to do it.

-----

[\[\<\<\<\]](ug_3.1.1.md) [\[\>\>\>\]](ug_3.3.md)
