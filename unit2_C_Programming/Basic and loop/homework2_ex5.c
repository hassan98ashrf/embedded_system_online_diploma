/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Homework2 - Ex5
12/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	char alpha=0;
	printf("Enter a character: "); 	
	scanf("%C",&alpha);
	
	if( (alpha >= 'a' && alpha <='z') || (alpha >= 'A' && alpha <='Z')){
		printf("%c is an alphabet ", alpha);
	}
	else{
		printf("%c is not an alphabet ", alpha);
	}
	
}