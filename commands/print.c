/*print.c

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

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../command.h"

/*POD
=H PRINT command

This file implements the two print commands that print to the standard output.
The print commands that print to a file are implemented in T<file.c>

The difference between the standard output printing and file printing commands
are that the file printing commands use th T<#> character to specify the file
number.

CUT*/

/*POD
=section printNL
=H Print a new line character
=verbatim
  print
=noverbatim

This command is a print command without any argument. This command prints a new line
character to the standard output. Note however that the R<print> command that has arguments
does not print new line character aftre the results of the expressions are printed to the standard
output. Therefore the following two statements are identical, altough the second generates somewhat longer code:

=verbatim
print
print "\n"
=noverbatim

CUT*/
COMMAND(PRINTNL)
#if NOTIMP_PRINTNL
NOTIMPLEMENTED;
#else

  void (*fpExtOut)(char, void *);

  fpExtOut = pEo->fpStdouFunction;

  if( fpExtOut )
    fpExtOut('\n',pEo->pEmbedder);
  else
    printf("\n");

#endif
END

/*POD
=section print
=H Print expression values to standard output
=verbatim
print expression_list
=noverbatim

This command prints the values of the expressions to the standard output. The expressions
are evaluated and the value is formmatted according to their actual type.

Long values are printed using the format T<%ld>.

Double values are printed using the format T<%lf>.

String values are printed sending each character to the standard output.

CUT*/
COMMAND(PRINT)
#if NOTIMP_PRINT
NOTIMPLEMENTED;
#else
  NODE nItem;
  VARIABLE ItemResult;
  char *s;
  unsigned long slen;
  void (*fpExtOut)(char, void *);
  char buffer[40];

  fpExtOut = pEo->fpStdouFunction;
  nItem = PARAMETERNODE;
  while( nItem ){
    ItemResult = _EVALUATEEXPRESSION_A(CAR(nItem));
    ASSERTOKE;

    if( memory_IsUndef(ItemResult) )
      strcpy(buffer,"undef");
    else
    switch( TYPE(ItemResult) ){
      case VTYPE_LONG:
        sprintf(buffer,"%ld",LONGVALUE(ItemResult));
        break;
      case VTYPE_DOUBLE:
        sprintf(buffer,"%g",DOUBLEVALUE(ItemResult));
        break;
      case VTYPE_STRING:
        s = STRINGVALUE(ItemResult);
        slen = STRLEN(ItemResult);
        while( slen -- )
          if( fpExtOut )
            fpExtOut(*s++,pEo->pEmbedder);
          else
            putc(((int)*s++),stdout);
          *buffer = (char)0;/* do not print anything afterwards */
        break;
      case VTYPE_ARRAY:
        sprintf(buffer,"ARRAY@#%08X",LONGVALUE(ItemResult));
        break;
      }

    s = buffer;
    while( *s )
      if( fpExtOut )
        fpExtOut(*s++,pEo->pEmbedder);
      else
        putc(((int)*s++),stdout);

    nItem = CDR(nItem);
    }


#endif
END

