# Division operator (/)

[\[\<\<\<\]](ug_9.10.1.2.md) [\[\>\>\>\]](ug_9.10.1.4.md)

This operator divides the first operand with the second. If any of the
operands are `undef` then the result is `undef`. If the second operand
is zero then the result is `undef`. If one of the operands is a real
number then the calculation is carried out on real numbers and the
result is real. If the operands are integer, but the calculation can not
be performed to result an integer number without remainder then the
operand values are converted to real. If both of the operands are
integers and there is no remainder after the division the result is
integer. String operands are automatically converted to numeric value.
In case the option

    OPTION RaiseMathError sbMathErrDiv

was used the operator will raise an error when the second argument is
zero.

-----

[\[\<\<\<\]](ug_9.10.1.2.md) [\[\>\>\>\]](ug_9.10.1.4.md)
