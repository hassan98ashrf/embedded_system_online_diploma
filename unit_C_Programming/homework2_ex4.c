/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Homework2 - Ex4
12/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	float num=0;
	printf("Enter a number: "); 	
	scanf("%f",&num);
	
	if(num>0){
		printf("%f is positive ", num);
	}
	else if(num<0){
		printf("%f is nigative ", num);
	}
	else{
		printf("you entired zero ");
	}
	
}