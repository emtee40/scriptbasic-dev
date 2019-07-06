/*
FILE:   report.c
HEADER: report.h

Common MIT License - Jan 31, 2018

ScriptBasic Copyright (c) 2018 Peter Verhas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

TO_HEADER:

typedef char *ReportMessage(char *Language, int ErrorCode);

typedef void ReportFunction(void *, // a pointer that the system passes to the report function
                            char *, // the file name, where the error has happened
                            long,   // line number where the error has happened
                            unsigned int,    // the code of the error
                            int,    // severity of the error
                            int *,  // error counter
                            char *,  // a single, language independant string parameter for the message
                            unsigned long * // a pointer to flag bits
                            );

typedef ReportFunction *pReportFunction;

// the different error severities

enum {
  REPORT_INFO = 0,
  REPORT_WARNING,
  REPORT_ERROR,
  REPORT_FATAL,
  REPORT_INTERNAL
  };

#define REPORT_F_CGI  0x00000001
#define REPORT_F_FRST 0x00000002 // zero on the first call and it is set to 1 later

*/

#include <stdio.h>
#include <string.h>

#include "report.h"
#include "errcodes.h"

/*POD

This file contains a simple error report handling function that prints the error to the standard error.

This is a default reporting function used by most variations of ScriptBasic. However some variations
like the ISAPI one needs to implements a function having the same interface.

CUT*/

/*POD
=H report_report()

This function implements the default error reporting function for both run-time and parse time errors and
warnings.

/*FUNCTION*/
void report_report(void *filepointer,
                   char *FileName,
                   long LineNumber,
                   unsigned int iErrorCode,
                   int iErrorSeverity,
                   int *piErrorCounter,
                   char *szErrorString,
                   unsigned long *fFlags
  ){
/*noverbatim
Aguments:
=itemize

=item T<filepointer> is a T<void *> pointer. The default value of this pointer is T<stderr> unless the
variation sets it different. This implementation uses this pointer as a T<FILE *> pointer. Other implementations
of this function may use it for any other purpose so long as long the usage of this pointer fits the variation.

=item T<FileName> is the name of the source file where the error was detected. This parameter is T<NULL> in case of
a run-time error. The reporting function is encouraged to display this information for the user.

=item T<LineNumber> is the line number within the source file where the error has happened. This parameter is valid
only in case the parameter T<FileName> is not T<NULL>

=item T<iErrorCode> is the error code.

=item T<iErrorSeverity> should define the severity of the error. It can be
T<REPORT_INFO>,
T<REPORT_WARNING>,
T<REPORT_ERROR>,
T<REPORT_FATAL>,
T<REPORT_INTERNAL>.
Whenever the error severity is above the warning level the T<*piErrorCounter> has to be incremented.

=item T<piErrorCounter> points to an T<int> counter that counts the number of errors. If there are errors
during syntax analysis the ScriptBasic interpreter stops its execution before starting execution.

=item T<szErrorString> is an optional error parameter string and not the displayable error message.
The error message is stored in the global constant array T<en_error_messages>. This string may
contain a T<%s> control referring to the error parameter string.

=item T<fFlags> is an T<unsigned long> bit field. The bits currently used are:
T<REPORT_F_CGI> is set if the error is to be reported as a CGI script. See the code for more details.
T<REPORT_F_FRST> is reset when the report function is called first time and is set by the report function. 
This allows the report function to report a header in case it needs.
Other bits are reserved for later use.

=noitemize
CUT*/

  if( ((*fFlags) & REPORT_F_CGI) && !((*fFlags) & REPORT_F_FRST) ){
    fprintf((FILE *)filepointer,"Status: 200 OK\nContent-Type: text/html\n\n"
                                "<HTML><HEAD>\n"
                                "<title>Error page, syntax error</title>\n"
                                "</HEAD><BODY>\n"
                                "<H1>Error has happened in the code</H1>"
                                "<pre>\n");
    }

  if( szErrorString && strlen(szErrorString) > 80 )szErrorString[79] = (char)0;

  if( iErrorSeverity >= REPORT_ERROR && piErrorCounter )(*piErrorCounter)++;

  if( FileName )fprintf((FILE*)filepointer,"%s(%ld):",FileName,LineNumber);
  fprintf((FILE *)filepointer,(iErrorCode < MAX_ERROR_CODE ? " error &H%x:" : " error 0x%08x:"),iErrorCode);
  if( iErrorCode >= MAX_ERROR_CODE )iErrorCode = COMMAND_ERROR_EXTENSION_SPECIFIC;
  if( szErrorString ){
    fprintf((FILE*)filepointer,en_error_messages[iErrorCode],szErrorString);
    fprintf((FILE*)filepointer,"\n");
    }else
    fprintf((FILE *)filepointer,"%s\n",en_error_messages[iErrorCode]);
  *fFlags |= REPORT_F_FRST;
  }
