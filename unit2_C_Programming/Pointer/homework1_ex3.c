/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Pointer - Ex3
30/3/2023

Write a program in C to print a string in reverse using a pointer
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>


void main()
{
	char name[]={"hassan"};
	int x = sizeof(name)/sizeof(name[0]);
	x=x-2;
	char *ptr= &name[x];
	printf("Input a string : %s\n",name);
	printf("Reverse of the string is :");
	int i ;
	for(i=0 ; i <=x ; i++ ){
		printf("%c",*ptr);
		ptr--;
	}
}