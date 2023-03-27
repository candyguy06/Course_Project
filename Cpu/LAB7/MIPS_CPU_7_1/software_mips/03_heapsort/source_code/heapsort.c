#include <stdio.h>

void heapsort(int [], int);
void adjust(int [], int, int);
void swap(int [], int, int);

int
main ()
{

  	volatile int* iarray = 0x7FFFFFFC ;
  	int length = 100 ;

  	//Quick Sort method.
	heapsort(iarray, length);
  
	//for(x = 0; x < 10; x++)
	//	printf("iarray[%d]=%d \n", x, iarray[x]);

  	return 0;
}



void heapsort(int numbers[], int n)
{
	int i, j;
  
  	for (i=n/2; i>0; i--)
  		adjust(numbers, i, n);	
  		
  	for (i=n-1; i>0; i--){
  		swap(numbers, 1, i+1);
  		adjust(numbers, 1, i);
  	}			
}



//adjust the binary tree to establish the heap
void adjust(int numbers[], int root, int n)
{
	int child;
	int temp;
	
	temp = numbers[root];
	child = 2*root;		//left child
	
	while(child <= n){
		if( (child < n) &&
		    (numbers[child] < numbers[child+1]) )
			child++;
		
		if(temp > numbers[child])	//compare root and max. child
			break;
		else {
			numbers[child/2]=numbers[child];
			child*=2;
		}
	}
	numbers[child/2]=temp;
}
	
	


void swap(int a[], int x, int y)
{
	int temp; 
	temp = a[x] ; 
	a[x] = a[y] ; 
	a[y] = temp ;
} 

 
