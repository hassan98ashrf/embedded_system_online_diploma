/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Struct - Ex4
14/3/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
struct data{
	int roll;
	char name[50];
	float marks;
}s[20];


void main()
{
	printf("Enter information of student \n\n");
	int i;
	for(i=0 ; i<5 ; i++){
		s[i].roll = i+1;
		printf("for roll : %d \n", s[i].roll  );
		printf("Enter name : ");
		scanf("%s",s[i].name);
		printf("Enter your mark : ");
		scanf("%f",&s[i].marks);
		printf("\n");
	}
	printf("\nDisplaaaying information of student \n");
	for(i=0 ; i<5 ; i++){
		s[i].roll = i+1;
		printf("Information of roll : %d \n", s[i].roll  );
		printf("Your name is : %s\n",s[i].name);
		printf("Your mark : %.2f\n",s[i].marks);
		printf("\n");
	}
}