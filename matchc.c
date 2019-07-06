/*
FILE: matchc.c
HEADER: matchc.h

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

This file contains declarations that are used by more than one command file in the
directory commands.

The pattern matching operator "LIKE" implemented in string.c uses an own data structure
and the directory listing "OPENDIR" implemented in file.c also need access to the same
data structure.

TO_HEADER:
typedef struct _PatternParam {
  unsigned long cArraySize;// allocated array size
  unsigned long cAArraySize;//actual array size (that is used actuall, should not be greater than cArraySize)
  unsigned long *pcbParameterArray;
  char **ParameterArray;
  unsigned long cbBufferSize;
  char *pszBuffer;
  int iMatches;
  pMatchSets pThisMatchSets;
  } PatternParam, *pPatternParam;
int initialize_like(pExecuteObject pEo);
*/
