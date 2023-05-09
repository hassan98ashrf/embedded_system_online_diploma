/*
Author : Hassan Ashraf Elsalakawy
Project 1 : control pressure
CP .h
*/
#ifndef CP_H_
#define CP_H_
#include "state.h"

typedef enum{
	CP_waiting,
	CP_driving
} CP_enum;
extern CP_enum CP_state_id;

STATE_def(CP_waiting);
STATE_def(CP_driving);

extern void (*CP_state)();

#endif /* CP_H_ */