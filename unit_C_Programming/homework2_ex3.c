/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Homework2 - Ex3
12/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	float num_1=0 , num_2=0 , num_3=0;
	printf("Enter three numbers: "); 	
	scanf("%f %f %f",&num_1 ,&num_2 ,&num_3);
	
	if(num_1 >= num_2 && num_1 >= num_3){
		printf("Largest number = %f ", num_1);
	}
	else if(num_2 >= num_1 && num_2 >= num_3){
		printf("Largest number = %f ", num_2);
	}
	else{
		printf("Largest number = %f ", num_3);
	}
	
}