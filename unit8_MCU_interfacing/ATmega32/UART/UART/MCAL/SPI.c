/*
 * SPI.c
 *
 * Created: 6/26/2023 11:49:29 AM
 *  Author: hassa
 */ 


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//============== Includes ==============
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "SPI.h"
#include "LCD.h"



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========= GENERIC VARIABLES ==========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void (*GP_SPI_CallBack)(void);



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== APIs Supported by " MCAL GPIO DRIVER " ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void MCAL_SPI_Init(SPI_CFG_t *SPI_CFG){
	
	uint8_t tmp1 = 0 ,tmp2 = 0;
	
	//Interrupt Enable
	if(SPI_CFG->SPIE == SPIE_Enable){
		General_Interrupt_EN;
		tmp1 = (tmp1 & ~(1 << 7)) | SPI_CFG->SPIE;
		GP_SPI_CallBack = SPI_CFG->PSPI_CallBack;
	}
	
	//Data order MSB or LSB
	tmp1 = (tmp1 & ~(1 << 5)) | SPI_CFG->DORD;
	
	//Master/Slave Select
	tmp1 = (tmp1 & ~(1 << 4)) | SPI_CFG->MSTR;
	
	//Clock Polarity
	tmp1 = (tmp1 & ~(1 << 3)) | SPI_CFG->CPOL;
	
	//Clock Phase
	tmp1 = (tmp1 & ~(1 << 2)) | SPI_CFG->CPHA;
	
	//SPI Clock Rate Select
	tmp1 = (tmp1 & ~(1 << 0)) | SPI_CFG->SPRn;
	
	//Double SPI Speed Bit
	SPI->SPSR = (SPI->SPSR & ~(1 << 0)) | SPI_CFG->SPI2X;
	
	SPI->SPCR = tmp1;
	//SPI GPIO enable pins
	MCAL_SPI_GPIO_SetPins(SPI_CFG);
	
	//SPI Enable
	SPI->SPCR  = (SPI->SPCR & ~(1 << 6)) | SPI_CFG->SPE;
	
	
}



void MCAL_SPI_Reset(void){
	SPI->SPCR = 0x00;
	SPI->SPDR = 0x00;
	SPI->SPSR = 0x00;
}



void MCAL_SPI_GPIO_SetPins(SPI_CFG_t *SPI_CFG){
	
/*	
	
	Pin		|	Direction, Master SPI	|	Direction, Slave SPI
------------|---------------------------|----------------------------
	MOSI	|		User Defines		|			Input
------------|---------------------------|----------------------------
	MISO	|			Input			|		User Defines		
------------|---------------------------|----------------------------
	SCK		|		User Defines		|			Input				
------------|---------------------------|----------------------------
	SS		|		User Defines		|			Input				
------------|---------------------------|----------------------------


*/	

	//PB4---> SS
	//PB5--->MOSI
	//PB6--->MISO
	//PB7--->SCK

	 GPIO_CFG_t gpiocfg;
	if(SPI_CFG->MSTR == MSTR_Master){
		//MOSI
		gpiocfg.GPIO_PinNumber = GPIO_PinNumber_5;
		gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
		MCAL_GPIO_INIT_PIN(PORTB , &gpiocfg);
		
		//MISO
		gpiocfg.GPIO_PinNumber = GPIO_PinNumber_6;
		gpiocfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
		MCAL_GPIO_INIT_PIN(PORTB , &gpiocfg);
		
		//SCK
		gpiocfg.GPIO_PinNumber = GPIO_PinNumber_7;
		gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
		MCAL_GPIO_INIT_PIN(PORTB , &gpiocfg);
		
		//SS
		gpiocfg.GPIO_PinNumber = GPIO_PinNumber_4;
		gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
		MCAL_GPIO_INIT_PIN(PORTB , &gpiocfg);
		if(SPI_CFG->CPOL == CPOL_High)
			MCAL_GPIO_WRITE_PIN(PORTB , gpiocfg.GPIO_PinNumber , 1);
		if(SPI_CFG->CPOL == CPOL_Low)
			MCAL_GPIO_WRITE_PIN(PORTB , gpiocfg.GPIO_PinNumber , 0);								
	}
	else if (SPI_CFG->MSTR == MSTR_Slave){
				
		//MOSI
		gpiocfg.GPIO_PinNumber = GPIO_PinNumber_5;
		gpiocfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
		MCAL_GPIO_INIT_PIN(PORTB , &gpiocfg);
		
		//MISO
		gpiocfg.GPIO_PinNumber = GPIO_PinNumber_6;
		gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
		MCAL_GPIO_INIT_PIN(PORTB , &gpiocfg);
		
		//SCK
		gpiocfg.GPIO_PinNumber = GPIO_PinNumber_7;
		gpiocfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
		MCAL_GPIO_INIT_PIN(PORTB , &gpiocfg);
		
		//SS
		gpiocfg.GPIO_PinNumber = GPIO_PinNumber_4;
		gpiocfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
		MCAL_GPIO_INIT_PIN(PORTB , &gpiocfg);
	}
		
}



void MCAL_SPI_SendData(uint16_t PBuffer , SPI_CFG_t *SPI_CFG){
	if(SPI_CFG->MSTR == MSTR_Slave){
		SPI->SPDR = PBuffer ;
	}
	if(SPI_CFG->MSTR == MSTR_Master){
		MCAL_GPIO_WRITE_PIN(PORTB ,4,0);
		SPI->SPDR = PBuffer ;
		MCAL_GPIO_WRITE_PIN(PORTB ,4,1);
	}
	if(SPI_CFG->SPIE == SPIE_Disable)
		while(!(SPI->SPSR & (1 << 7)));
}



void MCAL_SPI_ReceiveData(uint16_t *PBuffer , SPI_CFG_t *SPI_CFG){
	if(SPI_CFG->SPIE == SPIE_Disable)
		while(!(SPI->SPSR & (1 << 7)));
	if(SPI_CFG->MSTR == MSTR_Master){
		MCAL_GPIO_WRITE_PIN(PORTB ,4,0);
		*PBuffer = SPI->SPDR ;
		MCAL_GPIO_WRITE_PIN(PORTB ,4,1);
	}
	if(SPI_CFG->MSTR == MSTR_Slave){
		*PBuffer = SPI->SPDR ;
	}
}




void __vector_12 (void) __attribute__((signal));
void __vector_12 (void)
{
	GP_SPI_CallBack();
}
