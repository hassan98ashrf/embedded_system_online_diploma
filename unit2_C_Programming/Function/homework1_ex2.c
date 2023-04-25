/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Functios - Ex2
6/3/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
void factorial(int num,int x,int y);



void main()
{
	int num;
	printf("Enter a positive integr : ");
	scanf("%d",&num);
	int x=1 , y=num;
	factorial(num,x,y);
}

void factorial(int num,int x,int y){
	x=x*num;
	num--;
	if(num>0){
		factorial(num,x,y);
	}
	else{
		printf("Factorial of %d = %d",y,x);
	}
	
}