
/*
Author : Hassan  Ashraf Elsalakawy
LEFO.c
*/
#include "lifo.h"



lifo_status lifo_init_item (lifo_buff_t * lifo_buf  , element_type *buf  , unsigned int length ){
	if(buf==NULL){
		return lifo_null;
	}
	lifo_buf ->base  =  buf;
	lifo_buf ->head  =  buf;
	lifo_buf ->length  =  length;
	lifo_buf ->count  =  0;
	
	return lifo_no_error;
	
}

lifo_status lifo_add_item (lifo_buff_t * lifo_buf  , element_type item ){
	//check valid
	if(!(lifo_buf->base) || !(lifo_buf->head))
		return lifo_null;

	//Check if LIFO is full
	if(lifo_buf->count == lifo_buf->length)
		return lifo_full;

	//PUSH item
	*(lifo_buf->head) = item;
	lifo_buf->head++;
	lifo_buf->count++;

	return lifo_no_error;
	
}


lifo_status lifo_get_item (lifo_buff_t * lifo_buf  , element_type *item ){
	//check valid
	if(!(lifo_buf->base) || !(lifo_buf->head))
		return lifo_null;

	//Check if LIFO is empty
	if(lifo_buf->count == 0)
		return lifo_empty;

	//POP item
	lifo_buf->head--;
	*item = *(lifo_buf->head);
	lifo_buf->count--;

	return lifo_no_error;
	
}

lifo_status lifo_top(lifo_buff_t* lifo_buf, unsigned int* item){

	//Check LIFO validity
	if(!(lifo_buf->base) || !(lifo_buf->head))
		return lifo_null;

	//Check if LIFO is empty
	if(lifo_buf->count == 0)
		return lifo_empty;

	//TOP item
	lifo_buf->head--;
	*item = *(lifo_buf->head);
	lifo_buf->head++;

	return lifo_no_error;
}


