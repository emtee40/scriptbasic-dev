# Not equal operator (\<\>)

[\[\<\<\<\]](ug_9.10.1.8.md) [\[\>\>\>\]](ug_9.10.1.10.md)

This operator compares the operands. If both operators are `undef` the
result is 0, which is the internal value for `FALSE`. If only one of the
operands is `undef` then the result is -1, which is the internal value
for `TRUE`. In other words `undef` is equal to `undef`, but nothing
else.

If **any** of the operands is string then the comparison is done on
strings. The non-string operand if any is converted to string. String
comparison is case sensitive. Two strings are equal iff they are the
same length and contain the same valued bytes in the same order.

If the operands are numeric and at least one of them is a real number
then the comparison is done on real numbers. Otherwise the comparison is
done on integer numbers.

The result of the operator is always -1, which is the internal value for
`TRUE` or 0, which is the internal value for `FALSE`.

Later versions may change the behavior of this operator in case of
string comparison allowing case-insensitive comparison.

-----

[\[\<\<\<\]](ug_9.10.1.8.md) [\[\>\>\>\]](ug_9.10.1.10.md)
