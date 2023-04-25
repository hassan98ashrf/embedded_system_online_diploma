/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Homework2 - Ex6
12/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	short num = 0;
	long sum = 0;
	printf("Enter a number: "); 	
	scanf("%d",&num);
	
	short i = 0;
	for ( i = 0 ; i <= num ; i++){
		sum = sum + i;
	} 
	
	printf("Sum = %d",sum); 
}