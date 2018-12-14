# ByVal operator

[\[\<\<\<\]](ug_9.10.1.12.md) [\[\>\>\>\]](ug_9.10.1.14.md)

This operator is a very special one. This actually does nothing but
results the operand unaltered. Why to have such an operator? The reason
is to help calling functions and passing arguments by value. When an
expression is passed as an actual value for a function argument it is
passed by value. In other words the function gets the value of the
expression. When a variable is used as the actual argument for the
function the function gets the variable and not the value. Of course the
function can use the value of the variable, but when it alters the
variable, the original variable is also changed. To avoid this you can
use the operator `ByVal` in front of the variable, which is passed to a
function as argument. In this case the argument is not a variable
anymore, but rather an expression and thus the called function or
subroutine can not alter the value of the argument variable.

-----

[\[\<\<\<\]](ug_9.10.1.12.md) [\[\>\>\>\]](ug_9.10.1.14.md)
