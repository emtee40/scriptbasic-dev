REM
REM this bacth file compiles a TEXI documenation of modules
REM the argument has to be the file to be compiled
REM w/o the texi.jam extension
REM
cd bin\texi
mkdir tmp
cd tmp

copy ..\%1.texi %1.texi
perl ..\..\..\t2h.pl %1.texi %1
mkdir ..\..\..\..\html\texi\

copy %1.texi ..\..\..\..\html\texi\
copy %1.rtf ..\..\..\..\html\texi\

gzip %1.rtf
copy %1.rtf.gz ..\..\..\..\html\texi\

copy %1.html ..\..\..\..\html\texi\
gzip %1.html
copy %1.html.gz ..\..\..\..\html\texi\

hhc %1.hhp
copy %1.chm ..\..\..\..\html\texi\

tar cfz %1.html.tgz *.html
copy %1.html.tgz ..\..\..\..\html\texi\

rm -rf ..\..\..\..\html\texi\%1
mkdir ..\..\..\..\html\texi\%1
copy *.html ..\..\..\..\html\texi\%1\

tex -silent %1.texi
tex -silent %1.texi
dvips %1.dvi
gzip %1.ps
dvipdfm %1.dvi
copy %1.ps.gz ..\..\..\..\html\texi\
copy %1.pdf ..\..\..\..\html\texi\
gzip %1.pdf
copy %1.pdf.gz ..\..\..\..\html\texi\
gzip %1.texi
copy %1.texi.gz ..\..\..\..\html\texi\

cd ..
rm -rf tmp
cd ..\..
