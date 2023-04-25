/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Struct - Ex2
14/3/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
struct data{
	int feet;
	float inch;
}x1,x2,sum;
void main()
{
	printf("Enter information of first distance \n\n");
	printf("Enter feet : ");
	scanf("%d",&x1.feet);
	printf("Enter inch : ");
	scanf("%f",&x1.inch);
	printf("\nEnter information of first distance \n\n");
	printf("Enter feet : ");
	scanf("%d",&x2.feet);
	printf("Enter inch : ");
	scanf("%f",&x2.inch);
	
	sum.feet = x1.feet+x2.feet;
	sum.inch = x1.inch+x2.inch;
	
	while(sum.inch >=12){
		sum.inch = sum.inch-12;
		sum.feet++;
	}
	
	printf("\nSum of distance = %d'  %.2f\"", sum.feet , sum.inch);
	
}