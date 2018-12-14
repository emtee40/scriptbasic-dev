# Bit-wise and logical NOT (NOT)

[\[\<\<\<\]](ug_9.10.1.6.md) [\[\>\>\>\]](ug_9.10.1.8.md)

This unary operator calculates the logical negate of the operand. The
calculation is done on integer numbers, thus the operand is converted to
integer value. The operator inverts each bit of the operand. If the
operand is `undef` the result is -1, which is the internal value for
TRUE.

Great care should be taken when using the NOT operator in logical
expressions. The precedence of the operator is higher than that of any
binary operator. Therefore the expression

    not true or false

is true, while

    not (true or true)

is false.

-----

[\[\<\<\<\]](ug_9.10.1.6.md) [\[\>\>\>\]](ug_9.10.1.8.md)
