/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
String - Ex1
26/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	char arr[100];
	printf("Enter a string : ");
	gets(arr);
	char alpha;
	printf("Enter a character to find frequincey : ");
	scanf(" %c",&alpha);
	
	int count=0,i;
	for(i=0 ; arr[i]!='\0' ; i++){
		if(arr[i] == alpha){
			count++;
		}
	}
	printf("Frequincey of %c = %d" , alpha , count );
	
}