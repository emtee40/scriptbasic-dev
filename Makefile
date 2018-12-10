.PHONY: all

LD_FLAGS = -fPIC -shared


ifeq ($(shell uname),Darwin)
	EXTRA_CFLAGS := -D__DARWIN__
	LD_FLAGS := -dylib
endif

# all: bin/exe/scriba bin/exe/sbhttpd bin/lib/libscriba.a bin/lib/libscriba.so
all: bin/exe/scriba 

bin/lib/libscriba.a :  bin/obj/basext.o bin/obj/builder.o bin/obj/buildnum.o bin/obj/confpile.o bin/obj/conftree.o bin/obj/dynlolib.o bin/obj/epreproc.o bin/obj/errcodes.o bin/obj/execute.o bin/obj/expression.o bin/obj/filesys.o bin/obj/getopt.o bin/obj/hndlptr.o bin/obj/hookers.o bin/obj/httpd.o bin/obj/ipreproc.o bin/obj/lexer.o bin/obj/logger.o bin/obj/lsp.o bin/obj/match.o bin/obj/memory.o bin/obj/modumana.o bin/obj/myalloc.o bin/obj/mygmtime.o bin/obj/options.o  bin/obj/reader.o bin/obj/report.o bin/obj/scriba.o bin/obj/sym.o bin/obj/syntax.o bin/obj/thread.o bin/obj/uniqfnam.o bin/obj/md5.o bin/obj/environ.o bin/obj/external.o bin/obj/extops.o bin/obj/file.o bin/obj/function.o bin/obj/goto.o bin/obj/if.o bin/obj/let.o bin/obj/mathfunc.o bin/obj/mathops.o bin/obj/print.o bin/obj/string.o bin/obj/time.o bin/obj/while.o bin/obj/stndlone.o
	ar -r bin/lib/libscriba.a  bin/obj/basext.o bin/obj/builder.o bin/obj/buildnum.o bin/obj/confpile.o bin/obj/conftree.o bin/obj/dynlolib.o bin/obj/epreproc.o bin/obj/errcodes.o bin/obj/execute.o bin/obj/expression.o bin/obj/filesys.o bin/obj/getopt.o bin/obj/hndlptr.o bin/obj/hookers.o bin/obj/httpd.o bin/obj/ipreproc.o bin/obj/lexer.o bin/obj/logger.o bin/obj/lsp.o bin/obj/match.o bin/obj/memory.o bin/obj/modumana.o bin/obj/myalloc.o bin/obj/mygmtime.o bin/obj/options.o  bin/obj/reader.o bin/obj/report.o bin/obj/scriba.o bin/obj/sym.o bin/obj/syntax.o bin/obj/thread.o bin/obj/uniqfnam.o bin/obj/md5.o bin/obj/environ.o bin/obj/external.o bin/obj/extops.o bin/obj/file.o bin/obj/function.o bin/obj/goto.o bin/obj/if.o bin/obj/let.o bin/obj/mathfunc.o bin/obj/mathops.o bin/obj/print.o bin/obj/string.o bin/obj/time.o bin/obj/while.o bin/obj/stndlone.o


bin/lib/libscriba.so :  bin/obj/basext.o bin/obj/builder.o bin/obj/buildnum.o bin/obj/confpile.o bin/obj/conftree.o bin/obj/dynlolib.o bin/obj/epreproc.o bin/obj/errcodes.o bin/obj/execute.o bin/obj/expression.o bin/obj/filesys.o bin/obj/getopt.o bin/obj/hndlptr.o bin/obj/hookers.o bin/obj/httpd.o bin/obj/ipreproc.o bin/obj/lexer.o bin/obj/logger.o bin/obj/lsp.o bin/obj/match.o bin/obj/memory.o bin/obj/modumana.o bin/obj/myalloc.o bin/obj/mygmtime.o bin/obj/options.o  bin/obj/reader.o bin/obj/report.o bin/obj/scriba.o bin/obj/sym.o bin/obj/syntax.o bin/obj/thread.o bin/obj/uniqfnam.o bin/obj/md5.o bin/obj/environ.o bin/obj/external.o bin/obj/extops.o bin/obj/file.o bin/obj/function.o bin/obj/goto.o bin/obj/if.o bin/obj/let.o bin/obj/mathfunc.o bin/obj/mathops.o bin/obj/print.o bin/obj/string.o bin/obj/time.o bin/obj/while.o bin/obj/stndlone.o bin/obj/lmt_none.o
	ld $(LD_FLAGS) -o bin/lib/libscriba.so  bin/obj/basext.o bin/obj/builder.o bin/obj/buildnum.o bin/obj/confpile.o bin/obj/conftree.o bin/obj/dynlolib.o bin/obj/epreproc.o bin/obj/errcodes.o bin/obj/execute.o bin/obj/expression.o bin/obj/filesys.o bin/obj/getopt.o bin/obj/hndlptr.o bin/obj/hookers.o bin/obj/httpd.o bin/obj/ipreproc.o bin/obj/lexer.o bin/obj/logger.o bin/obj/lsp.o bin/obj/match.o bin/obj/memory.o bin/obj/modumana.o bin/obj/myalloc.o bin/obj/mygmtime.o bin/obj/options.o  bin/obj/reader.o bin/obj/report.o bin/obj/scriba.o bin/obj/sym.o bin/obj/syntax.o bin/obj/thread.o bin/obj/uniqfnam.o bin/obj/md5.o bin/obj/environ.o bin/obj/external.o bin/obj/extops.o bin/obj/file.o bin/obj/function.o bin/obj/goto.o bin/obj/if.o bin/obj/let.o bin/obj/mathfunc.o bin/obj/mathops.o bin/obj/print.o bin/obj/string.o bin/obj/time.o bin/obj/while.o bin/obj/lmt_none.o -lc -lm -ldl -lpthread


bin/lib/lscriba.a :  bin/obj/basext.o bin/obj/builder.o bin/obj/buildnum.o bin/obj/confpile.o bin/obj/conftree.o bin/obj/dynlolib.o bin/obj/epreproc.o bin/obj/errcodes.o bin/obj/execute.o bin/obj/expression.o bin/obj/filesys.o bin/obj/getopt.o bin/obj/hndlptr.o bin/obj/hookers.o bin/obj/httpd.o bin/obj/ipreproc.o bin/obj/lexer.o bin/obj/logger.o bin/obj/lsp.o bin/obj/match.o bin/obj/memory.o bin/obj/modumana.o bin/obj/myalloc.o bin/obj/mygmtime.o bin/obj/options.o  bin/obj/reader.o bin/obj/report.o bin/obj/scriba.o bin/obj/sym.o bin/obj/syntax.o bin/obj/thread.o bin/obj/uniqfnam.o bin/obj/md5.o bin/obj/environ.o bin/obj/external.o bin/obj/extops.o bin/obj/file.o bin/obj/function.o bin/obj/goto.o bin/obj/if.o bin/obj/let.o bin/obj/mathfunc.o bin/obj/mathops.o bin/obj/print.o bin/obj/string.o bin/obj/time.o bin/obj/while.o
	ar -r bin/lib/lscriba.a  bin/obj/basext.o bin/obj/builder.o bin/obj/buildnum.o bin/obj/confpile.o bin/obj/conftree.o bin/obj/dynlolib.o bin/obj/epreproc.o bin/obj/errcodes.o bin/obj/execute.o bin/obj/expression.o bin/obj/filesys.o bin/obj/getopt.o bin/obj/hndlptr.o bin/obj/hookers.o bin/obj/httpd.o bin/obj/ipreproc.o bin/obj/lexer.o bin/obj/logger.o bin/obj/lsp.o bin/obj/match.o bin/obj/memory.o bin/obj/modumana.o bin/obj/myalloc.o bin/obj/mygmtime.o bin/obj/options.o  bin/obj/reader.o bin/obj/report.o bin/obj/scriba.o bin/obj/sym.o bin/obj/syntax.o bin/obj/thread.o bin/obj/uniqfnam.o bin/obj/md5.o bin/obj/environ.o bin/obj/external.o bin/obj/extops.o bin/obj/file.o bin/obj/function.o bin/obj/goto.o bin/obj/if.o bin/obj/let.o bin/obj/mathfunc.o bin/obj/mathops.o bin/obj/print.o bin/obj/string.o bin/obj/time.o bin/obj/while.o



bin/obj/confpile.o : confpile.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/confpile.o confpile.c

bin/obj/ipreproc.o : ipreproc.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/ipreproc.o ipreproc.c

bin/obj/lsp.o : lsp.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/lsp.o lsp.c

bin/obj/scriba.o : scriba.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/scriba.o scriba.c

bin/obj/buildnum.o : buildnum.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/buildnum.o buildnum.c

bin/obj/builder.o : builder.c filesys.h report.h lexer.h sym.h expression.h myalloc.h builder.h errcodes.h buildnum.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/builder.o builder.c

bin/obj/conftree.o : conftree.c conftree.h errcodes.h filesys.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/conftree.o conftree.c

bin/obj/dynlolib.o : dynlolib.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/dynlolib.o dynlolib.c

bin/obj/execute.o : execute.c sym.h errcodes.h report.h lexer.h expression.h builder.h memory.h syntax.h execute.h myalloc.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/execute.o execute.c

bin/obj/expression.o : expression.c errcodes.h report.h lexer.h sym.h expression.h myalloc.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/expression.o expression.c

bin/obj/filesys.o : filesys.c errcodes.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/filesys.o filesys.c

bin/obj/httpd.o : httpd.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/httpd.o httpd.c

bin/obj/getopt.o : getopt.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/getopt.o getopt.c

bin/obj/lexer.o : lexer.c errcodes.h report.h lexer.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/lexer.o lexer.c

bin/obj/match.o : match.c errcodes.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/match.o match.c

bin/obj/logger.o : logger.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/logger.o logger.c

bin/obj/mygmtime.o : mygmtime.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/mygmtime.o mygmtime.c

bin/obj/thread.o : thread.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/thread.o thread.c

bin/obj/hndlptr.o : hndlptr.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/hndlptr.o hndlptr.c

bin/obj/memory.o : memory.c errcodes.h myalloc.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/memory.o memory.c

bin/obj/modumana.o : modumana.c basext.h sym.h errcodes.h report.h lexer.h expression.h builder.h memory.h syntax.h execute.h myalloc.h dynlolib.h modumana.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/modumana.o modumana.c

bin/obj/hookers.o : hookers.c basext.h sym.h errcodes.h report.h lexer.h expression.h builder.h memory.h syntax.h execute.h myalloc.h dynlolib.h hookers.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/hookers.o hookers.c

bin/obj/myalloc.o : myalloc.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/myalloc.o myalloc.c

bin/obj/epreproc.o : epreproc.c myalloc.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/epreproc.o epreproc.c

bin/obj/options.o : options.c sym.h errcodes.h report.h lexer.h expression.h builder.h memory.h syntax.h execute.h myalloc.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/options.o options.c

bin/obj/stndlone.o : stndlone.c getopt.h scriba.h basext.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/stndlone.o stndlone.c

bin/obj/reader.o : reader.c filesys.h report.h errcodes.h conftree.h reader.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/reader.o reader.c

bin/obj/report.o : report.c errcodes.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/report.o report.c

bin/obj/sym.o : sym.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/sym.o sym.c

bin/obj/basext.o : basext.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/basext.o basext.c

bin/obj/uniqfnam.o : uniqfnam.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/uniqfnam.o uniqfnam.c

bin/obj/errcodes.o : errcodes.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/errcodes.o errcodes.c

bin/obj/syntax.o : syntax.c report.h lexer.h sym.h expression.h syntax.h
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/syntax.o syntax.c

bin/obj/md5.o : md5.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/md5.o md5.c




bin/obj/extops.o : commands/extops.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/extops.o commands/extops.c

bin/obj/environ.o : commands/environ.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/environ.o commands/environ.c

bin/obj/external.o : commands/external.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/external.o commands/external.c

bin/obj/file.o : commands/file.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/file.o commands/file.c

bin/obj/function.o : commands/function.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/function.o commands/function.c

bin/obj/goto.o : commands/goto.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/goto.o commands/goto.c

bin/obj/if.o : commands/if.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/if.o commands/if.c

bin/obj/let.o : commands/let.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/let.o commands/let.c

bin/obj/mathfunc.o : commands/mathfunc.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/mathfunc.o commands/mathfunc.c

bin/obj/mathops.o : commands/mathops.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/mathops.o commands/mathops.c

bin/obj/print.o : commands/print.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/print.o commands/print.c

bin/obj/string.o : commands/string.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/string.o commands/string.c

bin/obj/time.o : commands/time.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/time.o commands/time.c

bin/obj/while.o : commands/while.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/while.o commands/while.c








bin/exe/scriba : bin/lib/lscriba.a bin/var/standard/scribacmd.o bin/obj/lmt_none.o
	gcc $(EXTRA_CFLAGS) -w -o bin/exe/sb bin/var/standard/scribacmd.o bin/obj/lmt_none.o bin/lib/lscriba.a -lc -lm -ldl -lpthread
	@echo
	bin/exe/sb -v

bin/var/standard/scribacmd.o : variations/standard/scribacmd.c
	mkdir -p bin/var/standard || echo
	gcc $(EXTRA_CFLAGS) -w -c -o bin/var/standard/scribacmd.o variations/standard/scribacmd.c

bin/obj/lmt_none.o : lmt_none.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/lmt_none.o lmt_none.c




bin/exe/sbhttpd : bin/lib/lscriba.a bin/var/httpd/websrv.o bin/var/httpd/service.o bin/obj/lmt_none.o
	gcc $(EXTRA_CFLAGS) -w -o bin/exe/sbhttpd bin/var/httpd/websrv.o bin/var/httpd/service.o bin/obj/lmt_none.o bin/lib/lscriba.a -lc -lm -ldl -lpthread


bin/var/httpd/websrv.o : variations/httpd/websrv.c
	mkdir -p bin/var/httpd || echo
	gcc $(EXTRA_CFLAGS) -w -c -o bin/var/httpd/websrv.o variations/httpd/websrv.c



bin/var/httpd/service.o : variations/httpd/service.c
	mkdir -p bin/var/httpd || echo
	gcc $(EXTRA_CFLAGS) -w -c -o bin/var/httpd/service.o variations/httpd/service.c


bin/obj/lmt_httpd.o : lmt_httpd.c
	gcc $(EXTRA_CFLAGS) -w -c -o bin/obj/lmt_httpd.o lmt_httpd.c

clean :
	rm -rf bin/exe/*
	rm -rf bin/include/*
	rm -rf bin/lib/*
	rm -rf bin/make/*
	rm -rf bin/obj/*
	rm -rf bin/var/*
	rm -rf bin/mod/*

