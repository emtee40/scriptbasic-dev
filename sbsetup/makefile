all : setup.exe

setup.res : setup.rc
	rc setup.rc

filesys.obj : ..\filesys.c
	cl /DWIN32 /ML /c ..\filesys.c

setup.obj : setup.c
	cl /DWIN32 /ML /c setup.c

setup.exe : setup.obj filesys.obj setup.res
	link /OUT:setup.exe /NODEFAULTLIB:LIBC setup.obj filesys.obj setup.res comctl32.lib ws2_32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib zlib.lib 
