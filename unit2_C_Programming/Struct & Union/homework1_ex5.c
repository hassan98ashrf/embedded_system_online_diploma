/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Struct - Ex5
14/3/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#define PI 3.14
#define AREA(r) (PI*r*r)


void main()
{
	printf("Enter the Redious : ");
	float i,res;
	scanf("%f",&i);
	res = AREA(i);
	printf("Area is %.2f",res);
}