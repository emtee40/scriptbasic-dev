call setup.cmd
call install.cmd t:\ScriptBasic
cd sbsetup
call pack.cmd
nmake
setup
cd ..
perl mkcdoc.pl
call mkath.cmd
perl scriba-zip.pl
call mkzip.cmd
call mkweb.cmd
