/*
 * 7_segment.c
 *
 * Created: 5/30/2023 7:21:42 PM
 * Author : hassa
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
//#include "mem_map.h"
#include "utils.h"
#include <util/delay.h>


int main(void)
{
	
	// port a as an output led
	SETBIT(DDRD,5);
	SETBIT(DDRD,6);
	SETBIT(DDRD,7);
	// port a as an output led
	SETBIT(DDRD,4);
	
	// port c as an input
	CLEARBIT(DDRD,0);
	CLEARBIT(DDRD,1); 
	SETBIT(PORTD,0);
	SETBIT(PORTD,1);
	volatile unsigned count = 5;
	while (1)
	{
		//turn on led
		while (count <=7 && READBIT(PIND,0)==1){
			SETBIT(PORTD,count);
			count++;
			_delay_ms(400);
		}
		count--;
		//turn off led
		while(count >=5 && READBIT(PIND,0)==1){
			CLEARBIT(PORTD,count); 
			count--;
			_delay_ms(400);
		}
		count++;
		//alarm
		while (READBIT(PIND,1)==1){
			SETBIT(PORTD,4);
			_delay_ms(2000);
			CLEARBIT(PORTD,4);
		}
		
	}
}

