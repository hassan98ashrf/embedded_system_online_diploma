/*
 * LCD.h
 *
 * Created: 6/26/2023 10:20:19 AM
 *  Author: hassa
 */ 


#ifndef LCD_H_
#define LCD_H_


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//============== Includes ==============
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#include "Atmega32.h"
#include "GPIO.h"

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//=========== GENERIC MACROS ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define LCD_INPUT_PINS		0x87		//Zeros on the input pins of the LCD to be masked with the input
#define PORT_OUTPUT_PINS	0x78		//ones on the output pins of the port to be masked with the output to the LCD


#define MOST_BIT_PIN		1			//used to shift right the LCD input if it is in the middle of the Port  specially in 4 bit mode
#define LEAST_BIT_PIN		3			//used to shift left the LCD input if it is in the middle of the Port specially in 4 bit mode

#define RS					1			//The register select pin
#define EN 					2			//enable pin
//#define WR 							//read write pin
//#define BF_PIN 						//busy flag pin

//MICROCONTROLLER CONFIGURATIONS
#define LCD_DATA   	PORTA->PORT			//Output data register of GPIO to LCD
#define LCD_CTRL    PORTA->PORT			//Output control register of LCD  (RS , WR , EN) pins

//todo
//#define LCD_DATA_DIR
//#define LCD_CTRL_DIR
//#define CONFIG_DATA_CTRL(x,y) LCD_DATA_DIR = ((LCD_DATA_DIR & PORT_INPUT_PINS) | PORT_##x##_PINS); LCD_CTRL_DIR = ((LCD_DATA_DIR & PORT_INPUT_PINS) | PORT_##y##_PINS);
/**************************************/


//LCD CONTROL
#define LCD_ENABLE							 LCD_CTRL |=(1<<EN); _delay_ms(50); LCD_CTRL &= ~(1<<EN); _delay_ms(200);	//Enable of the LCD
//#define LCD_READ_DATA                      ((1<<WR) | (1<<RS)) 			//Read data from the LCD to GPIO configurations
//#define LCD_READ_INSTRUCTION               ((1<<WR) & ~(1<<RS)) 			//Read INSTRUCTION from the LCD to GPIO configurations
#define LCD_WRITE_DATA                      (1<<RS) 						//Write data from the GPIO TO LCD configurations
#define LCD_WRITE_INSTRUCTION				~(1<<RS) 						//Write INSTRUCTION from the GPIO to LCD configurations

/**************************************/

//LCD MODES

//#define EIGHT_BIT_MODE
#define FOUR_BIT_MODE

/**************************************/

//LCD INSTRUCTIONS
#define LCD_Clear_Display              0x01
#define LCD_Return_Home                0x02
#define LCD_Enty_Mode_Set_Dec          0x04
#define LCD_Enty_Mode_Set_Inc_Shift    0x05
#define LCD_Enty_Mode_Set_Inc          0x06
#define LCD_Enty_Mode_Set_Dec_Shift    0x07
#define LCD_DISP_OFF                   0x08
#define LCD_DISP_ON                    0x0C
#define LCD_DISP_ON_BLINK              0x0D
#define LCD_DISP_ON_CURSOR             0x0E
#define LCD_DISP_ON_CURSOR_BLINK       0x0F
#define LCD_MOV_CURSOR_LEFT            0x10
#define LCD_MOV_CURSOR_RIGHT           0x14
#define LCD_MOV_DISP_LEFT              0x18
#define LCD_MOV_DISP_RIGHT             0x1C
#define LCD_4BITS_2LINES_5X10          0x2C
#define LCD_4BITS_2LINES_5X8           0x28
#define LCD_4BITS_1LINE_5X10           0x24
#define LCD_4BITS_1LINE_5X8            0x20
#define LCD_8BITS_2LINES_5X10          0x3C
#define LCD_8BITS_2LINES_5X8           0x38
#define LCD_8BITS_1LINE_5X10           0x34
#define LCD_8BITS_1LINE_5X8            0x30
#define LCD_ROW1_COLUMN1               0x80
#define LCD_ROW2_COLUMN2               0xC0
#define BAISX   128
#define BAISY   64

/**************************************/

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== APIs Supported by " HAL LCD DRIVER " ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void LCD_Init();

void LCD_BF_check(void);

void LCD_write_number(int num);

void LCD_write_real_num(double num);

void LCD_write_string(char* string);

void GOTO_XY(unsigned char x ,unsigned char y);

void LCD_write_command(unsigned char command);

void LCD_write_char(unsigned char character);

#endif /* LCD_H_ */