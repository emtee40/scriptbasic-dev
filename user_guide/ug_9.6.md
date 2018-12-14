# Forcing Variable Declaration

[\[\<\<\<\]](ug_9.5.md) [\[\>\>\>\]](ug_9.7.md)

BASIC languages generally do not require variable declaration to be
programmer friendly. ScriptBasic is no exception for compatibility
reasons: you can write huge programs without declaring any variable.
Although this is possible this is not a good practice. Programmers can
easily mistype a variable name and end up getting a new variable with
`undef` value instead of getting compilation error. This may cost a lot
of debugging time.

To help programmers avoid such a situation ScriptBasic can be asked to
report any such variable as compilation error. However this also means
that the programmer has to declare the global variables. To tell
ScriptBasic that a certain part of the program or the whole program
requires variable declaration the programmer has to issue the
declaration

    declare option DeclareVars

This is a directive that does not generate any code, but tells the
compiler to require variable declaration. To declare global variables
the program should use the command `global`. For example

    declare option DeclareVars
    global a,b,c

declares three global variables `a`, `b` and `c`. The directive `declare
option DeclareVars` is effective from the line where the directive is.
Any undeclared variable used before the directive can also be used
without declaration after the directive as well. For example:

    a = 2
    declare option DeclareVars
    global b,c
    b = 3
    c = 4
    print a,b,c
    print

The variable `a` is implicitly declared before the directive and thus it
can be used even after the directive. Before the directive the global
variables are implicitly declared. As no global variable is allowed to
be declared more than once such an implicitly declared variable should
NOT be declared in a `global` declaration. For example

    a = 2
    declare option DeclareVars
    global a

generates compilation time error. Once you switched on the variable
declaration requirement, you should declare each new global variable
until the end of the program. This means that all included or imported
files should declare all global variables if you use the directive
before including or importing a file. Because this may pose some
incompatibility with older code you can use the directive

    declare option AutoVars

Following this line the declaration is implicit again until the end of
the program or until the next `declare option DeclareVars`. You can
switch on and off global variable declaration forcing as many times as
you like. It is also not an error to switch it on if this is already on,
or off it is already off. The compiler does not count however the number
of on and off directives. Thus

    declare option DeclareVars
    declare option DeclareVars
    declare option AutoVars

is just the same as

    declare option DeclareVars
    declare option AutoVars

or just the same as

    declare option AutoVars

It is always the last `declare option` directive, which is in charge.

Although you can mix program segments that require and do not require
global variable declaration it is recommended to issue `declare option
DeclareVars` at the start of the program and declare all global
variables.

-----

[\[\<\<\<\]](ug_9.5.md) [\[\>\>\>\]](ug_9.7.md)
