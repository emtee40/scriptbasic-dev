# Strings

[\[\<\<\<\]](ug_9.1.md) [\[\>\>\>\]](ug_9.3.md)

Strings are most frequently used entities in a BASIC program. As you
could already see in the very first example strings are quoted with
double quote. But they can be more than just characters between double
quotes. String as a type is a basic data type of ScriptBasic. A variable
having string value contains several bytes. There is no length limit for
a string other than the virtual memory of the machine. A string may
contain character of any code even characters that have the ASCII code
zero. In other words a string is a collection of bytes of certain
length. You can treat strings as arbitrary length of binary data if you
need.

Strings can be concatenated, you can cut off a part of a string and
several other functions and operators can handle strings. ScriptBasic
automatically allocates the space required to store the string and
releases the unused space when the string is not needed anymore. For
more information on string handling operators and functions see the
chapter [Command reference](ug_25.md).

The simplest form of a string is a strings constant appearing in the
source file. This is the form like in the example

    print "Hello Word\n"

Here you can note that there is a special character at the end of the
string denoted by two characters. This may be familiar from other
languages. The characters `\n` mean a new line character in a readable
form. The \\ (backslash) character is the escape character in a string
altering the meaning of the character that follows it. The special
characters that ScriptBasic handles are:

  - `\t` is converted to a tabulator character.
  - `\n` is converted to a new line character.
  - `\r` is converted to a carriage return character.
  - `\"` is converted to a double quote character. This is the way to
    include a double quote character into the string.
  - `\0-9` is converted to ASCII code, see details later.

All other characters remain the same after a backslash. This means that
you can write `\\` to have a string containing a backslash character, or
`\"` to have a string containing a double quote character, but `\a`
means nothing else than the letter `a`.

There is another way to include special characters into string
constants. The usual way in BASIC is to split the string into sub
strings and concatenate the parts during run time, like in the code
fragment:

    St = "This is a special string, containing a bell character at the end" & chr(7)

You can do this in ScriptBasic, but you can do it easier and more
effective:

    St = "This is a special string, containing a bell character at the end\7" 

The last character is a number preceded by a backslash. Whenever numbers
follow a backslash character in a string ScriptBasic calculates the
value of the numbers and uses the character of the code. If the first
character after the backslash is zero then the number is treated as
octal number, otherwise it is treated as a decimal number.

Strings should not contain the new line character. In other words

    St = "this is
    a multi line
    string of three lines."

is not legal in ScriptBasic. It was legal in former versions before
v1.0build15 to write multi-line strings, but it caused problem to
programmers forgetting the closing double quote character on a line.
Instead a new string constant format was introduced that starts and ends
with three double quote characters. For example:

    St = """this is
    a multi line
    string of three lines."""

is perfectly correct. Strings starting and ending with three `"`
characters can, but need not span multiple lines. There is another
difference between single-line and multi-line strings. A multi-line
string may contain a double quote character without escaping with
backslash. You can write:

``` 

St = """this is " a double quote character """
```

or you can write

    St = """this is \" a double quote character """

which is also correct. The only situation where you should escape a
double quote character in a multi-line string is when you want to have
three or more " characters following each other in a string. For example

``` 

St = """this is """ three double quote characters """ THIS IS WRONG
```

is wrong. You have to type instead:

    St = """this is \""" three double quote characters """

or

    St = """this is "\"" three double quote characters """

or

    St = """this is ""\" three double quote characters """

or

    St = """this is \""\" three double quote characters """

or some other variation of escaping one or more of the consecutive `"`
characters. The rule is that there can not be three consecutive
un-escaped `"` characters inside a multi-line string.

There is another constrain regarding multi-line strings. The very first
character of a multi-line string should not be the character `&` or it
has to be escaped with the backslash character. Thus:

    St = """\& is a 
    multi-line string starting with an & character """

is the correct format. If you use the `&` character without escaping it
as the very first character of a multi-line string it will be treated as
a binary multi-line string.

A binary multi-line string is a very special beast that only hard code
users need to specify binary data inside a BASIC program. In such
strings all new-line characters are ignored unless escaped with the
back-slash character. Thus the following two strings

    """&is a 
    binary multi-line\n string starting with an & character """
    
    "is a binary multi-line\n string starting with an & character "

are equivalent with the exception that the second string is a liar,
because that is not a binary multi-line string. Single-line strings can
not be binary, and in case the first character of a single-line string
is the `&` character that is just treated as a normal character.

-----

[\[\<\<\<\]](ug_9.1.md) [\[\>\>\>\]](ug_9.3.md)
