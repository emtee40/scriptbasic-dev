	When = NOW() + 3
REM ADDMINUTE(NOW(),1)
A:	SLEEP(5)
	IF When > NOW() THEN GOTO A
	ERROR -3
	END
