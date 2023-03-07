/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Homework2 - Ex2
12/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	char alpha=0;
	printf("Enter an alphbet: "); 	
	scanf("%c",&alpha);
	
	
	switch(alpha){
		case'a':
		case'A':
		case'e':
		case'E':
		case'i':
		case'I':
		case'o':
		case'O':
		case'u':
		case'U':
		{
			printf("%c is a vowel",alpha);
		}
		break;
		default:
		{
			printf("%c is a consonant",alpha);
		}
		break;
		
	}	
	
}