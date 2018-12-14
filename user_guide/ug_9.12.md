# Operator Assignments

[\[\<\<\<\]](ug_9.11.md) [\[\>\>\>\]](ug_9.13.md)

Most of the times we assign the value of an expression to a variable,
which uses the variable itself. For example

    A = A + 1

increments the variable `A`. To ease programming ScriptBasic allows the
construct

    A += expression

instead of

    A = A + expression

This is a well known and widely used form by many languages, well
readable, though not BASIC like. Likewise programmers can write

    A -= expression instead of A = A - expression
    A *= expression instead of A = A * expression
    A /= expression instead of A = A / expression
    A \= expression instead of A = A \ expression
    A &= expression instead of A = A & expression

This is more readable for most of the programmers and results slightly
faster execution for addition, subtraction, multiplication, division,
integer division and string concatenation respectively.

-----

[\[\<\<\<\]](ug_9.11.md) [\[\>\>\>\]](ug_9.13.md)
