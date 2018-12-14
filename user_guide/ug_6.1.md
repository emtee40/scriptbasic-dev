# BASIC to EXE compilation technical details

[\[\<\<\<\]](ug_6.md) [\[\>\>\>\]](ug_7.md)

Under Windows and Linux an executable file is loaded into the system
without caring too much the length of the file. This is the feature that
let viruses attach themselves to executable file under Windows. When
ScriptBasic is started with the option \``-E`' the interpreter makes a
copy of the executable of itself and appends the compiled intermediate
code after the executable code. Finally it prints the eleven characters
string `SCRIPTBASIC` and a four byte file byte offset pointing after the
end of the executable part of the file.

When the interpreter starts first it check if the last 15 bytes start
with the string `SCRIPTBASIC`. If it does not then the interpreter
continues in normal operation processing the command line parameters.
However if the last 15 bytes start with the string `SCRIPTBASIC` then
the executable is a ScriptBasic generated executable and it loads the
code from the executable starting at the byte offset specified by the
last four bytes of the file.

-----

[\[\<\<\<\]](ug_6.md) [\[\>\>\>\]](ug_7.md)
