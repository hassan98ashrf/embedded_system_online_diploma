/*
 * stm32_f103c6_driver_RCC.h
 *
 *  Created on: Jun 17, 2023
 *      Author: hassa
 */

#ifndef INC_STM32_F103C6_DRIVER_RCC_H_
#define INC_STM32_F103C6_DRIVER_RCC_H_

//Includes
#include "stm32_f103c6.h"
#include "stm32_f103c6_driver_GPIO.h"

//assume multiplixor take from onside osclaitor 8MHz
#define HSE_Clock			(uint32_t)16000000   //16MHz
#define HSI_RC_clk			(uint32_t)8000000	//8MHz


uint32_t MCAL_RCC_GetSYS_CLCKFreq(void);
uint32_t MCAL_RCC_GetHCKFreq(void);
uint32_t MCAL_RCC_GetPLCK1Freq(void);
uint32_t MCAL_RCC_GetPLCK2Freq(void);



#endif /* INC_STM32_F103C6_DRIVER_RCC_H_ */
