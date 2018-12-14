# Creating arrays

[\[\<\<\<\]](ug_9.7.md) [\[\>\>\>\]](ug_9.7.2.md)

Any variable can become an array. In ScriptBasic arrays are
automatically created. There is no statement like `DIM`. All you have to
do is to use the variable like an array. Array subscripts are written
using square brackets. This is usually the convention in PASCAL and in
C. Other BASIC languages use normal parentheses to index arrays. That
confuses the reader as well as the parser, because function call looks
the same as array access. Therefore ScriptBasic uses the square
brackets.

There is no limit on the number of indices. You can use as many as you
like. Also there is no limit on the index values other than the index
values have to be integer and that memory may limit the array sizes.
Positive, negative or zero integers can play the role of an index.
Whenever you access an array element or assign a value to that
ScriptBasic automatically checks if the referenced array element exists
or not and adjusts the array if necessary. For example:

    a[1] = 3
    a[5]=4
    for i=1 to 5
    print a[i]
    print
    next

is perfectly legal and prints:

    3
    undef
    undef
    undef
    4

Arrays are handled quite liberal. You are not required to declare the
index bounds, you need not declare the number of indices. As a matter of
fact you can have different number of indices at different points in the
array. For example the following code is also legal:

    a[1] = 3
    a[5,3]=4
    print a[1],"\n",a[5,3]

You can even write:

    a[1] = 3
    a[5,3,1,6,5,4,3,6,4,3,2222]=4
    print a[1],"\n",a[5,3,1,6,5,4,3,6,4,3,2222]

if you wish.

What happens if you write:

    a[1] = 3
    a[5,3]=4
    print a[1],"\n",a[5]

ScriptBasic will print

    3
    ARRAY@#008C0BC8

or some similar message. What has happened? To understand we have to
explain how ScriptBasic stores the arrays.

An array in ScriptBasic is stored as a list of C pointers. When a
ScriptBasic variable first time used as an array a new array of a single
element is created. It has one element assigned to the index that was
referenced.

    VARIABLE[6] = 555

Later, when other elements are referenced the array is automatically
extended. For example if the array was first time referenced using the
index 6 and it was accessed second time using the index 11 ScriptBasic
automatically extends the array to contain six elements.

    VARIABLE[11] = "a string"

This means that an array can consume significant memory even if only a
few indices are used.

    VARIABLE[10,3] =6.24E3

When an array element, let's say index 10 is used with a second index,
let's say with 3 a new one-element array is created. Later this new
array is treated the same as the one assigned to the variable itself,
and when the element

    VARIABLE[10,6] = 55

is set it is enlarged to be able to hold all values between indices 3
and 6.

When the variable in our example named VARIABLE gets a new value, like

    VARIABLE = "NEW VALUE"

the arrays are released automatically.

When accessing an array element, which is an array itself ScriptBasic
tries to do its best. However the result may not be what you expect.

-----

[\[\<\<\<\]](ug_9.7.md) [\[\>\>\>\]](ug_9.7.2.md)
