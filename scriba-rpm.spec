#
# ScriptBasic RPM spec file
#
# Use this file to build the RPM package of the actual ScriptBasic build
# The command to build the RPM file is: make rpm
#
# Do not forget to edit the Version in the preamble as well as in the
# Source field in the file name
#
Summary: ScriptBasic interpreter
Name: scriba
Version: 2.1
Release: 2
Copyright: Common MIT
Group: Applications/Interpreter
Source: https://sandbox.allbasic.info:8181/scriptbasic/sb-dev
URL: http://scripbasic.org
Packager: ScriptBasic Developer Team

%description
ScriptBasic is a BASIC interpreter implementing a scripting
version of the language BASIC. It comes with a command line
version of the interpreter as well as a standalone http daemon
with ScriptBasic built in. ScriptBasic can handle external
modules written in C and can easily embedded delivering
a well defined and featureful API for C and C++ programmers.

%prep

%setup

%build
make all

%install
make install

%files
