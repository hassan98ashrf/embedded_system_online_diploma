/*
 * interrupt.c
 *
 * Created: 5/25/2023 8:15:23 AM
 * Author : hassan
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SET_BIT(ADDRESS,BIT) ADDRESS |= (1<<BIT)
#define CLEAR_BIT(ADDRESS,BIT) ADDRESS &= ~(1<<BIT)
#define TOGGLE_BIT(ADDRESS,BIT) ADDERSS ^= (1<<BIT)
#define READ_BIT(ADDRESS,BIT) ((ADDERSS & (1<<BIT))>>BIT)

#define BASE_IO 0x20
#define IO_PORTD *(volatile unsigned int *)(BASE_IO +0x12)
#define IO_DDRD *(volatile unsigned int *)(BASE_IO +0x11)
#define INT_MCUCR *(volatile unsigned int *)(BASE_IO +0x35)
#define INT_MCUCSR *(volatile unsigned int *)(BASE_IO +0x34)
#define INT_GICR *(volatile unsigned int *)(BASE_IO +0x3B)
int main(void)
{
	//pin 5,6,7 output
	SET_BIT(IO_DDRD,5);
	SET_BIT(IO_DDRD,6);
	SET_BIT(IO_DDRD,7);
	//INT0 logical
	SET_BIT(INT_MCUCR,0);
	CLEAR_BIT(INT_MCUCR,1);
	//INT1 rising edge
	SET_BIT(INT_MCUCR,2);
	SET_BIT(INT_MCUCR,3);
	//INT2 falling edge
	CLEAR_BIT(INT_MCUCSR,6);
	//enable INT0 , INT1 , INT2
	SET_BIT(INT_GICR,5);
	SET_BIT(INT_GICR,6);
	SET_BIT(INT_GICR,7);
	//enable G_interrupt
	sei();

    while (1) 
    {
		//to show any chang
		CLEAR_BIT(IO_PORTD,5);
		CLEAR_BIT(IO_PORTD,6);
		CLEAR_BIT(IO_PORTD,7);
    }
}

ISR(INT0_vect){
	SET_BIT(IO_PORTD,5);
	_delay_ms(1000);
}
ISR(INT1_vect){
	SET_BIT(IO_PORTD,6);
	_delay_ms(1000);
}
ISR(INT2_vect){
	SET_BIT(IO_PORTD,7);
	_delay_ms(1000);
}
