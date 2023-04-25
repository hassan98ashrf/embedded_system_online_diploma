/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Homework1 - Ex7
12/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	float num_1=0.0 , num_2=0.0 , temp=0.0;
	printf("Enter value of a: ");
	scanf("%f",&num_1);
	
	printf("Enter value of b: ");
	scanf("%f",&num_2);
	
	num_1 = num_1 + num_2;
	num_2 = num_1 - num_2;
	num_1 = num_1 - num_2;
	
	printf("\nAfter swapping, value of a = %f",num_1);
	printf("\nAfter swapping, value of b = %f\n",num_2);
}