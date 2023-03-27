#include <stdio.h>

int
main ()
{

  int* a = (int*)0x10000000 ;
  int* b = (int*)0x15000000 ;
  int n = 1200 ;
  int i, j, tmp;

  
  for (int i=0; i<n;i++){
      b[i] = a[i] + 1;
  }
  
//  for(i = 0; i < n; i++)
//  	printf("array[%d]=%d \n", i, array[i]);

  return 0;
}