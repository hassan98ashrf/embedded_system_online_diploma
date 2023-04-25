/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Homework1 - Ex3
12/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	long num_1=0 , num_2=0;
	printf("Enter two integers: ");
	scanf("%d",&num_1);
	scanf("%d",&num_2);
	
	num_1 = num_1 + num_2;

	printf("Sum: %d",num_1);
}