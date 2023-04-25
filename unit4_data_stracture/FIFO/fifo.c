/*
Author : Hassaan Ahsraf Elssalakawy
FIFO.c
*/
#include "fifo.h"

FIFO_Status FIFO_init(FIFO_Buffer_t* FIFO_Buffer, element_type* buff, uint32_t length){

	//Check Buffer availability
	if(buff == NULL)
		return FIFO_Null;

	//Initialize FIFO
	FIFO_Buffer->base = buff;
	FIFO_Buffer->head = buff;
	FIFO_Buffer->tail = buff;
	FIFO_Buffer->length = length;
	FIFO_Buffer->count = 0;

	return FIFO_No_Error;
}

FIFO_Status FIFO_enqueue(FIFO_Buffer_t* FIFO_Buffer, element_type item){

	//Check FIFO validity
	if(!(FIFO_Buffer->base) || !(FIFO_Buffer->head) || !(FIFO_Buffer->tail))
		return FIFO_Null;

	//Check if FIFO is full
	if(FIFO_isFull(FIFO_Buffer) == FIFO_Full)
		return FIFO_Full;

	//Enqueue item
	*(FIFO_Buffer->head) = item;
	FIFO_Buffer->count++;

	if(FIFO_Buffer->head == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(element_type))))
		FIFO_Buffer->head = FIFO_Buffer->base;
	else
		FIFO_Buffer->head++;

	return FIFO_No_Error;
}

FIFO_Status FIFO_dequeue(FIFO_Buffer_t* FIFO_Buffer, element_type* item){

	//Check FIFO validity
	if(!(FIFO_Buffer->base) || !(FIFO_Buffer->head) || !(FIFO_Buffer->tail))
		return FIFO_Null;

	//Check if FIFO is empty
	if(FIFO_Buffer->count == 0)
		return FIFO_Empty;

	//Dequeue item
	*item = *(FIFO_Buffer->tail);
	FIFO_Buffer->count--;

	if(FIFO_Buffer->tail == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(element_type))))
		FIFO_Buffer->tail = FIFO_Buffer->base;
	else
		FIFO_Buffer->tail++;

	return FIFO_No_Error;
}

FIFO_Status FIFO_isFull(FIFO_Buffer_t* FIFO_Buffer){

	//Check FIFO validity
	if(!(FIFO_Buffer->base) || !(FIFO_Buffer->head) || !(FIFO_Buffer->tail))
		return FIFO_Null;

	//Check if FIFO is full
	if(FIFO_Buffer->count == FIFO_Buffer->length)
		return FIFO_Full;

	return FIFO_No_Error;
}

void FIFO_print(FIFO_Buffer_t* FIFO_Buffer){

	//Check FIFO validity
	if(!(FIFO_Buffer->base) || !(FIFO_Buffer->head) || !(FIFO_Buffer->tail)){
		printf("FIFO is not Valid");
		return;
	}

	//Check if FIFO is empty
	if(FIFO_Buffer->count == 0){
		printf("FIFO is Empty");
		return;
	}

	//Print items
	element_type *temp;
	temp = FIFO_Buffer->tail;
	for(int i = 0; i < FIFO_Buffer->count; i++){
		printf("FIFO Item %d = %d \n", i, *temp);
		temp++;
	}
}









