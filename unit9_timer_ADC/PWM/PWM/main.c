/*
 * PWM.c
 *
 * Created: 7/1/2023 5:27:21 PM
 * Author : hassa
 */ 

#define F_CPU	8000000UL
#include "PWM.h"
#include "util/delay.h"
#define PIN_NUM			0
uint32_t timer_counter = 0;


void Timer_OverFlow_Interrupt_Handler(void)
{
	timer_counter++;
	if(timer_counter == 3921)
	{
		//Toggle Led every one second
		TOGGLE_BIT(PORTD, PIN_NUM);
		//Clear Counter
		timer_counter = 0;
	}
}

void Timer_CompareMatch_Interrupt_Handler(void)
{
	timer_counter++;
	if(timer_counter == 10000)
	{
		//Toggle Led every one second
		TOGGLE_BIT(PORTD, PIN_NUM);
		//Clear Counter
		timer_counter = 0;
	}
}


int main(void)
{
	//Configure PIND0 as Output
	SET_BIT(DDRD, PIN_NUM);
	//set compare value
	MCAL_SetTimer_compare_val(100);
	//set timer configuration
	TIMER_CONFIG_t timer_cfg;
	timer_cfg.Timer_Mode = TIMER_MODE_CTC;
	timer_cfg.Clock_Source = CLOCK_SOURCE_INTERNAL_PRESCALER_DIVIDED_BY_8;
	timer_cfg.IRQ_Enable = IRQ_ENABLE_OCIE0;
	timer_cfg.P_CallBack = Timer_CompareMatch_Interrupt_Handler;
	MCAL_Timer_Init(&timer_cfg);
	while (1)
	{
		
	}
}
