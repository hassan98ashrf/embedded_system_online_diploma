/*
 * KeyPad.h
 *
 * Created: 6/2/2023 12:16:21 PM
 *  Author: hassa
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#define F_CPU 1000000UL

#include "avr/io.h"
#include "util/delay.h"


#define  KeyPad_PORT PORTD
#define  Data_dir_KeyPad_PORT DDRD
#define  KeyPad_PIN PIND

#define R0 0
#define R1 1
#define R2 2 
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7

void KeyPad_Init();
char KeyPad_Get_char();




#endif /* KEYPAD_H_ */