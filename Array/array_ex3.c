/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Array - Ex3
22/2/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>

void main()
{
	int row,colum;
	printf("Enter number of row: ");
	scanf("%d",&row);
	printf("Enter number of colum: ");
	scanf("%d",&colum);
	
	int arr_1[row][colum];
	int arr_2[row][colum];
	printf("Enter element of matrix:\n");
	int  i,j;
	for(i=0 ; i<row ; i++){
		for(j=0 ; j<colum ; j++){
			printf("Enter element a%d%d: ",i+1,j+1);
			scanf("%d",&arr_1[i][j]);
			arr_2[j][i]=arr_1[i][j];
		}
	}
	
	printf("Entered matrix: \n");
	for(i=0 ; i<row ; i++){
		for(j=0 ; j<colum ; j++){
			printf("%d\t",arr_1[i][j]);	
		}
		printf("\n");
	}
	
	printf("Transpose of matrix:\n");
	int temp = row;
	row = colum;
	colum = temp;
	
	for(i=0 ; i<row ; i++){
		for(j=0 ; j<colum ; j++){
			printf("%d\t",arr_2[i][j]);	
		}
		printf("\n");
	}
	
	
}