
/*
Author : Hassan  Ashraf Elsalakawy
LEFO.h
*/

#ifndef LEFO_H_
#define LEFO_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define element_type uint32_t
#define width 5
typedef struct {
	unsigned int length;
	unsigned int count;
	element_type *base;   //start  of LIFO
	element_type *head; //change of end of LIFO
}lifo_buff_t;

typedef enum{
	lifo_no_error,
	lifo_full,
	lifo_empty,
	lifo_null
}lifo_status;

//APIs
lifo_status lifo_add_item (lifo_buff_t * lifo_buf  , element_type item );
lifo_status lifo_get_item (lifo_buff_t * lifo_buf  ,element_type *item );
lifo_status lifo_init_item (lifo_buff_t * lifo_buf  , element_type *buf  , unsigned int length );
lifo_status lifo_top(lifo_buff_t* lifo_buf, element_type* item);





#endif