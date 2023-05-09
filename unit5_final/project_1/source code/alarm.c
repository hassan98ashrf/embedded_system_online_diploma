/*
Author : Hassan Ashraf Elsalakawy
Project 1 : control pressure
alarm .c
*/
#include "alarm.h"
int ALARM_led = 0;
ALARM_enum ALARM_state_id;
void (*ALARM_state)();
void ALARM_init(){
	//printf("=====ALARM_INIT===== \n");
}
void Set_Alarm_actuator(int led){
	ALARM_led = led;
	ALARM_state = STATE(ALARM_busy);
	if (led == 1){
		SET_BIT(GPIOA_ODR,13);	
	}
	else if (led == 0){
		RESET_BIT(GPIOA_ODR,13);	
	}
}
STATE_def(ALARM_ideal){
	//State Name
	ALARM_state_id = ALARM_ideal;
	//State Action
}
STATE_def(ALARM_busy){
	//State Name
	ALARM_state_id = ALARM_busy;
	//State Action
	ALARM_state = STATE(ALARM_ideal);
}