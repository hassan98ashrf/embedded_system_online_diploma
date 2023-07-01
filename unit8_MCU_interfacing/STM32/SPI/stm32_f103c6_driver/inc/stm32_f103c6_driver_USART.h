/*
 * stm32_f103c6_driver_USART.h
 *
 *  Created on: Jun 17, 2023
 *      Author: hassa
 */

#ifndef INC_STM32_F103C6_DRIVER_USART_H_
#define INC_STM32_F103C6_DRIVER_USART_H_

#include "stm32_f103c6.h"
#include "stm32_f103c6_driver_GPIO.h"
#include "stm32_f103c6_driver_RCC.h"



//Config Structure
typedef struct
{
	uint8_t USART_Mode ; 		// Specifies TX/RX enable/dsiable.
								// This parameter must be set based on @ref UART_Mode_define

	uint32_t  BaudRate      ; 	// Specifies BoudRate for UART communication
								// This parameter can be a value of @ref UART_BoudRate_define

	uint8_t Payload_length;     // Specifies the number  of data bits transmited or received in a frame
								// This parameter can be a value of @ref UART_Payload_length_define

	uint8_t Parity;  		    // Specifies parity mode
								// This parameter can be a value of @ref UART_Parity_define

	uint8_t StopBits;  		    // Specifies number of stop bits
								// This parameter can be a value of @ref UART_StopBits_define

	uint8_t HWFlowCtl;  		// Specifies hardware enable or disable flow control
								// This parameter can be a value of @ref UART_HWFlowCtl_define

	uint8_t IRQ_Enable;  		// Specifies enable or disable UART IRQ TX/RX
								// This parameter can be a value of @ref UART_IRQ_Enable_define

	void(*P_IRQ_CallBack)(void);//set the C func which will be called once the IRQ happen
}UART_PinConfig_t;


//================================
//Macros Configuration References
//================================

//@ref USART_Mode_define
#define  UART_Mode_RX			(uint32_t)(1<<2)	//Bit 2 RE: Receiver enable
#define  UART_Mode_TX     	 	(uint32_t)(1<<3)  //Bit 3 TE: Transmitter enable
#define  UART_Mode_TX_RX		((uint32_t)(1<<2 | 1<<3))

// @ref BaudRate_define
#define UART_BaudRate_2400				2400
#define UART_BaudRate_9600				9600
#define UART_BaudRate_19200				19200
#define UART_BaudRate_57600				57600
#define UART_BaudRate_115200			115200
#define UART_BaudRate_230400			230400
#define UART_BaudRate_921600			921600
#define UART_BaudRate_2250000			2250000
#define UART_BaudRate_4500000			4500000


// @ref Payload_length_define
/*
 * Bit 12 M: Word length
This bit determines the word length. It is set or cleared by software.
0: 1 Start bit, 8 Data bits, n Stop bit
1: 1 Start bit, 9 Data bits, n Stop bit
*/
#define UART_Payload_length_8B	(uint32_t)(0)
#define UART_Payload_length_9B	(uint32_t)(1<<12)


//@ref Parity_define
/*
 * Bit 10 PCE: Parity control enable
This bit selects the hardware parity control (generation and detection). When the parity
control is enabled, the computed parity is inserted at the MSB position (9th bit if M=1; 8th bit
if M=0) and parity is checked on the received data. This bit is set and cleared by software.
Once it is set, PCE is active after the current byte (in reception and in transmission).
0: Parity control disabled
1: Parity control enabled

Bit 9 PS: Parity selection
This bit selects the odd or even parity when the parity generation/detection is enabled (PCE
bit set). It is set and cleared by software. The parity will be selected after the current byte.
0: Even parity
1: Odd parity
 * */
#define UART_Parity_none	(uint32_t)(0)
#define UART_Parity_EVEN	(uint32_t)(1<<10)
#define UART_Parity_ODD		(uint32_t)(1<<10 | 1<<9)


//@ref UART_StopBits_define
/*
 * Bits 13:12 STOP: STOP bits
These bits are used for programming the stop bits.
00: 1 Stop bit
01: 0.5 Stop bit
10: 2 Stop bits
11: 1.5 Stop bit
The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5.
 */
#define UART_StopBits_half 				(uint32_t)(1<<12)
#define UART_StopBits_one				(uint32_t)(0)
#define UART_StopBits_one_half			(uint32_t)(3<<12)
#define UART_StopBits_2					(uint32_t)(2<<12)


//@ref UART_HWFlowCtl_define
/*
 *Bit 9 CTSE: CTS enable
0: CTS hardware flow control disabled
1: CTS mode enabled, data is only transmitted when the CTS input is asserted (tied to 0).

Bit 8 RTSE: RTS enable
0: RTS hardware flow control disabled
1: RTS interrupt enabled, data is only requested when there is space in the receive buffer.
 */
#define UART_HWFlowCtl_NONE				(uint32_t)(0)
#define UART_HWFlowCtl_RTS				(uint32_t)(1<<8)
#define UART_HWFlowCtl_CTS				(uint32_t)(1<<9)
#define UART_HWFlowCtl_RTS_CTS			(uint32_t)(1<<8 |1<<9)


// @ref UART_IRQ_Enable_define
/*
 *
 */
#define UART_IRQ_Enable_NONE			(uint32_t)(0)
#define UART_IRQ_Enable_TXE				(uint32_t)(1<<7)
#define UART_IRQ_Enable_TC				(uint32_t)(1<<6)
#define UART_IRQ_Enable_RXNEIE			(uint32_t)(1<<5)
#define UART_IRQ_Enable_PE				(uint32_t)(1<<8)

//to ask user if he want send again and agine make
enum Polling_Mechanism
{
	enable,
	disable
};



//BAUDRATTE calculatiion
/*
 * USARTDIV = Fclk /(16*baudrate)
 * USARTDIV100 = uint32_t(100*fclk) / (16*baudrate) == (25*fclk) / (4*baudrate)
 * DIV_Mantissa_MUL100 = int part *100
 * DIV_Mantissa = int part
 * DIV_fraction = ((USARTDIV100 - DIV_Mantissa_MUL100) * 16) /100
 */

#define USARTDIV(_PCLK_ , _BAUD_)				(uint32_t)(_PCLK_/(16*_BAUD_))
#define USARTDIV100(_PCLK_ , _BAUD_)			(uint32_t)((25 * _PCLK_) / (4*_BAUD_))
#define Mantissa_MUL100(_PCLK_ , _BAUD_)		(uint32_t)(USARTDIV(_PCLK_ , _BAUD_) * 100)
#define Mantissa(_PCLK_ , _BAUD_)				(uint32_t)(USARTDIV(_PCLK_ , _BAUD_))
#define DIV_fraction(_PCLK_ , _BAUD_)			(uint32_t)(((USARTDIV100(_PCLK_ , _BAUD_) -Mantissa_MUL100(_PCLK_ , _BAUD_) ) *16)/100)
#define UART_BRR_Register(_PCLK_ , _BAUD_)		((Mantissa(_PCLK_ , _BAUD_)	)<<4) | ((DIV_fraction(_PCLK_ , _BAUD_)) & 0xF)

/*
 * =======================================================================================
 * 							APIs Supported by "MCAL GPIO DRIVER"
 * =======================================================================================
 */

void MCAL_UART_Init(USART_TypeDef * USARTx , UART_PinConfig_t *UART_Config);
void MCAL_UART_Deinit(USART_TypeDef * USARTx );

void MCAL_UART_GPIO_Sett_Pins(USART_TypeDef * USARTx );

void MCAL_UART_SendData(USART_TypeDef * USARTx , uint16_t* P_TXBuffer , enum Polling_Mechanism PollingEN );
void MCAL_UART_ReceiveData(USART_TypeDef * USARTx , uint16_t* P_TXBuffer , enum Polling_Mechanism PollingEN );

void MCAL_UART_WAIT_TC(USART_TypeDef * USARTx );



#endif /* INC_STM32_F103C6_DRIVER_USART_H_ */
