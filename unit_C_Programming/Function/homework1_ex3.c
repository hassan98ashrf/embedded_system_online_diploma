/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Functios - Ex3
6/3/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
void revers();



void main()
{
	printf("Enter a sentence : ");
	revers();
}

void revers(){
	char c;
	scanf("%c",&c);
	if(c !='\n'){
		revers();
		printf("%c",c);
	}
	
}