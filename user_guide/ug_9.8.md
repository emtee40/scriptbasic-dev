# Associative Arrays

[\[\<\<\<\]](ug_9.7.3.md) [\[\>\>\>\]](ug_9.8.1.md)

Associative arrays were introduced in ScriptBasic v1.0build19. This
section does not apply to any previous version.

Languages, like Perl or AWK have associative arrays and so does
ScriptBasic. Associative arrays differ from arbitrary arrays in two
points:

  - The index is written using curly brackets, like
    
    ``` 
     a{11}
    ```
    
    instead of normal brackets.

  - The value of the index can be anything not only integer numbers.

When you use a variable as associative array you can use strings,
integers, real numbers and even the value `undef` as index value.
Whenever you access certain element of an associative array the
interpreter searches for the index value and uses the value associated
with it. This leads to compact and easy to read programs.

For example:

    const nl="\n"
    a{"foo"} ="foo value"
    a{"bar"} = "bar value"
    a{"dummy"} = "dummy value"
    
    print a{"foo"},nl

will print

    foo value

If you use an index that is not present in the associative array the
result is `undef`.

``` 

const nl="\n"
a{"foo"} ="foo value"
a{"bar"} = "bar value"
a{"dummy"} = "dummy value"


print a{"FOO"},nl
```

will print `undef`.

Note that in this situation a new element with the new key is created
automatically containing the value `undef`.

Index values that are `undef`, integers or real numbers can be
referenced using the exactly same value. When using strings as keys the
matching is performed according to the option \``compare`'. The previous
example altered a bit:

``` 

option compare sbCaseInSensitive
const nl="\n"
a{"foo"} ="foo value"
a{"bar"} = "bar value"
a{"dummy"} = "dummy value"

print a{"FOO"},nl
```

will find the key and print `foo value`, although the key used for
definition and the key used for reference differ is case.

Associative arrays inside ScriptBasic are stored as normal arrays. The
difference between normal array and associative arrays are the way the
programmer handles them. Advanced programmers may and most probably
should use associative arrays as normal arrays as well.

An associative array is nothing else than a normal array storing the
keys on the even indices and the values on the odd indices. When you
reference

    a{"foo"}

the interpreter starts to search the string `"foo"` on the even indices
of the array and when it finds it returns the next element. To explain
it see the following sample:

    const nl="\n"
    a{"foo"} ="foo value"
    a{"bar"} = "bar value"
    a{"dummy"} = "dummy value"
    
    for i=lbound(a) to ubound(a)
    print i," ",a[i],nl
    next i

will print

    0 foo
    1 foo value
    2 bar
    
    3 bar value
    4 dummy
    5 dummy value

You can see that the keys and values are paired up in the array. Knowing
this you can iterate over the keys of an associative array:

    const nl="\n"
    a{"foo"} ="foo value"
    a{"bar"} = "bar value"
    a{"dummy"} = "dummy value"
    
    for i=lbound(a) to ubound(a) step 2
    print "a{",a[i],"}=",a{a[i]},nl
    next i

to get

    a{foo} =foo value
    a{bar} =bar value
    a{dummy} =dummy value

Note, however that in case the same key present many times in the array
using the `a{`} notation finds always the first value. For example:

    const nl="\n"
    a{"foo"} ="foo value"
    a{"bar"} = "bar value"
    a{"dummy"} = "dummy value"
    a[6] = "foo"
    a[7] = "never found"
    
    
    for i=lbound(a) to ubound(a) step 2
    print "a{",a[i],"}=",a{a[i]},nl
    next i

will print

    a{foo}=foo value
    a{bar}=bar value
    a{dummy}=dummy value
    a{foo}=foo value

and it never print `never found`.

Knowing that the associative arrays are just normal arrays inside one
can even make dirty tricks:

    const nl="\n"
    a{"foo"} ="foo value"
    a{"bar"} = "bar value"
    a{"dummy"} = "dummy value"
    a[-1] ="hoho"
    
    for i=lbound(a) to ubound(a)
    print i," ",a[i],nl
    next i
    
    print "--------------------------------\n"
    
    top = ubound(a)
    for i=lbound(a) to top step 2
    print i," a{",a[i],"}=",a{a[i]},nl
    next i

will result

    -1 hoho
    0 foo
    1 foo value
    2 bar
    3 bar value
    4 dummy
    
    5 dummy value
    --------------------------------
    -1 a{hoho}=foo
    
    
    1 a{foo value}=bar
    3 a{bar value}=dummy
    5 a{dummy value}=undef

Adding an extra -1-th element to the array all indices became values and
all values became indices.

Associative arrays can have multiple indices just like normal arrays.
For example:

    sub printit(zz)
      print zz{"foo"},"\n"
    end sub
    a{"dummy","bar"} = 13
    a{"dummy","foo"} = 14
    printit a{"dummy"}
    print a{"dummy","bar"}, _
      " ",a{"dummy","foo"}

will print

    14
    13 14

-----

[\[\<\<\<\]](ug_9.7.3.md) [\[\>\>\>\]](ug_9.8.1.md)
