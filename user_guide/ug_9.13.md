# Comments

[\[\<\<\<\]](ug_9.12.md) [\[\>\>\>\]](ug_9.14.md)

You can insert comments into the source file. A line starting with the
keyword `REM` or starting with the character `'` (apostrophe) is treated
as comment
    line.

    REM This is a simple program that prints the words "HELLO" and "WORD"
    REM to the screen
    PRINT "HELLO WORLD"

Or you can write it

    ' This is a simple program that prints the words "HELLO" and "WORLD"
    ' to the screen
    PRINT "HELLO WORLD"

However you can not use comments after commands, and therefore you can
not write:

    PRINT "HELLO WORD" 'This comment is invalid in ScriptBasic

or

    PRINT "HELLO WORD" REM This comment is invalid in ScriptBasic

Note that the comment lines are tokenized and are "removed" from the
source file after the lexical analyzer is done. Why is this important?
Because multi-line strings may span more than one line. In this case the
whole string that starts on a line being part of a comment will become
comment. This way you can easily create multi-line comments that are
quite useful for program documentation. For example:

    ' """
    
    FILE:   test.sb
    AUTHOR: Peter Verhas
    DATE:   August 20, 2002
    
    CONTENTS:
    This is a program that contains nothing else but a multi-line
    Comment.
    
    """

-----

[\[\<\<\<\]](ug_9.12.md) [\[\>\>\>\]](ug_9.14.md)
