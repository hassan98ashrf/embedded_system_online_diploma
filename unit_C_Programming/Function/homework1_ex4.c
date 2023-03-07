/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Functios - Ex4
6/3/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
int power_of(int num,int power);


void main()
{
	int num,power;
	printf("Enter a base number : ");
	scanf("%d",&num);
	printf("Enter a power number : ");
	scanf("%d",&power);
	printf("%d ^ %d = %d",num,power,power_of(num,power));
	
}

int power_of(int num,int power){
	if(power != 0){
		return (num*power_of(num,power-1));
	}
	else{
		return 1;
	}
	
}