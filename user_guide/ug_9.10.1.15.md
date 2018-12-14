# Extension operators

[\[\<\<\<\]](ug_9.10.1.14.md) [\[\>\>\>\]](ug_9.10.1.16.md)

Extension operators are defined and recognized by the ScriptBasic syntax
analyzer but no execution is implemented behind. Thus using any of the
extension operators will result an error "command is planned, but not
implemented". Why to have these operators?

These operators can be implemented by external modules. An external
module developer may decide to define the behavior of any of the
operators. For example an extension may decide to implement a hashing
algorithm and decide that `a->b` should result the actual hash value
from hash `a` having the key `b`. Any program wanting to use this
functionality can load the module using the statement `declare sub` and
use the operator.

Operators that are undefined by default but can be used by external
modules are:

``` 

?     !     #     `     @
+^    +<    +>    +?    +=    +*    +/    +%    +!    +#    +&    +\    +`    +'    
+@    -^    -<    ->    -?    -=    -*    -/    -%    -!    -#    -&    -\    -`    
-'    -@    ^^    ^<    ^>    ^?    ^=    ^*    ^/    ^%    ^!    ^#    ^&    ^\    

^`    ^'    ^@    <^    <<    <?    <*    </    <%    <!    <#    <&    <\    <`    
<'    <@    >^    ><    >>    >?    >*    >/    >%    >!    >#    >&    >\    >`    
>'    >@    ?^    ?<    ?>    ??    ?=    ?*    ?/    ?%    ?!    ?#    ?&    ?\    
?`    ?'    ?@    =^    =<    =>    =?    ==    =*    =/    =%    =!    =#    =&    
=\    =`    ='    =@    *^    *<    *>    *?    *=    **    */    *%    *!    *#    
*&    *\    *`    *'    *@    /^    /<    />    /?    /=    /*    //    /%    /!    
/#    /&    /\    /`    /'    /@    %^    %<    %>    %?    %=    %*    %/    %%    
%!    %#    %&    %\    %`    %'    %@    !^    !<    !>    !?    !=    !*    !/    
!%    !!    !#    !&    !\    !`    !'    !@    #^    #<    #>    #?    #=    #*    
#/    #%    #!    ##    #&    #\    #`    #'    #@    &^    &<    &>    &?    &=    
&*    &/    &%    &!    &#    &&    &\    &`    &'    &@    \^    \<    \>    \?    

\=    \*    \/    \%    \!    \#    \&    \\    \`    \'    \@    `^    `<    `>    
`?    `=    `*    `/    `%    `!    `#    `&    `\    ``    `'    `@    '^    '<    
'>    '?    '=    '*    '/    '%    '!    '#    '&    '\    '`    ''    '@    @^    
@<    @>    @?    @=    @*    @/    @%    @!    @#    @&    @\    @`    @'    @@
```

The analyzer recognizes these operators as valid. They can be used as
unary operator as well as binary operator. Used as binary operator they
have the highest precedence, one level above the power operator and they
are all evaluated from left to right.

Since build25 the unary operator `#` is implemented as identical
operator resulting the argument of it unchanged. This is to aid the old
BASIC programmers, who got used to write

    open "file" for input as #1

-----

[\[\<\<\<\]](ug_9.10.1.14.md) [\[\>\>\>\]](ug_9.10.1.16.md)
