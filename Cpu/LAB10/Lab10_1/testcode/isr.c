#include "isr.h"

void __irq irq_isr(void)
{
  volatile int *tube =  (int*) 0x20000000;    
  volatile int *IRCntl =  (int*) 0x57000000;
  
  tube[0] = 'I' ;     
  tube[0] = 'R' ;
  tube[0] = 'Q' ;
  tube[0] = '\n' ;

	while(1);
}
