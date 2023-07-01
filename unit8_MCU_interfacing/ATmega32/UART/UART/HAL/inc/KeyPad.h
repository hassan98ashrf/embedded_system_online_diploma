/*
 * KeyPad.h
 *
 * Created: 6/26/2023 10:12:01 AM
 *  Author: hassa
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//============== Includes ==============
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "Atmega32.h"
#include "GPIO.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//=========== GENERIC MACROS ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define KEYPAD_ROWS_INPUT 		PORTB->PIN		//Input register of rows
#define KEYPAD_COLUMNS_OUTPUT  	PORTC->PORT		//Output register of columns

#define COLUMNS_PINS			0x3C			//Ones on the columns pins used for configurations
#define ROW_PINS				0xF0			//Ones on the rows pins used for configurations

//Rows pin numbers
#define R0  4
#define R1  5
#define R2  6
#define R3  7

//Columns pin numbers
#define C0  2
#define C1  3
#define C2  4
#define C3  5



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== APIs Supported by " HAL KEYPAD DRIVER " ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void KeyPad_Init();
char KeyPad_get_char();



#endif /* KEYPAD_H_ */