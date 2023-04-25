/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Pointer - Ex4
30/3/2023

Write a program in C to print the elements 
of an array in reverse order.
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>


void main()
{
	int num[5];
	int *ptr=num;
	int i ;
	printf("Input element \n");
	for(i= 0 ; i<5 ; i++){
		printf("Elemnt %d : ",i+1);
		scanf("%d",ptr+i);
	}
	
	printf("\nReverse element \n");
	ptr=&num[4];
	for(i= 5 ; i>0 ; i--){
		printf("Elemnt %d : ",i);
		printf("%d\n",*ptr);
		ptr--;
	}

}