# Equality operator (=)

[\[\<\<\<\]](ug_9.10.1.7.md) [\[\>\>\>\]](ug_9.10.1.9.md)

This operator compares the operands. If both operators are `undef` the
result is -1, which is the internal value for `TRUE`. If only one of the
operands is `undef` then the result is zero, which is the internal value
for FALSE. In other words `undef` is equal to `undef`, but nothing else.

If **any** of the operands is string then the comparison is done on
strings. The non-string operand if any is converted to string. String
comparison is case sensitive by default, but you can alter this behavior
using the statement option. Two strings are equal iff they are the same
length and contain the same valued bytes in the same order.

If the operands are numeric and at least one of them is a real number
then the comparison is done on real numbers. Otherwise the comparison is
done on integer numbers.

The result of the operator is always -1, which is the internal value for
`TRUE` or 0, which is the internal value for `FALSE`.

To alter the behavior of case sensitive comparison you can use the
statement

    option compare sbCaseInsensitive

The comparing operator looks at the option "compare" and decides how to
compare two strings. The global constant `sbCaseInsensitive` is
pre-declared by ScriptBasic and can be used anywhere in your program. To
switch back to case sensitive comparison you have to issue the command

    option compare sbCaseSensitive

The global constant `sbCaseSensitive` is also a pre-declared constant.
Note that the option "compare" is also used by the pattern-matching
operator like and also alters the behavior of directory listing under
UNIX.

-----

[\[\<\<\<\]](ug_9.10.1.7.md) [\[\>\>\>\]](ug_9.10.1.9.md)
