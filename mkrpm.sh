#! /bin/sh

echo "Deleting all intermediate files."

rm -f *.h syntax.c errcodes.c
rm -rf deb/scriba/*
rm -f deb/*.deb
rm -rf bin/*
rm -f `find . -name *.lib -print`
rm -f `find . -name *.dll -print`
rm -f `find . -name *.exe -print`
rm -f `find . -name *.zip -print`
rm -f `find . -name *.gz  -print`
rm -f `find . -name *.tar -print`
rm -f `find . -name *.aux -print`
rm -f `find . -name *.dvi -print`
rm -f `find . -name *.ps  -print`
rm -f `find . -name *.tex -print`
rm -f `find . -name *.toc -print`
rm -f `find . -name *.exp -print`
rm -f `find . -name *.bbf -print`
rm -f `find . -name *.bkg -print`
rm -f `find . -name *.obj -print`
rm -f `find . -name *.ps -print`
rm -f `find . -name *.jar -print`
rm -f `find . -name *.tex -print`
rm -f `find . -name *.h_bas -print`
rm -f `find . -name *.pbt -print`
rm -f `find . -name *.log -print`
rm -f `find . -name *.c_ -print`
rm -f `find . -name *~ -print`
rm -f `find . -name *.thtml -print`
rm -rf `find . -name *Debug* -print`
rm -rf `find . -name *imDebug* -print`
rm -rf `find . -name *Release* -print`
rm -rf `find . -name *imRelease* -print`
rm -f *.conf
rm -rf gif
rm -rf html
rm -rf filesdoc
rm -rf extensions/japi/reference
rm -rf extensions/japi/c-examples

echo "copiing source files into RPM temporary directory"

# delete the old directory if it existed
rm -rf scriba-`cat version.txt`b`cat build.txt` | grep -v CVS 2> /dev/null

# create the directory
mkdir scriba-`cat version.txt`b`cat build.txt`

# get all the files in the current directory except the one that we just have created
ls -1|grep -v scriba-`cat version.txt`b`cat build.txt` >tmp

# copy all the files into the temporary directory
cp -R `cat tmp` scriba-`cat version.txt`b`cat build.txt`

# remove the file list
rm tmp

# pack the source files into tar.gz file
tar czf scriba-v`cat version.txt`b`cat build.txt`-source.tar.gz scriba-`cat version.txt`b`cat build.txt`

# remove the temporary directory
rm -rf scriba-`cat version.txt`b`cat build.txt`

# copy the tar.gz file into the dir where RPM expects it
cp scriba-v`cat version.txt`b`cat build.txt`-source.tar.gz /usr/src/redhat/SOURCES

# this script creates the RPM descriptor file
perl scriba-rpm.pl

# build the RPM packages
rpm -ba /usr/src/redhat/SPECS/scriba-rpm.spec
