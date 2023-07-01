/*
 * stm32_f103c6_driver_USART.c
 *
 *  Created on: Jun 17, 2023
 *      Author: hassa
 */


#include "stm32_f103c6_driver_USART.h"
//-----------------------------
//variables
//-----------------------------
UART_PinConfig_t *G_UART_config = NULL;

//-----------------------------
//functios
//-----------------------------


//-----------------------------
//APIs
//-----------------------------
/**================================================================
 * @Fn				-MCAL_UART_Init
 * @brief 			-Initializes UART (supported synnch, only)
 * @param [in] 		-USARTx: where x can be (1,2,3 depending on device used)
 * @param [in] 		-UART_Config All UART cofig EXTTI config_t
 * @retval 			-none
 * Note				- none
 */

void MCAL_UART_Init(USART_TypeDef * USARTx , UART_PinConfig_t* UART_Config)
{
	G_UART_config = UART_Config;
	uint32_t pclk, BRR;


	//enable the clk for given USART periphirals
	if(USARTx == USART1)
		RCC_USART1_CLK_EN();
	else if(USARTx == USART2)
		RCC_USART2_CLK_EN();
	else if(USARTx == USART3)
		RCC_USART3_CLK_EN();

	//Enable USART Module
	// Bit 13 UE :USART enable
	USARTx ->CR1 |= 1<<13;

	//Enable USART TX/RX
	// Bit 3 TE & RE enable
	USARTx ->CR1 |= UART_Config->USART_Mode;

	//PAYload width
	//USARTx -> CR1 bi12 M
	USARTx ->CR1 |= UART_Config->Payload_length;

	//config paritty
	//USARTx -> CR1 bit 12 PCE bit9 PS
	USARTx ->CR1 |= UART_Config->Parity;

	//stop bits
	USARTx ->CR2 |= UART_Config->StopBits;

	//flow conttrol
	USARTx ->CR3 |= UART_Config->HWFlowCtl;


	// boaud rate register
	//PCLK1 for uart 2,3
	//PCLK2 for uart 1
	if(USARTx == USART1)
	{
		pclk = MCAL_RCC_GetPLCK2Freq();
	}
	else
	{
		pclk = MCAL_RCC_GetPLCK1Freq();
	}
	BRR = UART_BRR_Register(pclk , UART_Config->BaudRate);

	USARTx->BRR =BRR;

	//enable / disable IRQ
	//USART CR1
	if(UART_Config->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= (UART_Config->IRQ_Enable);

		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable;

		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_Enable;

		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_Enable;

	}
}

/**================================================================
 * @Fn				-MCAL_UART_Deinit
 * @brief 			-deInitializes UART (supported synnch, only)
 * @param [in] 		-USARTx: where x can be (1,2,3 depending on device used)
 * @param [in] 		-UART_Config All UART cofig EXTTI config_t
 * @retval 			-none
 * Note				- none
 */
void MCAL_UART_Deinit(USART_TypeDef * USARTx )
{
	if(USARTx == USART1)
	{
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_Disable;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_Disable;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_Disable;
	}
}


/**================================================================
 * @Fn				-MCAL_UART_SendData
 * @brief 			-send BUFFER on UART
 * @param [in] 		-USARTx: where x can be (1,2,3 depending on device used)
 * @param [in] 		-P_TXBuffer
 * @param [in] 		-PollingEN en/disable polling
 * @retval 			-none
 * Note				- none
 */
void MCAL_UART_SendData(USART_TypeDef * USARTx , uint16_t* P_TXBuffer , enum Polling_Mechanism PollingEN )
{
	//wait until TXE flag is set in the SR
	if(PollingEN == enable)
		while(!(USARTx->SR & 1<<7));

	if(G_UART_config ->Payload_length == UART_Payload_length_9B)
	{
		USARTx->DR = (*P_TXBuffer & (uint16_t)0x01FF);
	}
	else
	{
		USARTx->DR = (*P_TXBuffer & (uint8_t)0xFF);
	}
}


/**================================================================
 * @Fn				-MCAL_UART_WAIT_TC
 * @brief 			-Wait till transfere
 * @param [in] 		-USARTx: where x can be (1,2,3 depending on device used)
 * @retval 			-none
 * Note				- none
 */
void MCAL_UART_WAIT_TC(USART_TypeDef * USARTx )
{
	//wait ttill TC flag is set in the SR
	while (!(USARTx ->SR & 1<<6));
}


/**================================================================
 * @Fn				-MCAL_UART_ReceiveData
 * @brief 			-receive data from USART
 * @param [in] 		-USARTx: where x can be (1,2,3 depending on device used)
 * @param [in] 		-P_TXBuffer
 * @param [in] 		-PollingEN en/disable polling
 * @retval 			-none
 * Note				- none
 */
void MCAL_UART_ReceiveData(USART_TypeDef * USARTx , uint16_t* P_TXBuffer , enum Polling_Mechanism PollingEN )
{
	//wait until TXE flag is set in the SR
		if(PollingEN == enable)
			while(!(USARTx->SR & 1<<5));
		if(G_UART_config ->Payload_length == UART_Payload_length_9B)
		{
			if(G_UART_config ->Parity == UART_Parity_none)
			{
				*((uint16_t*)P_TXBuffer) = USARTx->DR;
			}

			else
			{
				*((uint16_t*)P_TXBuffer) = (USARTx->DR & (uint8_t)0xFF);
			}
		}
		else
		{
			if(G_UART_config ->Parity == UART_Parity_none)
			{
				*((uint16_t*)P_TXBuffer) = (USARTx->DR & (uint8_t)0xFF);
			}

			else
			{
				*((uint16_t*)P_TXBuffer) = (USARTx->DR & (uint8_t)0x7F);
			}
		}
}



/**================================================================
 * @Fn				-MCAL_UART_GPIO_Sett_Pins
 * @brief 			-intialize GPIIO pins
 * @param [in] 		-USARTx: where x can be (1,2,3 depending on device used)
 * @retval 			-none
 * Note				- none
 */
void MCAL_UART_GPIO_Sett_Pins(USART_TypeDef * USARTx )
{
	GPIO_PinConfig_t PinCFG;
	if(USARTx == USART1)
	{
		//PA9   	TX
		//PA10		RX
		//PA11   	CTS
		//PA12		RTS

		//PA9   	TX
		PinCFG.GPIO_PinNumber = GPIO_PIN_9;
		PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCFG);

		//PA10		RX
		PinCFG.GPIO_PinNumber = GPIO_PIN_10;
		PinCFG.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCFG);

		if(G_UART_config->HWFlowCtl == UART_HWFlowCtl_CTS || G_UART_config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS )
		{
			//PA11   	CTS
			PinCFG.GPIO_PinNumber = GPIO_PIN_11;
			PinCFG.GPIO_MODE = GPIO_MODE_AF_INPUT;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}
		if(G_UART_config->HWFlowCtl == UART_HWFlowCtl_CTS || G_UART_config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS )
		{
			//PA12   	RTS
			PinCFG.GPIO_PinNumber = GPIO_PIN_12;
			PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}
	}


	else if(USARTx == USART2)
	{
		//PA2   	TX
		//PA3		RX
		//PA0   	CTS
		//PA1		RTS
		//PA2   	TX
		PinCFG.GPIO_PinNumber = GPIO_PIN_2;
		PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCFG);
		//PA3		RX
		PinCFG.GPIO_PinNumber = GPIO_PIN_3;
		PinCFG.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCFG);

		if(G_UART_config->HWFlowCtl == UART_HWFlowCtl_CTS || G_UART_config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS )
		{
			//PA0   	CTS
			PinCFG.GPIO_PinNumber = GPIO_PIN_0;
			PinCFG.GPIO_MODE = GPIO_MODE_AF_INPUT;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}
		if(G_UART_config->HWFlowCtl == UART_HWFlowCtl_CTS || G_UART_config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS )
		{
			//PA1   	RTS
			PinCFG.GPIO_PinNumber = GPIO_PIN_1;
			PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCFG);
		}
	}

	else if(USARTx == USART2)
	{
		//PB10   	TX
		//PB11		RX
		//PB13   	CTS
		//PB14		RTS
		//PB10   	TX
		PinCFG.GPIO_PinNumber = GPIO_PIN_10;
		PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCFG);
		//PB11		RX
		PinCFG.GPIO_PinNumber = GPIO_PIN_11;
		PinCFG.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB, &PinCFG);
		if(G_UART_config->HWFlowCtl == UART_HWFlowCtl_CTS || G_UART_config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS )
		{
			//PB13   	CTS
			PinCFG.GPIO_PinNumber = GPIO_PIN_13;
			PinCFG.GPIO_MODE = GPIO_MODE_AF_INPUT;
			MCAL_GPIO_Init(GPIOB, &PinCFG);
		}
		if(G_UART_config->HWFlowCtl == UART_HWFlowCtl_CTS || G_UART_config->HWFlowCtl == UART_HWFlowCtl_RTS_CTS )
		{
			//PB14   	RTS
			PinCFG.GPIO_PinNumber = GPIO_PIN_14;
			PinCFG.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCFG.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCFG);
		}
	}
}


//ISR

void USART1_IRQHandler(void)
{
	G_UART_config->P_IRQ_CallBack();
}


void USART2_IRQHandler(void)
{
	G_UART_config->P_IRQ_CallBack();
}

void USART3_IRQHandler(void)
{
	G_UART_config->P_IRQ_CallBack();
}




















