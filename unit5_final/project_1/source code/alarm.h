/*
Author : Hassan Ashraf Elsalakawy
Project 1 : control pressure
alarm .h
*/


#ifndef ALARM_H_
#define ALARM_H_

#include "state.h"

typedef enum{
	ALARM_ideal,
	ALARM_busy
} ALARM_enum;
extern ALARM_enum ALARM_state_id;

void ALARM_init();

STATE_def(ALARM_ideal);
STATE_def(ALARM_busy);

extern void (*ALARM_state)();

#endif /* ALARM_H_ */



