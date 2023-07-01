/*
 * GPIO.c
 *
 * Created: 6/26/2023 11:46:39 AM
 *  Author: hassa
 */ 

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//============== Includes ==============
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "inc/GPIO.h"
#include "inc/Atmega32.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== APIs Supported by " MCAL GPIO DRIVER " ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void MCAL_GPIO_INIT_PIN( GPIO_t * PORTx ,  GPIO_CFG_t * PIN){
	
	if(PIN->GPIO_Mode == GPIO_Mode_INPUT){
		PORTx->DDR = (PORTx->DDR & ~(1 << PIN->GPIO_PinNumber)) | (PIN->GPIO_Mode << PIN->GPIO_PinNumber);
		PORTx->PORT &= 1 << PIN->GPIO_PinNumber;
	}
	else if(PIN->GPIO_Mode == GPIO_Mode_INPUT_FLO){
		PORTx->DDR &= ~(1 << PIN->GPIO_PinNumber);
		PORTx->PORT &= ~(1 << PIN->GPIO_PinNumber);
	}
	else{
		PORTx->DDR = (PORTx->DDR & ~(1 << PIN->GPIO_PinNumber)) | (PIN->GPIO_Mode << PIN->GPIO_PinNumber);
	}
}


void MCAL_GPIO_RESET( GPIO_t* PORTx_RESET){
	PORTx_RESET->DDR = 0;
	PORTx_RESET->PIN = 0;
	PORTx_RESET->PORT = 0;
}

unsigned char MCAL_GPIO_READ_PIN( GPIO_t* PORTx , unsigned char PIN_NUMBER){
	return (PORTx->PIN >> PIN_NUMBER & 1);
}

unsigned char MCAL_GPIO_READ_PORT( GPIO_t * PORTx){
	return PORTx->PIN;
}


void MCAL_GPIO_WRITE_PIN( GPIO_t * PORTx , unsigned char PIN_NUMBER , unsigned char VAL){
	PORTx->PORT = (PORTx->PORT & ~(1 << PIN_NUMBER)) | (VAL << PIN_NUMBER);
}


void MCAL_GPIO_WRITE_PORT( GPIO_t* PORTx , unsigned char VAL){
	PORTx->PORT = VAL;
}

void MCAL_GPIO_tOGGLE_PIN( GPIO_t* PORTx , unsigned char PIN_NUMBER){
	PORTx->PORT ^= (1 << PIN_NUMBER);
}

