' """
FILE: slre.bas

This is the BASIC import file for the module slre.

This file was generated by headerer.pl from the file interface.c
Do not edit this file, rather edit the file interface.c and use
headerer.pl to regenerate this file.
"""

module slre

declare sub     ::m alias "match"   lib "slre"
declare sub     ::$ alias "dollar"  lib "slre"
' FUNCTION DECLARATIONS 
declare sub     ::match  alias "match"  lib "slre"
declare sub     ::n      alias "nmatch" lib "slre"
declare sub     ::dollar alias "dollar" lib "slre"

end module