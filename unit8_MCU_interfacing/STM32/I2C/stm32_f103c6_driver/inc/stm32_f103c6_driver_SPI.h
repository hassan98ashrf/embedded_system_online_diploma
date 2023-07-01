/*
 * stm32_f103c6_driver_SPI.h
 *
 *  Created on: Jun 23, 2023
 *      Author: hassa
 */

#ifndef INC_STM32_F103C6_DRIVER_SPI_H_
#define INC_STM32_F103C6_DRIVER_SPI_H_



//================================
//INCLUDES
//================================
#include "stm32_f103c6.h"
#include "stm32_f103c6_driver_GPIO.h"
#include "stm32_f103c6_driver_RCC.h"


//================================
//GENERIC VARIABLES
//================================
struct S_IRQ_SRC{
	uint8_t TXE:1; //Tx buffer empty interrupt
	uint8_t RXNE:1; //Rx buffer not empty interrupt
	uint8_t ERRI:1; //Error interrupt
	uint8_t Reserved:5;	//Don't touch
};


//Config Structure
typedef struct
{
	uint16_t MSTR;				//Specifies the SPI operation mode (Master/Slave)
								// This parameter must be set based on @ref MSTR_define

	uint16_t BIDIOE_BIDIMODE;	//Output enable in bidirectional mode & Bidirectional data mode enable
								// This parameter can be a value of @ref BIDIOE_BIDIMODE_define

	uint16_t LSBFIRST;			//Specifies (LSB/MSB)
								// This parameter can be a value of @ref LSBFIRST_define

	uint16_t DFF;				//Specifies Data size transmitted
								// This parameter can be a value of @ref DFF_define

	uint16_t CPOL;				//Specifies Polarity of the SPI clock
								// This parameter can be a value of  @ref CPOL_define

	uint16_t CPHA;				//Specifies Phase of the SPI clock
								// This parameter can be a value of @ref CPHA_define

	uint16_t NSS;				//Specifies whether the NSS signal is managed byhardware (NSS pin) or by software using the SSI bit enable
								// This parameter can be a value of @ref NSS_define

	uint16_t BR;				//Specifies the baud rate prescalar value which will be used to configure
								//the transmit and receive SCK clock.
								//This parameter can be a value of @ref BR_define


	uint16_t SPI_IRQ;			//Enable the interrupt of the SPI
								// This parameter can be a value of @ref SPI_IRQ_define

	void(*P_IRQ_CallBack)(struct S_IRQ_SRC irq_src);//Set the function() which will be called once the IRQ happen

}SPI_PinConfig_t;

//================================
//Macros Configuration References
//================================

//@ref MSTR_define
#define MSTR_Slave							0					//Slave configuration
#define MSTR_Master 						(1 << 2)			//Master configuration

//@ref BIDIOE_BIDIMODE_define
#define BIDIOE_BIDIMODE_2LINES				0					//2-line unidirectional data mode selected & Output disabled (receive-only mode)
#define BIDIOE_BIDIMODE_2LINES_RXONLY		(1 << 10) 			//Output disabled (Receive-only mode) & Output disabled (receive-only mode)
#define BIDIOE_BIDIMODE_1LINE_ReceiveONLY	(1 << 15)			//1-line bidirectional data mode selected
#define BIDIOE_BIDIMODE_1LINE_transmitONLY	(1 << 15 | 1 << 14) //Output enabled (transmit-only mode) & 1-line bidirectional data mode selected



// @ref LSBFIRST_define
#define LSBFIRST_MSB						0					//MSB transmitted first
#define LSBFIRST_LSB						(1 << 7)			//LSB transmitted first


//@ref DFF_define
#define DFF_8BIT							0					//8-bit data frame format is selected for transmission/reception
#define DFF_16BIT							(1 << 11)			//16-bit data frame format is selected for transmission/reception




//@ref CPOL_define
#define CPOL_LOW							0					//CK to 0 when idle
#define CPOL_HIGH							(1 << 1)			//CK to 1 when idle

//@ref Baud_Rate_Prescalar_define
#define BR_2								0
#define BR_4								(0b001 << 3)
#define BR_8								(0b010 << 3)
#define BR_16								(0b011 << 3)
#define BR_32								(0b100 << 3)
#define BR_64								(0b101 << 3)
#define BR_128								(0b110 << 3)
#define BR_256								(0b111 << 3)

// @ref NSS_define
//Hardware
#define NSS_Hard_Slave						0					//Hardware NSS management (SSM = 0)
#define NSS_Hard_Master_SS_output_enable	(1 << 2)			//NSS output enabled (SSM = 0, SSOE = 1)
#define NSS_Hard_Master_SS_output_disable	0					//NSS output disabled (SSM = 0, SSOE = 0)

//Software
#define NSS_Soft_reset						(1 << 9)			//Software slave management disabled
#define NSS_Soft_set						(1 << 9 | 1 << 8)	//Software slave management enabled &


//@ref SPI_IRQ_define
#define SPI_IRQ_Enable_NONE					(uint32_t)(0)		//No interrupt enabled
#define SPI_IRQ_Enable_TXEIE				(uint32_t)(1 << 7)	//TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.
#define SPI_IRQ_Enable_RXNEIE				(uint32_t)(1 << 6)	//RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is set.
#define SPI_IRQ_Enable_ERRIE				(uint32_t)(1 << 5)	//Error interrupt is enabled





enum SPI_Polling_mechanism{
	SPI_enable,
	SPI_disable
};
/*
 * =======================================================================================
 * 							APIs Supported by "MCAL GPIO DRIVER"
 * =======================================================================================
 */

void MCAL_SPI_INIT(SPI_TypeDef * SPIx , SPI_PinConfig_t * SPI_Config);
void MCAL_SPI_RESET(SPI_TypeDef * SPIx);
void MCAL_SPI_GPIO_SetPins(SPI_TypeDef * SPIx );
void MCAL_SPI_SendData(SPI_TypeDef * SPIx , uint16_t * PTxBuffer , enum SPI_Polling_mechanism  PollingEn );
void MCAL_SPI_ReceiveData(SPI_TypeDef * SPIx , uint16_t * PTxBuffer , enum SPI_Polling_mechanism  PollingEn );
void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx , uint16_t * PTxBuffer , enum SPI_Polling_mechanism  PollingEn );




#endif /* INC_STM32_F103C6_DRIVER_SPI_H_ */
