/*
 * output.c
 *
 * Created: 5/30/2023 3:19:59 PM
 * Author : hassa
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
	// port c as an input
	DDRC = 0x00;
	PORTC = 0xff;
	volatile unsigned count = 0;
	while (1)
	{
		
		if (READBIT(PINC,0)==0){
			SETBIT(PORTA,count);
			count++;
			_delay_ms(250);
		}
		
		
		
	}
}

