#include "main_function.h"

void main_function ()
{
 volatile int *tube =  (int*) 0x20000000;

 
 
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
   
  tube[0] = 'T' ;
  tube[0] = 'i' ;
  tube[0] = 'm' ;
  tube[0] = 'e' ;
  tube[0] = 'r' ;
  tube[0] = '\t' ; 
  tube[0] = 'W' ;
  tube[0] = 'a' ;
  tube[0] = 'k' ;
  tube[0] = 'e' ;
  tube[0] = 'U' ;      
  tube[0] = 'p' ; 
  tube[0] = '!' ;
  tube[0] = '\n' ;  
  
  while(1){}
 // if(interrupt)  break;
 
}
