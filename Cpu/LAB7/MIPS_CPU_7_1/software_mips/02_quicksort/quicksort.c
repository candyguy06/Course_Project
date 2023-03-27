#include <stdio.h>

void quicksort(int [], int, int);
void swap(int [], int, int);

int
main ()
{

  	int* a = (int*)0x10000000 ;
  	int n = 100 ;

  	//Quick Sort method.
	quicksort(a, 0, n-1);
  
	//for(x = 0; x < 10; x++)
	//	printf("iarray[%d]=%d \n", x, iarray[x]);

  	return 0;
}



void quicksort(int numbers[], int left, int right)
{
	int pivot, i, j;
  
  	if(left < right)
  	{
  		i = left;
  		j = right+1;
  		pivot = numbers[left];
	  	
  		do{
  			do{
  				i++;
  			}while(numbers[i]<pivot);
  		
  			do{
  				j--;
  			}while(numbers[j]>pivot);

			if(i < j)
				swap(numbers, i, j);
  		
  		}while(i < j);

  		swap(numbers, left, j);
  		quicksort(numbers, left, j-1);
  		quicksort(numbers, j+1, right);
  			
	}  			
}


void swap(int a[], int x, int y)
{
	int temp; 
	temp = a[x] ; 
	a[x] = a[y] ; 
	a[y] = temp ;
} 

 
