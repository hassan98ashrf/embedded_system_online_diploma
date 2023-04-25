/*
Author : Hassaan Ahsraf Elssalakawy
FIFO.h
*/
#ifndef FIFO_H_
#define FIFO_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
/* USER Configuration */
#define element_type uint8_t

/* Buffer Definition */
#define width 5

/* FIFO Data types */
typedef struct{
	uint32_t length;
	uint32_t count;
	element_type* base;
	element_type* head;
	element_type* tail;
} FIFO_Buffer_t;

typedef enum{
	FIFO_No_Error,
	FIFO_Full,
	FIFO_Empty,
	FIFO_Null
} FIFO_Status;

/* APIs */
FIFO_Status FIFO_init(FIFO_Buffer_t* FIFO_Buffer, element_type* buff, uint32_t length);
FIFO_Status FIFO_enqueue(FIFO_Buffer_t* FIFO_Buffer, element_type item);
FIFO_Status FIFO_dequeue(FIFO_Buffer_t* FIFO_Buffer, element_type* item);
FIFO_Status FIFO_isFull(FIFO_Buffer_t* FIFO_Buffer);
void FIFO_print(FIFO_Buffer_t* FIFO_Buffer);

#endif