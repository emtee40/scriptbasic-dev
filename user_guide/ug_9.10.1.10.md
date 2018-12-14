# Compare operators (\<, \<=, \>, \>=)

[\[\<\<\<\]](ug_9.10.1.9.md) [\[\>\>\>\]](ug_9.10.1.11.md)

These operators compare numeric and string values. The result of the
operation is `undef` if any of the operands is `undef`. If **any** of
the operands is string the operands are converted to string value and
string comparison is performed. If none of the operands is string but at
least one of the operands is float value then the operands are converted
to floating number and the comparison is done comparing floating
numbers. Otherwise the comparison is done with integer numbers.

The result of the operator is always -1, which is the internal value for
`TRUE` or 0, which is the internal value for `FALSE`.

-----

[\[\<\<\<\]](ug_9.10.1.9.md) [\[\>\>\>\]](ug_9.10.1.11.md)
