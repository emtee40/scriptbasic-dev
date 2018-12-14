# Power operator (^)

[\[\<\<\<\]](ug_9.10.1.md) [\[\>\>\>\]](ug_9.10.1.2.md)

The power operator `a^b` calculates the b-th power of a.

The actual implementation of the power operator is quite complex. It
tries to be as precise as possible. In case the calculation can be
carried out using integer numbers only integer calculation is used. This
way no unnecessary rounding errors are introduced.

If the mantissa is positive then the calculation is definite. However
unlike other BASIC implementations ScriptBasic tries to calculate the
result of the power operator even when the mantissa is negative.
Actually power operator always results an integer or real number when
possible. The implementation internally uses complex numbers and in case
the imaginary part of the result is zero the real value is used as the
result.

If either of the operands are `undef` then the result is `undef`.

-----

[\[\<\<\<\]](ug_9.10.1.md) [\[\>\>\>\]](ug_9.10.1.2.md)
