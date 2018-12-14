# Writing CGI programs

[\[\<\<\<\]](ug_2.2.md) [\[\>\>\>\]](ug_3.md)

There are two ways to write CGI programs in ScriptBasic. The old way is
just like in any other language: the basic program can access the
environment, the standard input and standard output. This is all needed
to write a CGI program, decode the CGI parameters and create the http
response.

The better way is to use the CGI module delivered with ScriptBasic that
automatically handles CGI input, CGI environment variables, creates the
uploaded files and even supports some security settings. For more
details on the CGI module read the separate documentation of the module
named CGI.

-----

[\[\<\<\<\]](ug_2.2.md) [\[\>\>\>\]](ug_3.md)
