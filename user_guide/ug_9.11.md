# Assignments (LET)

[\[\<\<\<\]](ug_9.10.1.16.md) [\[\>\>\>\]](ug_9.12.md)

Assignment is the most important command of languages. This is used to
assign calculated values of expressions to variables. You have already
seen examples of it but we did not discuss it in details so far. An
assignment is nothing else than a variable on the left side of an `=`
character and an expression on the right side.

The command calculates the expression first. The expression may contain
the variable that stands on the left side. In this case the variable
holds its original value while calculating the expression. When the
expression is fully evaluated the command releases the old value of the
variable and then assigns the new value just calculated.

The calculated value can be string, integer, real number, even undefined
or a whole array. The variable can be a global variable, local variable,
argument of a subroutine or function or element of an array. For
example:

    ' This assigns the value 18 to the variable A
    A = 13 + 5
    ' This assignes the value "apple" to the array element
    B[55] = "apple"

When the right hand side of the assignment is a whole array ScriptBasic
creates a copy of the array and the left hand side variable will hold
the new array.

Regarding evaluation order the assignment command first calculates the
variable on the left side of the command and then it calculates the
expression. Why is this important? There can be some special cases. Look
at the following example:

    function q
     z = z + 1
     q = z
    end function
    
    z =55
    a[q()] = z
    print a[56]

Will it print 55 or 56? Because the left side of the command is
evaluated first it does print 56.

Some BASIC implementations allow a keyword `LET` to be used before the
variable on the left side of the command before the variable. This is
rarely used by programmer and is not allowed by ScriptBasic.

-----

[\[\<\<\<\]](ug_9.10.1.16.md) [\[\>\>\>\]](ug_9.12.md)
