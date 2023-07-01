/*
 * LCD.c
 *
 * Created: 6/2/2023 10:51:28 AM
 * Author : hassa
 */ 

#include <avr/io.h>
#include "LCD driver/lcd.h"
#include "keypad driver/KeyPad.h"

int main(void)
{
    LCD_init();
	KeyPad_Init();
	//LCD_write_char('A');
	//LCD_write_string("AaBbCCcDdEeFfGgHhIiJj");
	char press_key;
    while (1) 
    {
		press_key = KeyPad_Get_char();
		switch(press_key)
		{
			case ('!'):
				LCD_Clear_screen();
				break;
			case ('N'):
				break;
			default:
				LCD_write_char(press_key);
				break;
		}
			
    }
}

