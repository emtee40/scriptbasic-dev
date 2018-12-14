# Expressions

[\[\<\<\<\]](ug_9.9.md) [\[\>\>\>\]](ug_9.10.1.md)

To calculate values you will need expressions. The simplest expression
is the one that contains only a constant number or string of the format
described in the previous sections. A bit more complex expression
contains variables, array elements, operators, function calls, and even
parentheses.

ScriptBasic expression format is much the same as that of many other
basic languages. The operators have precedence of the usual order, and
you can alter the order of operator evaluation using parentheses. The
operators are in order of precedence from the highest to the lowest:

  - `^` Power operator. `a^b` means `a` to the power `b`.
  - `*` Multiplication operator. This operator multiplies the operands.
  - `/` Division operator. This operator divides the left operand by the
    right operand and the result is usually a real number.
  - `\` Integer division operator. This operator divides the left
    operand by the right operand and the result is an integer.
  - `%` Modulus operator. This operator divides the left operand by the
    right operand and the result is the remainder after the division.
  - `+` Plus operator. This operator adds the operands and the result is
    the sum of the two operands.
  - `-` Minus operator. This operator subtracts the right operand from
    the left operand and the result is the signed difference of the two
    operands.
  - `=` Equality check operator. This operator checks if the operators
    are equal and results true if they are equal. Otherwise the result
    is false.
  - `<` Less than check operator. This operator checks if the first
    operand is less than the second operand and results true if yes.
    Otherwise it results false.
  - `<=` Less than or equal check operator. This operator checks if the
    first operand is less than the second operand or is equal to the
    second operator and results true if yes. Otherwise the result is
    false.
  - `>`Greater than check operator. This operator checks that the first
    operand is greater than the second one and it results true of yes.
    Otherwise it results false.
  - `>=` Greater than or equal check operator. This operator checks that
    the first operand is greater than the second operand or is equal to
    the second operand
  - `<>` Not equal check operator. This operator checks that the
    operands are NOT equal and it results true if they are not equal.
    Otherwise it results false.
  - `And` Logical and bit-wise AND operator. This operator calculates
    the logical and the bit-wise AND operation of the operands.
  - `Or` Logical and bit-wise OR operator. This operator calculates the
    logical and the bit-wise OR operation of the operands.
  - `Xor` Logical and bit-wise exclusive OR operator. This operator
    calculates the logical and the bit-wise exclusive OR operation of
    the operands.
  - `&` String concatenation operator. This operator concatenates the
    operands as strings.
  - `LIKE` Pattern matching operator.

These binary operators are evaluated from left to right. This means that
6-3+3 is 6 and not zero. This should be usual and obvious. 3 is
subtracted from 6 and the last 3 is added to the result of the
subtraction.

Operand types are not determined during compilation. There are no
integer, real or string variables in ScriptBasic, any variable can hold
any value (but only one at a time). Whenever a numeric operator gets a
string value it converts the value automatically to numeric. The
concatenation operator automatically converts the numeric operands to
string.

Operators that work with both numeric and string operands do not convert
the operands.

-----

[\[\<\<\<\]](ug_9.9.md) [\[\>\>\>\]](ug_9.10.1.md)
