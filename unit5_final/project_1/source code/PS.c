/*
Author : Hassan Ashraf Elsalakawy
Project 1 : control pressure
PS .C
*/
#include "PS.h"

//variables
int PS_pressure = 0;
PS_enum PS_state_id;

void (*PS_state)();

void PS_init(){
	//printf("=====PS_INIT=====\n");
}

STATE_def(PS_busy){

	//State Name
	PS_state_id = PS_busy;

	//State Action
	PS_pressure = getPressureVal();
	//printf("PS_busy state: pressure = %d \n", PS_pressure);
	PS_set_pressure(PS_pressure);
	PS_state = STATE(PS_busy);
}


