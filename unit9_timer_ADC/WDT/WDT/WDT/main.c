/*
 * WDT.c
 *
 * Created: 7/1/2023 9:37:26 AM
 * Author : hassa
 */ 

#define  F_CPU						8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define  SET_BIT(PORT,BIT)			(PORT |= (1 << BIT))
#define  RESET_BIT(PORT,BIT)		(PORT &= ~(1 << BIT))
#define  TOGGLE_BIT(PORT,BIT)		(PORT ^= (1 << BIT))
#define  READ_BIT(PORT,BIT)			(PORT & (1 << BIT))

#define  LED_DDR					DDRC
#define  LED_PORT					PORTC
#define  LED_PIN					0


void WDT_OFF()
{
	WDTCR |= (1 << WDTOE ) | (1 << WDE);
	WDTCR = 0x00;
}

void WDT_ON()
{
	WDTCR |= (1 << WDE ) | (1 << WDP1) | (1 << WDP2);
	RESET_BIT (WDTCR, WDP0);
}


int main(void)
{
    SET_BIT(LED_DDR,LED_PIN);
	_delay_ms(100);
    while (1) 
    {
		WDT_ON();
		TOGGLE_BIT(LED_PORT,LED_PIN);
		_delay_ms(2000);   //if higer than 1000 ms WDT will reset System
		WDT_OFF();
		
    }
}

