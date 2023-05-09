/*
Author : Hassan Ashraf Elsalakawy
Project 1 : control pressure
main .c
*/
#include "CP.h"
#include "PS.h"
#include "alarm.h"
void setup(){

	//Initialize Blocks
	PS_init();
	ALARM_init();

	//Set State pointers to their corresponding block
	CP_state = STATE(CP_waiting);
	PS_state = STATE(PS_busy);
	ALARM_state = STATE(ALARM_ideal);
}
void main(){
	GPIO_INITIALIZATION();
	setup();
	while(1){
		//Call state pointer of each block
		PS_state();
		CP_state();
		ALARM_state();

		//Delay loop
		Delay(2000);
	}
}
