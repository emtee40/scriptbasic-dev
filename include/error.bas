' This file was automatically generated by the program generrh.pl
' using the error code definition file errors.def from the
' ScriptBasic distribution
'
' This file is part of the ScriptBasic distribution and is
' specific to the actual build it was shipped. Do not use
' this file for any version or build of the ScriptBasic
' interpreter other than the one this file was shipped.
'
' THIS FILE IS FOR V1.0 BUILD 1
'
Global Const sbErrorOK = 0
Global Const sbErrorMemory = 1

Global Const sbErrorNoarray = 2
' Function can not return a whole array
' -------------------------------------

Global Const sbErrorDiv = 3
' Division by zero or other calculation error
' -------------------------------------------

Global Const sbErrorUndefop = 4
' Argument to operator is undefined
' ---------------------------------

Global Const sbErrorBadCall = 5
' The command or sub was called the wrong way
' -------------------------------------------

Global Const sbErrorFewArgs = 6
' There are not enough arguments of the module function.
' ------------------------------------------------------

Global Const sbErrorArgumentType = 7
' The argument passed to a module function is not the needed type.
' ----------------------------------------------------------------

Global Const sbErrorArgumentRange = 8
' The argument passed to a module function is out of the accepted range.
' ----------------------------------------------------------------------

Global Const sbErrorFileRead = 9
' The module experiences difficulties reading the file
' ----------------------------------------------------

Global Const sbErrorFileWrite = 10
' The module experiences difficulties writing the file.
' -----------------------------------------------------

Global Const sbErrorFile = 11
' The module experiences handling the file.
' -----------------------------------------

Global Const sbErrorCircular = 12
' There is a circular reference in memory.
' ----------------------------------------

Global Const sbErrorModuleNotLoaded = 13
' The module can not be unloaded, because it was not loaded.
' ----------------------------------------------------------

Global Const sbErrorPartialUnload = 14
' Some modules were active and could not be unloaded.
' ---------------------------------------------------

Global Const sbErrorModuleActive = 15
' The module can not be unloaded, because it is currently active.
' ---------------------------------------------------------------

Global Const sbErrorModuleLoad = 16
' The requested module can not be loaded.
' ---------------------------------------

Global Const sbErrorModuleFunction = 17
' The requested function does not exist in the module.
' ----------------------------------------------------

Global Const sbErrorModuleInitialize = 18
' The module did not initialize correctly
' ---------------------------------------

Global Const sbErrorModuleVersion = 19
' The module was developed for a different version of ScriptBasic.
' ----------------------------------------------------------------

Global Const sbErrorBadFileNumber = 20
' File number is out of range, it should be between 1 and 512
' -----------------------------------------------------------

Global Const sbErrorFileNumberIsUsed = 21
' The file number is already used.
' --------------------------------

Global Const sbErrorFileCannotBeOpened = 22
' The file can not be opened.
' ---------------------------

Global Const sbErrorFileIsNotOpened = 23
' The file is not opened.
' -----------------------

Global Const sbErrorInvalidLock = 24
' The lock type is invalid.
' -------------------------

Global Const sbErrorPrintFail = 25
' The print command failed. The file may be locked by another process.
' --------------------------------------------------------------------

Global Const sbErrorMkdirFail = 26
' Directory can not be created.
' -----------------------------

Global Const sbErrorDeleteFail = 27
' The directory or file could not be deleted.
' -------------------------------------------

Global Const sbErrorNotimp = 28
' Command is not implemented and no currently loaded extension module defined behaviour for it
' --------------------------------------------------------------------------------------------

Global Const sbErrorInvalidJoker = 29
' The character can not be a joker or wild card character.
' --------------------------------------------------------

Global Const sbErrorNoResume = 30
' The code tried to execute a resume while not being in error correction code.
' ----------------------------------------------------------------------------

Global Const sbErrorInvalidDirectoryName = 31
' The directory name in open directory is invalid.
' ------------------------------------------------

Global Const sbErrorInvalidOptionDirOpen = 32
' Invalid option for directory open.
' ----------------------------------

Global Const sbErrorDirectoryNoOpen = 33
' The directory can not be opened.
' --------------------------------

Global Const sbErrorBadRecordLength = 34
' The record length is invalid in the open statements (undefined, zero or negative)
' ---------------------------------------------------------------------------------

Global Const sbErrorNoCurrentDirectory = 35
' The current directory can not be retrieved for some reason.
' -----------------------------------------------------------

Global Const sbErrorChDirUndef = 36
' The directory name in chdir can not be undef.
' ---------------------------------------------

Global Const sbErrorChDir = 37
' Cannot change the current working directory to the desired directory.
' ---------------------------------------------------------------------

Global Const sbErrorReturnWithoutGosub = 38
' The command RETURN can not be executed, because there is no where to return.
' ----------------------------------------------------------------------------

Global Const sbErrorInvalidArgumentForFunctionAddress = 39
' The argument for the function address is invalid.
' -------------------------------------------------

Global Const sbErrorSetfileInvalidAttribute = 40
' The attribute value or symbol is invalid in the set file command.
' -----------------------------------------------------------------

Global Const sbErrorChownInvalidUser = 41
' The user does not exist.
' ------------------------

Global Const sbErrorChownNotSupported = 42
' The chown command is not supported on Win95 and Win98
' -----------------------------------------------------

Global Const sbErrorChownSetOwner = 43
' Can not change owner.
' ---------------------

Global Const sbErrorInvalidFileName = 44
' The file name is invalid.
' -------------------------

Global Const sbErrorSetCreateTime = 45
' Setting the create time of the file has failed.
' -----------------------------------------------

Global Const sbErrorSetModifyTime = 46
' Setting the modify time of the file has failed.
' -----------------------------------------------

Global Const sbErrorSetAccessTime = 47
' Setting the access time of the file has failed
' ----------------------------------------------

Global Const sbErrorInvalidTimeFormat = 48
' The specified time format is invalid
' ------------------------------------

Global Const sbErrorInvalidTime = 49
' The time is not valid, cannot be earlier than January 1, 1970. 00:00
' --------------------------------------------------------------------

Global Const sbErrorExtensionSpecific = 50
' Extension specific error: %s
' ----------------------------

Global Const sbErrorSocketFile = 51
' The operation can be done on files only and not on sockets.
' -----------------------------------------------------------

Global Const sbErrorInvalidCode = 52
' The embedding application tried to start the code at an invalid location
' ------------------------------------------------------------------------

Global Const sbErrorMandarg = 53
' Mandatory argument is missing
' -----------------------------

Global Const sbErrorTimeout = 54
' Subprocess did not finish within time limits
' --------------------------------------------

Global Const sbErrorStaysInMemory = 55
' The module can not be unloaded
' ------------------------------

Global Const sbErrorPreprocessorAbort = 56
' The preprocessor said to abort program compilation or execution.
' ----------------------------------------------------------------

