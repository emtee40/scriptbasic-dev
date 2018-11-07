'	Assume the worst
	ERROR(0)
	ON ERROR GOTO Err_catch

' Bad status to DCL
	ExitStatus = 255

	logfile = FREEFILE()
	OPEN "LOGFILE" FOR APPEND AS logfile

	PRINT #logfile, FORMATDATE("YEAR/0M/0D 0H:0m:0s", NOW())," Before EXECUTE\n"
	ON ERROR GOTO StartLooping
	Result = EXECUTE("T:/MyProjects/ScriptBasic/source/bin/vc7/exe/scriba.exe T:/MyProjects/ScriptBasic/source/examples/testwaitpid_loop.bas", 1, PID)
	PRINT #logfile, FORMATDATE("YEAR/0M/0D 0H:0m:0s", NOW())," Result = ",Result,"\n"

StartLooping:
	IF ERROR() <> 54 THEN
		GOTO Err_catch
	END IF

	ON ERROR GOTO Err_catch

	PRINT #logfile, FORMATDATE("YEAR/0M/0D 0H:0m:0s", NOW())," PID = ",PID,"\n"
	RESUME Looping

Looping:
	WHILE WAITPID(PID,ExitCode) = 0
		SLEEP(5)
	WEND
	print "waiting some extra\n"
        SLEEP(10)
	print WAITPID(PID,ExitCode)
	PRINT #logfile, FORMATDATE("YEAR/0M/0D 0H:0m:0s", NOW())," ExitCode = ",ExitCode,"\n"

Finished:

' We make it OK
	ExitStatus = 0

	GOTO Exit_program

Err_catch:
	err_code=ERROR()
	RESUME Crash

Crash:

	PRINT #logfile, "*\n"
	PRINT #logfile, "* ERROR: TEST has terminated due to an unexpected error.\n"
	PRINT #logfile, "*        Error number ",err_code,",",ERROR$(err_code),"\n"
	ExitStatus = err_code

Exit_program:

	PRINT #logfile, "* Done at ", FORMATDATE("YEAR/0M/0D 0H:0m:0s", NOW()),"\n"
	ON ERROR GOTO NULL
	ERROR(-ExitStatus)
END
