/*
FILE: prepext.c
HEADER: prepext.h

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

// this is the Internal Preprocessor interface version
#define IP_INTERFACE_VERSION 1

typedef struct _Prepext {
  long lVersion;
  void *pPointer;
  void *pMemorySegment;
  struct _SupportTable *pST;
  } Prepext, *pPrepext;

enum PreprocessorCommands {
// constant values that tell the preprocessor the actual action that the
// preprocessor is called for
  PreprocessorLoad = 0,
  PreprocessorReadStart,
  PreprocessorReadDone0,
  PreprocessorReadDone1,
  PreprocessorReadDone2,
  PreprocessorReadDone3,

  PreprocessorLexInit,
  PreprocessorLexDone,
  PreprocessorLexNASymbol,
  PreprocessorLexASymbol,
  PreprocessorLexSymbol,
  PreprocessorLexString,
  PreprocessorLexMString,
  PreprocessorLexInteger,
  PreprocessorLexReal,
  PreprocessorLexCharacter,

  PreprocessorExStart,
  PreprocessorExStartLine,
  PreprocessorExEnd,
  PreprocessorExFinish,
  PreprocessorExStartLocal,
  PreprocessorExEndLocal,
  PreprocessorExLineNode,

  PreprocessorExeStart,
  PreprocessorExeFinish,
  PreprocessorExeNoRun,

// constant values that the preprocessor can pass back to the calling
// level to tell what to do next
  PreprocessorContinue, // go on call the next available preprocessor
  PreprocessorDone, // this preprocessor has done what had to be done at this level, do not call further preprocessors
  PreprocessorUnload,


  _PreprocesorDummy_
  };

*/
