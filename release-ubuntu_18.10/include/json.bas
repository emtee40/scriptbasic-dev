' """
FILE: json.bas

This is the BASIC import file for the module json.

This file was generated by headerer.pl from the file interface.c
Do not edit this file, rather edit the file interface.c and use
headerer.pl to regenerate this file.
"""

module json

' FUNCTION DECLARATIONS 
declare sub     ::load    alias "load"    lib "json"
declare sub     ::save    alias "save"    lib "json"
declare sub     ::count   alias "count"   lib "json"
declare sub     ::object  alias "object"  lib "json"
declare sub     ::get     alias "get"     lib "json"
declare sub     ::new     alias "new"     lib "json"
declare sub     ::settext alias "settext" lib "json"
declare sub     ::setnum  alias "setnum"  lib "json"

end module
