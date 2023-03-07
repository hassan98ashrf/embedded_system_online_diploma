/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Array - Ex4
22/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	int num;
	printf("Enter number of element:");
	scanf("%d",&num);
	
	int arr[num];
	int  i;
	for(i=0 ; i<num ; i++){
		scanf("%d",&arr[i]);
	}
	
	int target;
	printf("Enter the element to be inserted:");
	scanf("%d",&target);
	
	int location;
	printf("Enter the location:");
	scanf("%d",&location);
	
	for(i=0 ; i<num ; i++){
		if(i==(location-1)){
			arr+1;
			printf("%d\t",target);
		}
		printf("%d\t",arr[i]);	
	}
	
}