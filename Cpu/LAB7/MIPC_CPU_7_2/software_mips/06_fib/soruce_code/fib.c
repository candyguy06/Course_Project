#include <stdio.h>

int fib(int);

int
main ()
{

  	volatile int* a = 0x80000000 ;
  	int length = 47 ;
	
	int i;

	for(i=0; i<length; i++)
		a[i]=fib(i);	

  	return 0;
}


int fib(int n)
{
	if(n<=1) 
		return n;	//F(0)=0, F(1)=1
	else {
		int fn;
		int fnm2=0;
		int fnm1=1;
		int i;
		
		for(i=2;i<=n;i++)
		{
			fn=fnm1+fnm2;
			fnm2=fnm1;
			fnm1=fn;
		}
		
		return fn;
	}
}
		
	


	






