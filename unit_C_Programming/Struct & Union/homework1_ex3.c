/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Struct - Ex3
14/3/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
struct data{
	float real;
	float imagine;
};

struct data add (struct data number_1 ,struct data number_2){
	struct data temp;
	temp.real = number_1.real+number_2.real;
	temp.imagine = number_1.imagine+number_2.imagine;
	return temp;
}

void main()
{
	struct data temp,number_1, number_2;
	printf("First complex number \n\n");
	printf("Enter real : ");
	scanf("%f",&number_1.real);
	printf("Enter imaginary : ");
	scanf("%f",&number_1.imagine);
	printf("\nEnter information of first distance \n\n");
	printf("Enter real : ");
	scanf("%f",&number_2.real);
	printf("Enter imaginary : ");
	scanf("%f",&number_2.imagine);
	
	temp = add(number_1,number_2);
	
	printf("\nSum = %.2f +%.2f i", temp.real , temp.imagine);
	
}