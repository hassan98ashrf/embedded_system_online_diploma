/*
 * 7 led.c
 *
 * Created: 5/30/2023 2:01:49 PM
 * Author : hassan
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
//#include "mem_map.h"
#include "utils.h"
#include <util/delay.h>


int main(void)
{
    // port a as an output
	DDRA = 0xff;
    while (1) 
    {
		volatile unsigned count = 0;
		//led on from pin0 to pin 7
		while (count <= 7)
		{
			_delay_ms(500);
			SETBIT (PORTA,count);
			count++;
		}
		//led of from pin7 to pin 0
		while (count !=255)
		{
			_delay_ms(500);
			 CLEARBIT (PORTA,count);
			 count--;
		 }
		
    }
}

