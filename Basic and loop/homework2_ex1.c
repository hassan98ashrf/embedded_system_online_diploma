/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Homework2 - Ex1
12/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	short num=0;
	printf("Enter an integer you want to check: "); 	
	scanf("%d",&num);
	
	if(num % 2 ==0){
		printf("%d is even",num);
	}
	else{
		printf("%d is odd",num);
	}
	
}