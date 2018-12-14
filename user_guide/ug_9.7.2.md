# Array index limits

[\[\<\<\<\]](ug_9.7.1.md) [\[\>\>\>\]](ug_9.7.3.md)

Because array indices are automatically adjusted the lower and upper
limit of indices of an array are not constant. They may change. To get
the lowest and the highest index of an array that has assigned value
(possibly `undef`) you can use the function `lbound` and `ubound`. The
names stand for lower bound index and upper bound index.

For example the simple program

    a[1] = undef
    print lbound(a)," ",ubound(a)
    print
    
    a[2,-3] = "whoops"
    print lbound(a)," ",ubound(a)
    print
    print lbound(a[2])," ",ubound(a[2])
    print

will print

    1 1
    1 2
    -3 -3

As you can see the argument to these functions can be a variable that
has array value or an expression that has an array value. (Such an
expression is likely to be an array element, which is an array by
itself.)

When the argument is not an array the functions returns `undef`.

-----

[\[\<\<\<\]](ug_9.7.1.md) [\[\>\>\>\]](ug_9.7.3.md)
