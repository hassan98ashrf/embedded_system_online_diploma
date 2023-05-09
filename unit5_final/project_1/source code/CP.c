/*
Author : Hassan Ashraf Elsalakawy
Project 1 : control pressure
CP .c
*/

#include "CP.h"
//variables
int CP_led = 0;
int CP_pressure = 0;
int CP_threshold = 20;

CP_enum CP_state_id;
void (*CP_state)();

void PS_set_pressure(int pressure){
	CP_pressure = pressure;
	(CP_pressure <= CP_threshold)? (CP_state = STATE(CP_waiting)) : (CP_state = STATE(CP_driving));
}

STATE_def(CP_waiting){
	//State Name
	CP_state_id = CP_waiting;
	//State Action
	CP_led = 1;
	Set_Alarm_actuator(CP_led);
}
STATE_def(CP_driving){
	//State Name
	CP_state_id = CP_driving;
	//State Action
	CP_led =0;
	//ALARM_set_led(CP_led);
	Set_Alarm_actuator(CP_led);
}
