
/*
Author : Hassan  Ashraf Elsalakawy
main.c
*/

#include "lifo.h"


element_type  buffer_1[width];

void main(){
	int i, temp=0;
	lifo_buff_t uart_lifo , I2C_lifo;
	lifo_init_item(&uart_lifo,buffer_1,5);//static allocation
	
	element_type *  buffer_2 = (element_type *)malloc(5*sizeof(element_type));
	lifo_init_item(&I2C_lifo,buffer_2,5);
	
	
	for(i=0 ; i<5  ; i++){
		if (lifo_add_item(&uart_lifo,i) == lifo_no_error )
			printf("UART add item : %d\n",i);
	}
	i=0;
	for(i=0 ; i<5  ; i++){
		if (lifo_get_item(&uart_lifo,&temp) == lifo_no_error )
			printf("UART get item : %d\n",temp);
	}
	


}
