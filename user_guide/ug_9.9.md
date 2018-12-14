# Using Array Mixed Mode

[\[\<\<\<\]](ug_9.8.1.md) [\[\>\>\>\]](ug_9.10.md)

Once you will reach a point when you want to use an array in a mixed
indexed mode. For example you want to handle an array of associative
arrays. In other words you want to have an array, of which each element
is an array itself.

For example you want to store the phone number, the room number and the
name of the dog for each of your employee. You have 78 employees in your
firm. In this case you need an array having 78 elements, each element
being an associative array itself, with the keys "phone", "room",
"dogname".

To do this you can

    FOR I=1 to 78
    
      PRINT I,". ",EMPLOYEE[I]{"phone"}," ",EMPLOYEE[I]{"room"},_
            " ",EMPLOYEE[I]{"dogname"},\n"
    NEXT I

You can mix the indices any order in any deepness. For example

    ARR{"1"}[2,3][3]{undef,"3",4}{"5"}[66]

is correct. What you can use it for is another question though.

Note that

    a[3][5]

is almost the same as

    a[3,5]

but the latter is a bit more efficient (due to ScriptBasic internal
algorithms). The details on differences can be read in the section
[Reference Variables](ug_19.md).

-----

[\[\<\<\<\]](ug_9.8.1.md) [\[\>\>\>\]](ug_9.10.md)
