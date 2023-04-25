/*
------------------------------------
Eng: Hassan Ashraf Hassan Elsalakawy
Functios - Ex1
6/3/2023
------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
void check_prime(int i);



void main()
{
	int num_1,num_2;
	printf("Enter two number : ");
	scanf("%d",&num_1);
	scanf("%d",&num_2);
	
	printf("Prime number betweeen %d and %d are : \n",num_1 ,num_2);
	int i;
	for(i=num_1 ; i<num_2 ; i++){
		check_prime(i);
	}
}

void check_prime(int i){
	
	
	int x= i-1 ,flag=0;
	if(i==0||i==1){
		flag=1;
	}
			
	while(x>1){
			
		if(i%x != 0){
			x--;
			flag=0;
		}
		else{
			flag=1;
			break;
		}
	}
	if(flag==0){
			printf("%d \n",i);
	}	
}