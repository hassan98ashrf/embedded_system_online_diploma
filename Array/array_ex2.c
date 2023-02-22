/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Array - Ex2
22/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	short num;
	printf("Enter number of data:");
	scanf("%d",&num);
	float arr[num];
	
	long i;
	float avg=0.0,sum=0.0;
	
	for(i=0 ; i<num ; i++){
		printf("%d. Enter number: ",i+1);
		scanf("%f",&arr[i]);
		sum += arr[i];
	}
	avg=sum/num;
	printf("The avarge = %f",avg);
	
}