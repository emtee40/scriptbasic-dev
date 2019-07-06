/* 
FILE:   uniqfnam.c
HEADER: uniqfnam.h

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

#define UNIQ_FILE_NAME_LENGTH 32

*/


/*POD
=H Creating unique file name
=abstract
The function in this file is used to create a unique file name for
internal storage. This is used in code cache and preprocessing
operations.

=toc

CUT*/

#include <string.h>

#include "tools/global.h"
#include "tools/md5.h"

/*POD
=section uniqfnam
=H Calculate unique file name

The input file name should be the name of a file including the full path
to the file name. The function calculates the MD5 digest of the file name,
which is a 16-byte number and converts it to ASCII and copies the result to
the output argument T<pszOutputFileName>. The argument T<pszOutputFileName>
should point to a buffer of at least 33 characters (32 characters plus the
ZCHAR).

/*FUNCTION*/
void uniqfnam(char *pszInputFileName,
              char *pszOutputFileName
  ){
/*noverbatim
CUT*/
  MD5_CTX MyContext;
  unsigned char digest[16];
  int i;

  /* calculate the MD5 digest of the file name */
  MD5Init(&MyContext);
  MD5Update(&MyContext, pszInputFileName, strlen(pszInputFileName));
  MD5Final(digest,&MyContext);

  /* convert the digest to ASCII */
  for( i = 0 ; i < 16 ; i++ ){
    pszOutputFileName[2*i] = 'A' + (digest[i]&0x0F);
    digest[i] >>= 4;
    pszOutputFileName[2*i+1] = 'A' + (digest[i]&0x0F);
    }
  pszOutputFileName[32] = (char)0;
  }
