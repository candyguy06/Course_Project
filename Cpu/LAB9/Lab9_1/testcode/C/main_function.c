#include "main_function.h"

void main_function ()
{
 volatile int *tube =  (int*) 0x20000000;
 volatile int *EXmem =  (int*) 0x40000000; 
 
 EXmem[256] = 24976146;
 
  tube[0] = '\n' ;     
  tube[0] = 'H' ;
  tube[0] = 'e' ;
  tube[0] = 'l' ;
  tube[0] = 'l' ;
  tube[0] = 'o' ;
  tube[0] = '\t' ;  
  tube[0] = 'E' ;
  tube[0] = 'A' ;
  tube[0] = 'S' ;
  tube[0] = 'Y' ;
  tube[0] = '!' ;
  tube[0] = '\n' ; 

 
}
