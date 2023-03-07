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
	char arr_1[100],arr_2[100];
	printf("Enter a string : ");
	scanf(" %s",arr_1);
	
	int count=0,i;
	for(i=0 ; arr_1[i]!='\0' ; i++){
		count++;
	}
	
	
	for(i=0 ; i<count ; i++){
		arr_2[i] =arr_1[(count-1)-i];
	}
	
	printf("Reverse %s is = %s"  , arr_1,arr_2 );
}