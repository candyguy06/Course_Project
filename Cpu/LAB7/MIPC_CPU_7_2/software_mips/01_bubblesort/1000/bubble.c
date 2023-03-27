#include <stdio.h>

int
main ()
{

  int* a = (int*)0x10000000 ;
  int n = 1000 ;
  int i, j, tmp;

  // Bubble sort method.
  for (i=0; i<n-1; i++){
  	for (j=0; j<n-1-i; j++){
  		if (a[j+1] < a[j]) {  /* compare the two neighbors */
  		   	tmp = a[j];         /* swap a[j] and a[j+1]      */
      			a[j] = a[j+1];
      			a[j+1] = tmp;
   		}
	}
  }
  
//  for(i = 0; i < n; i++)
//  	printf("array[%d]=%d \n", i, array[i]);

  return 0;
}