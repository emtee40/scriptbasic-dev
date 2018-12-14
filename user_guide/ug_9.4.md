# Variables

[\[\<\<\<\]](ug_9.3.md) [\[\>\>\>\]](ug_9.5.md)

Variables are core entities of ScriptBasic. Variables are used to store
string, real or integer values. Variable names start with alpha
characters, underscore, dollar sign or colon, and from the second
character they may contain digit characters in addition to all these
characters. The last character of a variable name should not be colon.

Whenever you need a variable choose a meaningful name. If you are a real
old BASIC programmer use trailing `$` to denote string variables.
However ScriptBasic can store any value in any variable, one at a time
of course.

The colon as a name character is allowed to help name space management,
and you should use it only for the purpose.

The following are valid and invalid variable name examples:

    myvariable   This is a perfectly legal variable name.
    main::var    This is OK. This variable is in the name space main.
    chr$         This is invalid. Chr$ is a reserved word,
                 this is a built-in function
    apple$       This is OK. You will use it probably to store strings.
    b:2          This is valid, but it is recommended not to use : inside
                 variable names, because it is unreadable.
                 Use colon only to separate hierarchical name space and
                 variable name.
    
    _mother      If it is your taste to start a variable with underscore you can.
    Beee$bop     Valid, but it is not recommended. The dollar sign is allowed in
                 variable names to allow the usual BASIC string variable notation.
                 System or application specific extensions may use predefined global
                 variable names that contain a $ sign inside. Using such variable
                 names you may get into conflict.
    ::boo        This is valid. This variable is explicitly noted to be in the
                 current name space.
    
    _::baa       This is valid. The variable is in the parent name space.
    ::chr$       This is valid, even though chr$ is a predefined function.

For more information on name spaces read the chapter [Name
spaces](ug_11.md).

Variables can contain any data in ScriptBasic. There is nothing like
integer or string variable. A variable may contain integer value at a
time a real value another time and string value later. You can use a
variable name to use real, integer or string value at a time; later you
may use the variable as an array; later as a real again. You can change
it any time.

Variables can be local or global. Global variables are those that are
not declared but used (unless `declare option DeclareVars` is specified
in the code, or `declare option DefaultLocal` declaration is in effect).
Any variable by default is global unless it is declared to be local.
Local variables are local to the function or subroutine in which they
are declared to be local. To declare local variables you should use the
command `local`. (Note that it is possible to use the directive `declare
option DeclareVars` to require explicit variable declarations. This
directive is detailed later.)

    REM This is a sample program to demonstrate local variables
    
    
    'A is a global variable
    A=13
    Call MySUB
    Print A,"\n",B
    
    Sub MySUB
    Local A
    A=9
    B=55
    End Sub

The output of the program is

    13
    55

This is because the variable `B` inside the sub is global, but the
variable `A` is local and as such it does not alter the value of the
global variable `A`. You can define one or more variables to be local in
a local statement. If you declare more than one variable to be local
then you have to separate the variable names with commas.

-----

[\[\<\<\<\]](ug_9.3.md) [\[\>\>\>\]](ug_9.5.md)
