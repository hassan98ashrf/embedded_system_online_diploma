/*
 * UART.c
 *
 * Created: 6/26/2023 11:36:28 AM
 *  Author: hassa
 */ 
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//============== Includes ==============
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "inc/USART.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========= GENERIC MACROS ==========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
 #define UBBR_SYNCH(_BAUD_ , F_CPU)			(uint16_t)(( ((float)(F_CPU))/ ( 2.0 * _BAUD_) ) - 0.5)



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========= GENERIC VARIABLES ==========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void (*GP_USART_CallBack[3])(void);



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== APIs Supported by "MCAL UART DRIVER" ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void MCAL_USART_Init(USART_CFG_t *USART_CFG){
	
	//Enable the interrupt	
	if(USART_CFG->INT_CASE){
		General_Interrupt_EN;	//Enable the general interrupt
		if(USART_CFG->USART_ENABLE == USART_ENABLE_RX || USART_CFG->USART_ENABLE == USART_ENABLE_TX_RX){
			USART->UCSRB |= (1 << 7);	//Bit 7 – RXCIE: RX Complete Interrupt Enable
		}
		else if(USART_CFG->USART_ENABLE == USART_ENABLE_TX || USART_CFG->USART_ENABLE == USART_ENABLE_TX_RX){
		//	USART->UCSRB |= (1 << 6);	//Bit 6 – TXCIE: TX Complete Interrupt Enable
		}
	//	USART->UCSRB |= (1 << 5);	//Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable
	}
	
//=========================================================================================================

	UCSRC_UBBRH |= 1 << 7;	//Select the UCSRC register
	UCSRC_UBBRH = (UCSRC_UBBRH & ~(1 << 6)) | (USART_CFG->CLK_MODE << 6);	//Bit 6 – UMSEL: Mode Select synch or Asynch

//=========================================================================================================
	
	if(USART_CFG->CLK_MODE == CLK_MODE_ASYNCH){
		USART->UCSRA = (USART->UCSRA & ~(1 << 1)) | (USART_CFG->Device_ASYNCH_MODE << 1);	//Bit 1 – U2X: Double the USART Transmission Speed
		UCSRC_UBBRH = (UCSRC_UBBRH & ~(0b11 << 4)) | (USART_CFG->Parity << 4);	//Bits 5:4 – UPMn: Parity Mode [n = 1:0]
		UCSRC_UBBRH = (UCSRC_UBBRH & ~(1 << 3)) | (USART_CFG->StopBits << 3);		//Bit 3 – USBS: Stop Bit Select
		
		//Set the Baud rate
		UCSRC_UBBRH &= ~(1 << 7);
		UCSRC_UBBRH = (UCSRC_UBBRH & ~(0xF)) | ((USART_CFG->BaudRate  >> 8) & 0xF);
		USART->UBBRL = USART_CFG->BaudRate  & 0xFF;

	}
	
//=========================================================================================================
	
	if(USART_CFG->CLK_MODE == CLK_MODE_SYNCH){
		UCSRC_UBBRH = (UCSRC_UBBRH & ~(1 << 0)) | (USART_CFG->ClockPolarity << 0);	//Bit 0 – UCPOL: Clock Polarity
		
			//Set the Baud rate
		USART->UBBRL = UBBR_SYNCH(USART_CFG->BaudRate , F_CPU) & 0xFF;
		UCSRC_UBBRH &= ~(1 << 7);
		UCSRC_UBBRH = (UCSRC_UBBRH & ~(0xF)) | ((UBBR_SYNCH(USART_CFG->BaudRate , F_CPU) >> 8) & 0xF);
		
		//Set master or slave
		MCAL_USART_GPIO_SetPins(USART_CFG);
	
	}
	
//=========================================================================================================
	
	//Bits 2:1 – UCSZn: Character Size [n = 1:0]
	if(USART_CFG->DataSize == DataSize_9){
		UCSRC_UBBRH |= 1 << 7;	//Select the UCSRC register
		UCSRC_UBBRH = (UCSRC_UBBRH & ~(0b11 << 1)) | (0b11 << 1);
		USART->UCSRB = (USART->UCSRB & ~(1 << 2)) | (1 << 2);
	}
	else if(USART_CFG->DataSize != DataSize_9){
		UCSRC_UBBRH |= 1 << 7;	//Select the UCSRC register
		UCSRC_UBBRH = (UCSRC_UBBRH & ~(0b11 << 1)) | (USART_CFG->DataSize << 1);
	}


//=========================================================================================================	
	
	//Bit 0 – MPCM: Multi-processor Communication Mode
	USART->UCSRA = (USART->UCSRA & ~(1)) | USART_CFG->MPCM_Case;
//=========================================================================================================
	
	//Bit4 – RXEN: Receiver Enable & Bit3 – TXEN: Transmitter Enable
	USART->UCSRB = (USART->UCSRB & ~(0b11 << 3)) | (USART_CFG->USART_ENABLE << 3);
	
	GP_USART_CallBack[0] = USART_CFG->P_USART_CallBack[0];
	GP_USART_CallBack[1] = USART_CFG->P_USART_CallBack[1];
	GP_USART_CallBack[2] = USART_CFG->P_USART_CallBack[2];
}



void MCAL_USART_Reset(void){
	USART->UBBRL = 0x00;
	USART->UCSRA = 0x20;
	USART->UCSRB = 0x0A;
	UCSRC_UBBRH |= (1 << 7);
	UCSRC_UBBRH = 0x06;
	UCSRC_UBBRH &= ~(1 << 7);
	UCSRC_UBBRH &= ~(0xF);
	USART->UDR = 0x00;
}



void MCAL_USART_GPIO_SetPins(USART_CFG_t *USART_CFG){
	
 	 GPIO_CFG_t gpiocfg;
	if(USART_CFG->Device_SYNCH_MODE == Device_SYNCH_MODE_Master){
		gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
		gpiocfg.GPIO_PinNumber = GPIO_PinNumber_0;
		MCAL_GPIO_INIT_PIN(PORTB , &gpiocfg);
	
	}
	else if(USART_CFG->Device_SYNCH_MODE == Device_SYNCH_MODE_Salve){
		gpiocfg.GPIO_Mode = GPIO_Mode_INPUT;
		gpiocfg.GPIO_PinNumber = GPIO_PinNumber_0;
		MCAL_GPIO_INIT_PIN(PORTB , &gpiocfg);
	}
 }



void MCAL_USART_SendData(uint16_t *PBuffer ,USART_CFG_t *USART_CFG){
	
	if(!USART_CFG->INT_CASE){
	//	while(!(USART->UCSRA & (1 << 6)));		//Bit 6 – TXC: USART Transmit Complete
	//	while(!(USART->UCSRA & (1 << 5)));		//Bit 5 – UDRE: USART Data Register Empty
	}
	
	if(USART_CFG->DataSize == DataSize_9){
		//				(			mask		) | (		  VAL		)
		USART->UCSRB = (USART->UCSRB & ~(1 << 0)) | ((*PBuffer >> 8) & 1);	//TXB8 is the ninth data bit in the character to be transmitted
	}
	//*PBuffer = (*PBuffer & (((uint16_t)1) << 8)) | (USART->UDR  & 0xFF);
	USART->UDR = *PBuffer & 0xFF;
};



void MCAL_USART_ReceiveData(uint16_t *PBuffer , USART_CFG_t *USART_CFG){
	if(!USART_CFG->INT_CASE){
		while(!(USART->UCSRA & (1 << 7)));		//Bit 7 – RXC: USART Receive Complete
	}
	
	if(USART_CFG->DataSize == DataSize_9){
		*PBuffer = 0;
		*PBuffer = ((USART->UCSRB >> 1) & 1) << 8;	//RXB8 is the ninth data bit in the character to be received	
	}
	*PBuffer = (*PBuffer & (((uint16_t)1) << 8)) | (USART->UDR  & 0xFF);
	
};


void __vector_13 (void) __attribute__((signal));
void __vector_13 (void)
{
	GP_USART_CallBack[0]();
}


void __vector_14 (void) __attribute__((signal));
void __vector_14 (void)
{
	GP_USART_CallBack[1]();
}


void __vector_15 (void) __attribute__((signal));
void __vector_15 (void)
{
	GP_USART_CallBack[2]();
}
