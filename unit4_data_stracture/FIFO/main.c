/*
Author : Hassaan Ahsraf Elssalakawy
main.c
*/


#include "fifo.h"

element_type buffer[width];

void main(){

	element_type i, temp;

	//Static Allocation
	FIFO_Buffer_t UART_FIFO;
	if(FIFO_init(&UART_FIFO, buffer, 5) == FIFO_No_Error)
		printf("====FIFO Initialized Successfully==== \n");

	//Enqueue item
	printf("====FIFO enqueue start==== \n");
	for(i = 0; i < 7; i++){
		if(FIFO_enqueue(&UART_FIFO, i) == FIFO_No_Error)
			printf("FIFO Enqueue : %d \n", i);
		else
			printf("FIFO Failed : %d \n", i);
	}
	printf("====FIFO enqueue end==== \n");
	
	//Print FIFO items
	FIFO_print(&UART_FIFO);

	//Dequeue 2 items
	if(FIFO_dequeue(&UART_FIFO, &temp) == FIFO_No_Error)
		printf("FIFO dequeue : %d \n", temp);

	if(FIFO_dequeue(&UART_FIFO, &temp) == FIFO_No_Error)
		printf("FIFO dequeue : %d \n", temp);

	//Print FIFO items
	FIFO_print(&UART_FIFO);

}