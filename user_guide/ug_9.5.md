# Constants

[\[\<\<\<\]](ug_9.4.md) [\[\>\>\>\]](ug_9.6.md)

Constants are values that the program can not alter. Unlike variables
constants have a single value and this value does not change during
program execution. The strings and numbers that are used in a program
are naturally constants. They are the simplest forms of constants
without a name. However you may want to name constant values. You could
store the value in a named location, in a variable but that consumes an
extra variable and slows down execution.

ScriptBasic allows you to define constants using the format:

    const name=value

or

    global const name=value

where *name* is an identifier and value is a string or a number. You can
not specify an expression as a value, only constant string or number.
Later you can use the name of the constant in any expression where you
could use the value of the constant. If you have the constant
declaration:

    Const nl = "\n"

then the following two lines are identical, they create the same
executed code and therefore execute the same speed and need the same
size of memory:

    print 6+6,nl
    print 6+6,"\n"

ScriptBasic evaluates named constants during syntax analysis and the
name of the constant is replaced by their defined value in the
expression where the constant is used.

Named constants are local to the subroutine or function they are defined
in unless you use the keyword `global`. If you declare a constant in a
module (see chapter [Name spaces](ug_11.md) for more on modules and
name spaces) the named constant becomes part of the name space and you
can refer to the constant only with full name space specification from
outside of the module. If you declare a named constant inside a function
or a subroutine without the keyword `global` the constant becomes local,
and can not be used outside of the subroutine or function.

If you use the keyword `global` the constant is declared global. This
means that the constant is not part of any name space and can be used
anywhere in the program after the line it was declared.

When ScriptBasic finds an identifier in an expression, which is not a
built-in function or reserved word it checks the followings until a
check succeeds:

  - Checks if the identifier is a local constant of the current function
    or subroutine. This check is skipped if the expression is inside of
    any function or subroutine.
  - Checks if the identifier is a constant of the current name space.
  - Checks if the identifier is a global constant.
  - Checks if the identifier is a local variable of the current function
    or subroutine. This check is skipped if the expression is not inside
    of any function or subroutine.
  - If all above checks fail the identifier is treated as global, module
    specific variable.

Constants can be redefined. When a named constant is defined in a const
statement ScriptBasic does not check if the constant has already be
defined. It is legal to change the actual value of a constant during
compile time. Note however, that this does not make a constant to be a
variable. The change of the value is performed during syntax analysis
and not during execution. `Const` statements do not generate any
executable code and therefore are never executed.

When an identifier is declared as a constant the identifier can not be
used as variable in an expressions following the program line that
defines the constant. Sometimes you want to delete a defined constant
and use the identifier as variable again. To use an identifier as a
variable that was already defined as constant you can use the command

    var name

where the `name` is the identifier. This declaration tells ScriptBasic
that the identifier is not a constant anymore. This declaration is
similar to the normal, non-global const declaration. If you write a
`var` statement inside a function or subroutine the identifier becomes a
local or module specific global variable in the function or subroutine
only. If you write a `var` statement outside any function or subroutine
the identifier becomes a variable in the module only.

To explain the behavior let us see an example:

    module TEST
    a = "GLOBAL VARIABLE"
    Global Const a = "a "
    
    Const b = "b "
    
    sub TestSub
      const c = "c "
      ' all three identifiers are constants here
      print "  values in TestSub=",a,b,c,"\n"
      ' from now on until end of the sub
      ' 'a' is a variable (global or local)
      var a
    
      ' here 'a' is a global variable
      print "a in sub as a global variable holds the value=",a,"\n"
    
    
      ' now a is defined to be a local variable from now on
      ' until the end of the subroutine
      local a
      a = "LOCAL VARIABLE"
      print "a in sub=",a,"\n"
    end sub
    
    ' 'a' and 'b' are constants here again as 
    ' 'var' declaration was inside the sub
    print "values in the module=",a,b,c,"\n"
    
    print "values called from within the module:\n"
    TestSub
    
    ' 'a' is a variable from now on (global only
    '                                as we are global here)
    var a
    
    ' here a is a global variable again
    print "a in module=",a,"\n"
    
    end module
    
    ' here 'a' is a global const (var a was inside the module)
    ' --
    ' 'b' was const but not 'global const', so here it is
    ' a global variable again
    ' --
    ' 'c' was inside the module, inside the sub. Here it is
    ' totally undef
    print "values outside the module=",a,b,c,"\n"
    
    print "values called from outside the module:\n"
    TEST::TestSub
    var a
    print "a in global=",a,"\n"

The output is:

    values in the module=a b undef
    values called from within the module:
      values in TestSub=a b c
    a in sub as a global variable holds the value=GLOBAL VARIABLE
    a in sub=LOCAL VARIABLE
    a in module=GLOBAL VARIABLE
    values outside the module=a undefundef
    values called from outside the module:
      values in TestSub=a b c
    a in sub as a global variable holds the value=GLOBAL VARIABLE
    a in sub=LOCAL VARIABLE
    a in global=undef

To help understand even deeper the behavior of local, global, module
specific constants and variables here we present a short description how
the syntax analyzer handles the constants. You need read this only if
you are curious.

There are several symbol tables during syntax analysis. ScriptBasic
maintains a symbol table

  - for the labels,
  - one for global variables,
  - one for local variables and
  - a separate one for constants.

When a constant is defined the name and the corresponding value gets
into this symbol table. If the const statement is global the name is not
altered. If the const statement is not global the name is modified to
include the name space. This modification is the same as the
modification for variables. After this modification an apostrophe
character is appended to the constant name and the name of the actual
function or subroutine if the constant is defined inside one. This is
the same name decoration mechanism, which is performed for the labels.

When an identifier is found in an expression the syntax analyzer
searches for the name `module::constname'function` in the symbol table
if the expression is inside a function or subroutine. If the expression
is in a global area - out of any subroutine or function - this search is
not performed. If there is no such entry in the symbol table the
analyzer searches for the symbol `module::constname'`. If this symbol is
still not defined in the symbol table the analyzer searches `constname`.

If any of the names can be found in the symbol table the identifier
`constaname` is replaced in the token list with the value of the
constant.

When a `var` statement declares an identifier to be constant it actually
does a weird action inside the interpreter. It redefines the constant
name `module::constname'` or `module::constname'function` to be
associated with the value `NULL`. In other words, when the syntax
analyzer finds the constant name in the symbol table and retrieves the
pointer that is supposed to point to the constant replacement lexical
element it gets a pointer with `NULL` value. But it does find the
constant name in the symbol table and the search finishes successfully.
On the other hand the next step in the syntax analysis sees only the
`NULL` value in the constant replacement pointer and thinks that no
constant was found.

This means that if the basic program has a global constant and we
declare the identifier to be a variable using a `var` statement the
constant search stops when it finds it to be a local (either function or
subroutine local or module local) constant. A local constant that
happens to have a replacement pointer pointing to `NULL`. And it does
not search for the global constant, because it did find a symbol table
entry.

The same situation happens if a module constant is redefined using the
`var` statement inside a subroutine or function.

ScriptBasic defines some named constants before it starts analyzing the
program. These named constants always start with the letters `sb`, and
their purpose is to help the programmer to set various options in option
statements.

The global constants defined by the ScriptBasic interpreter are:

  - `sbCaseSensitive`
  - `sbCaseInsensitive`
  - `sbMathErrDiv`
  - `sbMathErrUndef`
  - `sbMathErrUndefCompare`
  - `sbCollectDirectories`
  - `sbCollectDots`
  - `sbCollectRecursively`
  - `sbCollectFullPath`
  - `sbCollectFiles`
  - `sbSortBySize`
  - `sbSortByCreateTime`
  - `sbSortByAccessTime`
  - `sbSortByModifyTime`
  - `sbSortByName`
  - `sbSortByPath`
  - `sbSortAscending`
  - `sbSortDescending`
  - `sbSortByNone`
  - `SbTypeUndef`
  - `SbTypeString`
  - `SbTypeReal`
  - `SbTypeInteger`
  - `SbTypeArray`

These constants are defined by the interpreter and there is no need to
include any file to use these constants. Other constants are defined in
various header files.

-----

[\[\<\<\<\]](ug_9.4.md) [\[\>\>\>\]](ug_9.6.md)
