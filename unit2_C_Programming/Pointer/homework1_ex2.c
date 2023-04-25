/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Pointer - Ex2
30/3/2023

Write a program in C to print all the alphabets using a pointer. Go
to the editor
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>


void main()
{
	char alpha[25];
	char *x=alpha;
	
	int i;
	for(i = 0 ; i<26 ; i++){
		*x= i +'A';
		x++;
	}
	x=alpha;
	
	for(i = 0 ; i<26 ; i++){
		printf("%c\t",*x);
		x++;
	}
}