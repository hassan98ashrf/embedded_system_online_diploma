/*
Author : Hassan Ashraf Elsalakawy
Project 1 : control pressure
state .h
*/

#ifndef STATE_H_
#define STATE_H_
#include "driver.h"
#include <stdio.h>
#include <stdlib.h>

//State function generator
#define STATE_def(_stateFun_) void State_##_stateFun_()
#define STATE(_stateFun_) State_##_stateFun_

//Triggered signals interface
void PS_set_pressure(int pressure);
void ALARM_set_led(int led);



#endif /* STATE_H_ */