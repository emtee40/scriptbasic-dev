# Integer division operator (\\)

[\[\<\<\<\]](ug_9.10.1.3.md) [\[\>\>\>\]](ug_9.10.1.5.md)

This operator divides the first operand with the second. If any of the
operands are `undef` then the result is `undef`. If the second operand
is zero then the result is `undef`. If one of the operands is a real
number then the calculation is carried out on real numbers and the
result is real. If the operands are integer then the calculation is
performed using integer numbers and the result is truncated towards
zero. String operands are automatically converted to numeric value. In
case the option

    OPTION RaiseMathError sbMathErrDiv

was used the operator will raise an error when the second argument is
zero.

-----

[\[\<\<\<\]](ug_9.10.1.3.md) [\[\>\>\>\]](ug_9.10.1.5.md)
