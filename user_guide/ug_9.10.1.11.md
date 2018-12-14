# Logical operators (and, or, xor)

[\[\<\<\<\]](ug_9.10.1.10.md) [\[\>\>\>\]](ug_9.10.1.12.md)

These operators can be used for both logical and bit-wise operators.
ScriptBasic does not have a separate type for logical values. Boolean
values are stored in integer storage. The logical `TRUE` is represented
as integer value -1 and the logical `FALSE` is 0. In other words the
logical `TRUE` is an integer value, which is represented by a memory
location of n bytes having all bits set to 1. On the other hand logical
`FALSE` is an integer value represented by a memory location of n bytes
having all bits reset.

The operators and, `or` and `xor` perform the calculation on integer
values, If any of the operands is not integer it is converted to integer
value before the operation takes place. The operations are performed on
each bit of the operands.

This means that the operators can also be used for logical operations.

-----

[\[\<\<\<\]](ug_9.10.1.10.md) [\[\>\>\>\]](ug_9.10.1.12.md)
