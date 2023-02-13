/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Homework1 - Ex4
12/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	float num_1=0.0 , num_2=0.0;
	printf("Enter two numbers : ");
	scanf("%f",&num_1);
	scanf("%f",&num_2);
	
	num_1 = num_1 * num_2;

	printf("Product: %f",num_1);
}