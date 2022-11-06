# SB-DEV

Development version of Script BASIC

Execute the following Perl command to install a Perl extension Setup needs.

sudo perl jamal.pl -i

./setup   (this builds the ScriptBasic runtime executables and include files created in the bin directory.

If all goes well, create a local install using mkdist.sh <dest dir>.



## Required Development Libraries
In order to build the external modules, you will need the following dev libraries:

### Linux
---
* libcurl4-gnutls-dev
* libiodbc2-dev
* libmysqlclient-dev
* libncurses5-dev
* libsqlite3-dev
* libssl-dev
* zlib1g-dev

### Raspbery Pi
---
* libcurl4-gnutls-dev
* libiodbc2-dev
* libmariadbclient-dev-compat *(provides mysqlclient)*
* libncurses5-dev
* libsqlite3-dev
* libssl-dev
* zlib1g-dev

### macOS
---
TBD

