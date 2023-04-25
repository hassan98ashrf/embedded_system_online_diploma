/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Struct - Ex1
14/3/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
struct data{
	char name[50];
	int roll;
	float mark;
}x;
void main()
{
	printf("Enter information of student \n\nEnter name : ");
	printf("Enter name : ");
	scanf("%s",x.name);
	printf("Enter your roll : ");
	scanf("%d",&x.roll);
	printf("Enter your mark : ");
	scanf("%f",&x.mark);
	printf("\nDisplaying information of student \n");
	printf("Name : ");
	printf("%s",x.name);
	printf("\nRoll : ");
	printf("%d",x.roll);
	printf("\nMark : ");
	printf("%.2f",x.mark);
}