/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Homework2 - Ex7
12/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	short num = 0;
	long facto = 1;
	
	printf("Enter an integer: "); 	
	scanf("%d",&num);
	
	// expect state n=0 & n<0
	if( num == 0 ){
		printf("Factorial = 1");
	}
	
	else if ( num < 0 ){
		printf("ERROR!!!! factorial of negative number doesnot exist");
	}
	
	else{
		short i = 1;
		while(i<=num){
			facto = facto * i;
			i++;
		}
		
		printf("Factorial = %d",facto); 
	}
}