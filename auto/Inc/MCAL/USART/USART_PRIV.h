/*
 * USART_PRIV.h
 *
 *  Created on: Nov 21, 2023
 *      Author: remaa
 */

#ifndef MCAL_USART_USART_PRIV_H_
#define MCAL_USART_USART_PRIV_H_



/******************************************************************************
* Includes
*******************************************************************************/




/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/




/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Typedefs
*******************************************************************************/

typedef struct{

	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 BRR;
	volatile u32 GTPR;
	volatile u32 RTOR;
	volatile u32 RQR;
	volatile u32 ISR;
	volatile u32 ICR;
	volatile u32 RDR;
	volatile u32 TDR;
}USART_Type;


/******************************************************************************
* Macros
*******************************************************************************/




#define USART1 ( ( volatile USART_Type* ) 0x40013800 )	//USART1 APB2

#define USART2 ( ( volatile USART_Type* ) 0x40004400  ) //USART2	APB1

#define USART3 ( ( volatile USART_Type* ) 0x40004800 )	// APB1


#define TXE	7
#define TXC	6
#define RXNE	5

/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Module Variable Definitions
*******************************************************************************/




/******************************************************************************
* Private Function Prototypes
*******************************************************************************/


void USART_voidBuadRateCalc(u32 BuadRate , u32 PClock , u32 *BRR_Reg);
void USART1_EXTI25_IRQHandler(void);
void USART2_EXTI26_IRQHandler(void);
void USART3_EXTI28_IRQHandler(void);



#endif /* MCAL_USART_USART_PRIV_H_ */
