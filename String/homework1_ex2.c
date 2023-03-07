/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
String - Ex2
26/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	char arr[100];
	printf("Enter a string : ");
	scanf(" %s",arr);
	
	int count=0,i;
	for(i=0 ; arr[i]!='\0' ; i++){
		count++;
	}
	
	
	
	
	
	printf("The length of %s = %d" , arr , count );
	
}