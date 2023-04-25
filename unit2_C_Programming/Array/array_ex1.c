/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Array - Ex1
22/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	int arr_1[2][2],arr_2[2][2];
	printf("Enter element of 1st matrix :\n");
	short i,j=0;
	
	for(i=0 ; i<2 ; i++){
		printf("Enter a%d%d:",j+1,i+1);
		scanf("%d",&arr_1[j][i]);
		if(i==1&&j==0){
			j=1;
			i=-1;
		}
	}
	printf("Enter element of 2nd matrix :\n");
	j=0;
	for(i=0 ; i<2 ; i++){
		printf("Enter b%d%d:",j+1,i+1);
		scanf("%d",&arr_2[j][i]);
		if(i==1&&j==0){
			j=1;
			i=-1;
		}
	}
	printf("Sum of matrix :\n");
	printf("%d\t%d\n",arr_1[0][0]+arr_2[0][0],arr_1[0][1]+arr_2[0][1]);
	printf("%d\t%d",arr_1[1][0]+arr_2[1][0],arr_1[1][1]+arr_2[1][1]);
}