# Numbers

[\[\<\<\<\]](ug_9.2.md) [\[\>\>\>\]](ug_9.4.md)

There are two types of numbers in ScriptBasic:

  - integer numbers and
  - real numbers.

The integer numbers can be used to represent integral values, while real
numbers can be used to represent number that have fractional part or are
too large to store as integer. The integer numbers are stored in a
memory location of size equivalent to a `long` of the programming
language C. The real numbers are stored internally as C `double`.

Number constants can be used in the basic program in the usual format.
Integer numbers are represented in either decimal or hexadecimal format.
Decimal numbers contain only digits. Hexadecimal numbers start with the
characters `0x` or `0X` and are followed by hexadecimal digits. The
format that many basic implementation follows using the `&H` characters
to start a hexadecimal number is also allowed. When a number contains a
`#` character inside, like `2#110111` then the number preceding the `#`
is the RADIX of the number and the characters following the `#` is the
number in the given radix. Because the limited number of characters in
the ABC the RADIX can go from 2 to 36 only. The following numbers are
valid integer constants in ScriptBasic:

  - `123`
  - `0xFF` equals to decimal `255`
  - `0x255` equals to decimal `597`
  - `0X0` is a hexadecimal zero
  - `&H52` equals to decimal `82`
  - `17#GG` is 288

There is no internal difference between decimal and hexadecimal numbers
for ScriptBasic. The lexical analyzer converts both format to internal
representation and stores the value of the number. In other words
wherever you are allowed to use a decimal number you are allowed to use
a hexadecimal number or any radix number as well. You should decide
whether to use decimal or hexadecimal or any other radix number for your
convenience taking care of BASIC source code readability.

Real number constants can only be decimal and may contain fractional and
exponential part. The followings are valid real number constants:

    3.14
    1.0
    1.
    2.3E-7
    
    2.3e7
    2.3E+7

Note that the exponent part is preceded by the character `e` or `E` and
is followed optionally be a sign. The number `1.` is a real number and
is stored in a C `double` internally although it could be integer.
ScriptBasic will store this number as a real number. However real
numbers are automatically converted to integer values whenever
ScriptBasic needs an integer value.

-----

[\[\<\<\<\]](ug_9.2.md) [\[\>\>\>\]](ug_9.4.md)
