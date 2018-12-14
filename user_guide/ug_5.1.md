# Binary format of the BASIC code

[\[\<\<\<\]](ug_5.md) [\[\>\>\>\]](ug_6.md)

In this section we describe some features of the binary format of the
BASIC programs saved by ScriptBasic automatically into the cache
directory or to a file using the option \``-o`'. There is absolutely no
need to know or understand the binary format of ScriptBasic for those
who want to program in ScriptBasic. However advanced users may want to
perform some modification on binary format BASIC programs, like changing
the interpreter location in the start line. For those this section
describes the details.

The binary format is binary. It starts with some constant leading code
to ensure that no erroneous execution starts and to avoid memory
corruption. This leading code helps ScriptBasic to recognize the binary
format even if the interpreter was started without specifying the option
\``-b`'.

The binary format *may*, however start with a textual line specifying
the interpreter. This is needed to make the binary format file
executable on UNIX, for example to run a CGI program. This line is
interpreted by the UNIX operating system and is ignored by the
interpreter. Because this line has no meaning on Windows NT the line HAS
TO be terminated by a line feed and not CR/LF. You need not worry about
it, because this is created this way on Windows NT as well as on UNIX.
This first line is copied from the source BAS file when the binary
format is created.

You may want to change this line when you want to run the code on a
machine having the interpreter located at a different location. To do
this you can use the following sample ScriptBasic code:

    cmdlin = command()
    split cmdlin by " " to FileName,Interpreter
    open FileName for input as 1
    
    
    
    binmode 1
    File$ = input(lof(1),1)
    close 1
    if left(File$,1) = "#" then
      i = 1
      while i < len(File$) and mid(File$,i,1) <> "\n"
        i = i+1
      wend
      if mid(File$,i,1) = "\n" then
        File$ = "#!" & Interpreter & mid(File$,i,len(File$))
      end if
    
      open FileName for output as 1
      binmode 1
    
      print#1,File$
      close 1
    end if

This leading line is optional.

The first byte of the binary code (following the optional command line)
is the ASCII number of the size of a long on the actual platform. This
is currently 4 on Linux and Windows NT, Windows 95/8 and it is 8 for
Tru64 UNIX.

This is followed a magic code. This is `0x1A534142`. On DOS platforms
this is printed as `BAS^Z` and prevents dumping the code to the screen
if one attempts. This magic code is saved as a `long`. This means that
the order of the bytes follows the order of the bytes in a long in
memory on the machine the code was saved. This is followed by six long
values. These are

  - `VersionHigh` the high number of the ScriptBasic version
  - `VersionLow` the low number of the ScriptBasic version
  - `MyVersionHigh` the high number of the variation version
  - `MyVersionLow` the low number of the variation version
  - `Build` the build number of the version
  - `Date` coded date

The following eight bytes contain the name of the variation that created
the binary code. Because some variations do not differ in binary format
from the STANDARD variation they create binary file saying it being
STANDARD.

To successfully load a binary format file to run in ScriptBasic the long
size, the magic code, version information including the build and the
variation string should match. Date may be different.

Following this header the real information of the executable code is
placed. The following four long numbers present in order the

  - Number of global variables
  - The number of nodes in the code
  - The start node serial number
  - The size of the table containing the constant strings

Following this the nodes come one after the other. ScriptBasic prints
the size of a single node in bytes when the option \``-v`' is used. This
is usually 16bytes on 32bit systems and 24bytes on 64bit systems. If you
get smaller node size printed then you will face alignment problems. If
you get bigger node check your compiler options. ScriptBasic was not
tested on 128bit systems up to now.

The string table follows the nodes. This contains all the strings zero
character terminated that present in the code. There is at least a zero
valued byte in the string table even if the program does not contain any
string constant.

There can be arbitrary data following the string table, they are
ignored.

-----

[\[\<\<\<\]](ug_5.md) [\[\>\>\>\]](ug_6.md)
