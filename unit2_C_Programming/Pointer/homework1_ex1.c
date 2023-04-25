/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Pointer - Ex1
30/3/2023

Write a program in C to demonstrate how to handle the pointers
in the program.
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>


void main()
{
	int m=29 , *ab=&m;
	printf("Address of m : %p \n",&m);
	printf("Value of m : %d \n",m);
	
	printf("\nNow ab is assigned with the address of m. \n");
	printf("Address of pointer ab : %p \n",ab);
	printf("Value of pointer ab : %d \n",*ab);
	
	printf("\nThe value of m assigned to 34 now. \n");
	m=34;
	printf("Address of pointer ab : %p \n",ab);
	printf("Value of pointer ab : %d \n",*ab);
	
	printf("\nThe value of m assigned to 34 now. \n");
	*ab=7;
	printf("Address of m : %p \n",&m);
	printf("Value of m : %d \n",m);
	
	
}