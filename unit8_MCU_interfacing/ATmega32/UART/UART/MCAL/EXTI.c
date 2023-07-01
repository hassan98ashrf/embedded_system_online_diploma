/*
 * EXTI.c
 *
 * Created: 6/26/2023 11:48:01 AM
 *  Author: hassa
 */ 


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//============== Includes ==============
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "inc/EXTI.h"



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========= GENERIC VARIABLES ==========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void(* GP_INT_CallBack[3])(void);



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== APIs Supported by " MCAL GPIO DRIVER " ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void MCAL_EXTI_INIT( EXTI_CFG_t* EXTI_CFG){
	General_Interrupt_EN;		//Enable the general interrupt in the status register
	
	//Configure the trigger case of the interrupt and enable it
	if(EXTI_CFG->INT_NUM == INT_NUM_0){
		EXTI->MCUCR = (EXTI->MCUCR & ~(0x3)) | (EXTI_CFG->Trigger_Case);
		EXTI->GICR = (EXTI->GICR & ~(1 << 6)) | (EXTI_CFG->EXTI_State << 6);
		GP_INT_CallBack[0] = EXTI_CFG->P_INT_CallBack;
	}
	else if (EXTI_CFG->INT_NUM == INT_NUM_1){
		EXTI->MCUCR = (EXTI->MCUCR & ~(0b11 << 2)) | (EXTI_CFG->Trigger_Case << 2);
		EXTI->GICR = (EXTI->GICR & ~(1 << 7)) | (EXTI_CFG->EXTI_State << 7);
		GP_INT_CallBack[1] = EXTI_CFG->P_INT_CallBack;
	}
	else if (EXTI_CFG->INT_NUM == INT_NUM_2){
		EXTI->GICR &= ~(1 << 5);
		EXTI->MCUCSR |=  (EXTI_CFG->Trigger_Case << 6);
		EXTI->GIFR |= (1 << 5);
		EXTI->GICR |= (EXTI_CFG->EXTI_State << 5);
		GP_INT_CallBack[2] = EXTI_CFG->P_INT_CallBack;
	}
	
	
}



void MCAL_EXTI_RESET(unsigned char INT_NUM){
	if(INT_NUM == INT_NUM_0){
		EXTI->GICR &= ~(1 << 6);
		EXTI->GIFR &= ~(1 << 6);
		
	}
	else if (INT_NUM == INT_NUM_1){
		EXTI->GICR &= ~(1 << 7);
		EXTI->GIFR &= ~(1 << 7);
	}
	else if (INT_NUM == INT_NUM_2){
		EXTI->GICR &= ~(1 << 5);
		EXTI->GIFR &= ~(1 << 5);
	}
}



void MCAL_EXTI_GPIO_CFG(unsigned char INT_NUM){
	if(INT_NUM == INT_NUM_0){
		//PORTD.2
		GPIO_CFG_t INT0_PIN;
		INT0_PIN.GPIO_PinNumber = GPIO_PinNumber_2;
		INT0_PIN.GPIO_Mode = GPIO_Mode_INPUT;
		MCAL_GPIO_INIT_PIN(PORTD , &INT0_PIN);
		
	}
	else if (INT_NUM == INT_NUM_1){
		//PORTD.3
		GPIO_CFG_t INT1_PIN;
		INT1_PIN.GPIO_PinNumber = GPIO_PinNumber_3;
		INT1_PIN.GPIO_Mode = GPIO_Mode_INPUT;
		MCAL_GPIO_INIT_PIN(PORTD , &INT1_PIN);
	}
	else if (INT_NUM == INT_NUM_2){
		//PORTB.2
		GPIO_CFG_t INT2_PIN;
		INT2_PIN.GPIO_PinNumber = GPIO_PinNumber_2;
		INT2_PIN.GPIO_Mode = GPIO_Mode_INPUT;
		MCAL_GPIO_INIT_PIN(PORTB , &INT2_PIN);
	}
}


void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	GP_INT_CallBack[0]();
}


void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	GP_INT_CallBack[1]();
}


void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	GP_INT_CallBack[2]();
}