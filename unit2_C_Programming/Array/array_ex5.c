/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Array - Ex5
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
	printf("Enter the element to be sarched:");
	scanf("%d",&target);
	
	int location,flag=0;
	for(i=0 ; i<num ; i++){
		if(arr[i]==target){
			printf("number found at location : %d",i+1);
			flag=1;
			break;
		}
		flag=0;
	}
	if(flag == 0){
		printf("number %d not found ",target);
	}
}