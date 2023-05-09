/*
Author : Hassan Ashraf Elsalakawy
Project 1 : control pressure
PS .h
*/

#ifndef PS_H_
#define PS_H_
#include "state.h"

//define state
typedef enum{
	PS_busy
} PS_enum;
extern PS_enum PS_state_id;

void PS_init();

STATE_def(PS_busy);

extern void (*PS_state)();

#endif /* PS_H_ */




