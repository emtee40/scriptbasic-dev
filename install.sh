#! /bin/sh
#
# This script is 'install.sh' will install ScriptBasic from the
# compiled binary to the final destination.
#
# This script was gerenared by the program setup.pl started with
# the option --install
#
# This is not a source file, do not edit!
#

ERRCOUNT=0
#
# creating the directory ${HOME}/.scriba
#
if [ -e ${HOME}/.scriba ] ; then
  echo "${HOME}/.scriba already exists"
else
  mkdir -p ${HOME}/.scriba 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR creating directory ${HOME}/.scriba"
    let ERRCOUNT= $ERRCOUNT+1
  fi
  chmod 666 ${HOME}/.scriba 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR setting the permission of ${HOME}/.scriba to 666"
    let ERRCOUNT= $ERRCOUNT+1
  fi
fi
#--------------------------------------------------------------

#
# creating the directory /etc/scriba
#
if [ -e /etc/scriba ] ; then
  echo "/etc/scriba already exists"
else
  mkdir -p /etc/scriba 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR creating directory /etc/scriba"
    let ERRCOUNT= $ERRCOUNT+1
  fi
  chmod 555 /etc/scriba 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR setting the permission of /etc/scriba to 555"
    let ERRCOUNT= $ERRCOUNT+1
  fi
fi
#--------------------------------------------------------------

#
# creating the directory /usr/share/scriba/include
#
if [ -e /usr/share/scriba/include ] ; then
  echo "/usr/share/scriba/include already exists"
else
  mkdir -p /usr/share/scriba/include 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR creating directory /usr/share/scriba/include"
    let ERRCOUNT= $ERRCOUNT+1
  fi
  chmod 555 /usr/share/scriba/include 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR setting the permission of /usr/share/scriba/include to 555"
    let ERRCOUNT= $ERRCOUNT+1
  fi
fi
#--------------------------------------------------------------

#
# creating the directory /usr/share/scriba/source
#
if [ -e /usr/share/scriba/source ] ; then
  echo "/usr/share/scriba/source already exists"
else
  mkdir -p /usr/share/scriba/source 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR creating directory /usr/share/scriba/source"
    let ERRCOUNT= $ERRCOUNT+1
  fi
  chmod 555 /usr/share/scriba/source 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR setting the permission of /usr/share/scriba/source to 555"
    let ERRCOUNT= $ERRCOUNT+1
  fi
fi
#--------------------------------------------------------------

#
# creating the directory /usr/local/lib/scriba
#
if [ -e /usr/local/lib/scriba ] ; then
  echo "/usr/local/lib/scriba already exists"
else
  mkdir -p /usr/local/lib/scriba 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR creating directory /usr/local/lib/scriba"
    let ERRCOUNT= $ERRCOUNT+1
  fi
  chmod 555 /usr/local/lib/scriba 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR setting the permission of /usr/local/lib/scriba to 555"
    let ERRCOUNT= $ERRCOUNT+1
  fi
fi
#--------------------------------------------------------------

#
# creating the directory /usr/local/lib
#
if [ -e /usr/local/lib ] ; then
  echo "/usr/local/lib already exists"
else
  mkdir -p /usr/local/lib 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR creating directory /usr/local/lib"
    let ERRCOUNT= $ERRCOUNT+1
  fi
  chmod 655 /usr/local/lib 2> /dev/null
  if [ $? -ne 0 ] ; then
    echo "###ERROR setting the permission of /usr/local/lib to 655"
    let ERRCOUNT= $ERRCOUNT+1
  fi
fi
#--------------------------------------------------------------

#
# clean old cache files that may
# have been created by previous version
#
if [ -e ${HOME}/.scriba/cache ] ; then
 echo "purging old cache files from ${HOME}/.scriba/cache"
 rm -rf ${HOME}/.scriba/cache/*
else
 echo "creating cache directory ${HOME}/.scriba/cache"
 mkdir -p ${HOME}/.scriba/cache
fi
echo "setting permission 777 to ${HOME}/.scriba/cache"
chmod 777 ${HOME}/.scriba/cache 2>/dev/null
if [ $? -ne 0 ] ; then
 echo "###ERROR setting the permission of the directory ${HOME}/.scriba/cache to 777"
 let ERRCOUNT = $ERRCOUNT+1
fi

if [ -e ${HOME}/.scriba/hebtemp ] ; then
 rm -rf ${HOME}/.scriba/hebtemp/*
fi
mkdir -p ${HOME}/.scriba/hebtemp
chmod a+rw ${HOME}/.scriba/hebtemp

cp ./bin/exe/scriba /usr/bin/scriba
chown root:root /usr/bin/scriba
chmod 555 /usr/bin/scriba


echo "Now I stop the Eszter SB Engine."
if [ -e /etc/init.d/sbhttpd ] ; then
  /etc/init.d/sbhttpd stop >/dev/null 2>/dev/null
fi
killall sbhttpd 2> /dev/null

echo "copying the file sbhttpd binary executable to /usr/bin"
# 
# Copy the file ./bin/exe/sbhttpd to /usr/bin/sbhttpd
# 
chmod 777 /usr/bin/sbhttpd 2>/dev/null                  
cp ./bin/exe/sbhttpd /usr/bin/sbhttpd 2>/dev/null
if [ $? -ne 0 ] ;then
  echo "###ERROR copying the file ./bin/exe/sbhttpd to /usr/bin/sbhttpd"
  let ERRCOUNT = $ERRCOUNT+1
fi         

chown root:root /usr/bin/sbhttpd 2>/dev/null
if [ $? -ne 0 ] ; then
  echo "###ERROR setting the owner of the file /usr/bin/sbhttpd to root"
  let ERRCOUNT = $ERRCOUNT+1
fi

chmod 555 /usr/bin/sbhttpd 2>/dev/null
if [ $? -ne 0 ] ; then
  echo "###ERROR changing the permission of /usr/bin/sbhttpd to 555"
  let ERRCOUNT = $ERRCOUNT+1
fi
#--------------------------------------------------------------

echo "copying the file sbhttpd shell script to /etc/init.d"
# 
# Copy the file ./etc-init.d-sbhttpd to /etc/init.d/sbhttpd
# 
chmod 777 /etc/init.d/sbhttpd 2>/dev/null                  
cp ./etc-init.d-sbhttpd /etc/init.d/sbhttpd 2>/dev/null
if [ $? -ne 0 ] ;then
  echo "###ERROR copying the file ./etc-init.d-sbhttpd to /etc/init.d/sbhttpd"
  let ERRCOUNT = $ERRCOUNT+1
fi         

chown root:root /etc/init.d/sbhttpd 2>/dev/null
if [ $? -ne 0 ] ; then
  echo "###ERROR setting the owner of the file /etc/init.d/sbhttpd to root"
  let ERRCOUNT = $ERRCOUNT+1
fi

chmod 555 /etc/init.d/sbhttpd 2>/dev/null
if [ $? -ne 0 ] ; then
  echo "###ERROR changing the permission of /etc/init.d/sbhttpd to 555"
  let ERRCOUNT = $ERRCOUNT+1
fi
#--------------------------------------------------------------

cat <<'END'
************************************************************
The Eszter SB Application Engine (if it was running) was
stopped to allow upgrade. It may happen that it was not
running at all though. No problem.

Due to security reasons the installation process does not
start or in case it was already running restart the server.

If you need Eszter SB Application Engine running then please
start it saying:

/etc/init.d/sbhttpd start
************************************************************"
END
# this is commented out because we do not want to install
# and start a http daemon on any system so that the system
# manager may not be aware of it
# /etc/init.d/sbhttpd start
# get the file if it is not belonging to root
chown root:root /etc/scriba/basic.conf
# make it so that we can write it
chmod u+rw /etc/scriba/basic.conf
# recompile the file 
/usr/bin/scriba -k -f /etc/scriba/basic.conf scriba.conf.unix.lsp
if [ $? -ne 0 ] ; then
  echo "###ERROR creating the default configuration file"
  let ERRCOUNT = $ERRCOUNT+1
fi
# make it readable for all, but no writes it
chmod 444 /etc/scriba/basic.conf
cat <<END
************************************************************
The ScriptBasic configuration file was updated using the
default sample configuration file. In case you have already
a configuration file that you have used reinstall it
using the configuration compiler program saying:

/usr/bin/scriba -f /etc/scriba/basic.conf -k your_old_config_file

If you did not have a configuration from an older installation
then start using the default configuration and save the text
version of the default config file at a location you wish.
The text version of the default configuration is stored in
the file scriba.conf.unix.lsp
************************************************************
END
echo "copying the standard header files"
#
# Copy files include/*.bas to /usr/share/scriba/include
#
chmod 777 /usr/share/scriba/include/*.bas 2>/dev/null
cp include/*.bas /usr/share/scriba/include 2>/dev/null
if [ $? -ne 0 ] ;then
  echo "###ERROR copying the file include/*.bas to /usr/share/scriba/include"
  let ERRCOUNT = $ERRCOUNT+1
fi  

chown root:root /usr/share/scriba/include/*.bas 2>/dev/null
if [ $? -ne 0 ] ; then
  echo "###ERROR setting the owner of the file /usr/share/scriba/include/*.bas to root"
  let ERRCOUNT = $ERRCOUNT+1
fi

chmod 444 /usr/share/scriba/include/*.bas 2>/dev/null
if [ $? -ne 0 ] ; then
  echo "###ERROR changing the permission of /usr/share/scriba/include/*.bas to 444"
  let ERRCOUNT = $ERRCOUNT+1
fi
#--------------------------------------------------------------

echo "installing all modules that were successfully compiled"
echo "copy the scriba library file"
# 
# Copy the file ./bin/lib/libscriba.a to /usr/local/lib/libscriba.a
# 
chmod 777 /usr/local/lib/libscriba.a 2>/dev/null                  
cp ./bin/lib/libscriba.a /usr/local/lib/libscriba.a 2>/dev/null
if [ $? -ne 0 ] ;then
  echo "###ERROR copying the file ./bin/lib/libscriba.a to /usr/local/lib/libscriba.a"
  let ERRCOUNT = $ERRCOUNT+1
fi         

chown root:root /usr/local/lib/libscriba.a 2>/dev/null
if [ $? -ne 0 ] ; then
  echo "###ERROR setting the owner of the file /usr/local/lib/libscriba.a to root"
  let ERRCOUNT = $ERRCOUNT+1
fi

chmod 444 /usr/local/lib/libscriba.a 2>/dev/null
if [ $? -ne 0 ] ; then
  echo "###ERROR changing the permission of /usr/local/lib/libscriba.a to 444"
  let ERRCOUNT = $ERRCOUNT+1
fi
#--------------------------------------------------------------

echo "copy the example preprocessor to the source directory"
# 
# Copy the file ./heber.bas to /usr/share/scriba/source/heber.bas
# 
chmod 777 /usr/share/scriba/source/heber.bas 2>/dev/null                  
cp ./heber.bas /usr/share/scriba/source/heber.bas 2>/dev/null
if [ $? -ne 0 ] ;then
  echo "###ERROR copying the file ./heber.bas to /usr/share/scriba/source/heber.bas"
  let ERRCOUNT = $ERRCOUNT+1
fi         

chown root:root /usr/share/scriba/source/heber.bas 2>/dev/null
if [ $? -ne 0 ] ; then
  echo "###ERROR setting the owner of the file /usr/share/scriba/source/heber.bas to root"
  let ERRCOUNT = $ERRCOUNT+1
fi

chmod 444 /usr/share/scriba/source/heber.bas 2>/dev/null
if [ $? -ne 0 ] ; then
  echo "###ERROR changing the permission of /usr/share/scriba/source/heber.bas to 444"
  let ERRCOUNT = $ERRCOUNT+1
fi
#--------------------------------------------------------------

if [ $ERRCOUNT -eq 0 ] ; then
 echo "It seems that the installation was sucessful"
else
 if [ $ERRCOUNT -eq 1 ] ; then
  echo "There was one error during installation."
 else
  echo "There were $ERRCOUNT errors during installation."
 fi
fi
echo
echo "DID YOU READ ALL THE MESSAGES ABOVE? THEY ARE IMPORTANT!"

