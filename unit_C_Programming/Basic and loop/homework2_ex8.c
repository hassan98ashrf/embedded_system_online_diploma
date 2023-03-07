/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Homework2 - Ex8
12/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	char symb = 0;
	float num_1  = 0 , num_2 = 0 , result = 0;
	
	printf("Enter operator either + or - or * or / : "); 	
	scanf("%c",&symb);
	
	printf("Enter two operands: "); 	
	scanf("%f %f",&num_1,&num_2);
	
	switch(symb){
		case'+':
		{
			result = num_1 + num_2;
			printf("%f %c %f = %f",num_1,symb,num_2,result);
		}
		break;
		
		case'-':
		{
			result = num_1 - num_2;
			printf("%f %c %f = %f",num_1,symb,num_2,result);
		}
		break;
		
		case'*':
		{
			result = num_1 * num_2;
			printf("%f %c %f = %f",num_1,symb,num_2,result);
		}
		break;
		
		case'/':
		{
			result = num_1 / num_2;
			printf("%f %c %f = %f",num_1,symb,num_2,result);
		}
		break;
	}
	
	
}