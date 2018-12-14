# Deleting an array

[\[\<\<\<\]](ug_9.7.2.md) [\[\>\>\>\]](ug_9.8.md)

Usually there is no need to delete an array. Arrays are allocated when
they are needed and are released when they are not needed anymore.
However there may be some circumstances, when there is a need to
explicitly delete an array and release the memory assigned to the array.
To do this you have to use command `undef`. The name is the same as the
function `undef`, but instead of returning the undefined value this
command sets the variables listed after the command name to hold the
undefined value. The format is

    undef variable_list

The variable list may contain variables that are arrays, variables that
hold string, integer or real values and may also contain array elements,
like `a[13]`, which is a variable itself. When you apply the command
`undef` to a variable, which is not an array or reference the result is
the same as assigning the undefined value to the variable. For example
the following lines

    undef A
    A = undef 

have the same effect unless `A` is an array or reference. However when
the variable `A` is an array assigning to it the undefined value will
make the first element of the array undefined and not the whole array.
To explore the effects try to run the following program:

    sub fun(a)
    print a,"\n"
    print lbound(a),"\n"
    print a[1]," ",a[2]," ",a[3]
    print
    print
    end sub
    
    k[1] = 1
    k[3] = 2
    fun k
    k = undef
    fun k
    undef k
    fun k

After running it comment out the line `undef k` and compare the result
running the program again.

-----

[\[\<\<\<\]](ug_9.7.2.md) [\[\>\>\>\]](ug_9.8.md)
