/* FILE: lmt_ftpd.def

This file was automatically created by the program lmt_make.pl

DO NOT EDIT THIS FILE!!!

Rather edit the file lmt_ftpd.def that is the source 

*/
#include <stdio.h>
#include "basext.h"

extern SLFST MT_SLFST[];
MODLIST StaticallyLinkedModules[] ={
  {"mt" , (void *)MT_SLFST },
  { NULL, NULL },
  };
