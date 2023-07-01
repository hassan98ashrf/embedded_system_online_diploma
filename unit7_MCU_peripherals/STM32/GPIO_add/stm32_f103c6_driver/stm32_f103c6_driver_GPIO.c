/*
 * stm32_f103c6_driver_GPIO.c
 *
 *  Created on: Jun 1, 2023
 *      Author: hassa
 */
#include "stm32_f103c6_driver_GPIO.h"
#include "stm32_f103c6.h"
uint32_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
	    return 28;
		break;
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}


/**============================================================================
 * @fn			: MCAL_GPIO_Init
 * @brief		: initialize GPIOx and PINy to specific parameter in PinConfig
 * @param [in] 	: GPIOx(as x = {A,B,C,d,E})
 * @param [in]	: PinConfig contain the configuration of specific GPIOx
 * retval		: none
 * note 		: LQFP48 package there is no port E and part of ports c,d
 */
void MCAL_GPIO_Init(GPIO_TypeDef * GPIOx , GPIO_PinConfig_t * PinConfig)
{
	//Port configuration register low (GPIOx_CRL) from pin 0->7
	//Port configuration register high (GPIOx_CRH) from pin 8->15
	volatile uint32_t * ConfigRegister = NULL;
	uint8_t pin_config = 0;

	ConfigRegister = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL :&GPIOx->CRH;

	// clear CNFy[1:0]:(MODE[1:0])
	(*ConfigRegister) &= ~(0xF << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	//if pin is output
	if((PinConfig->GPIO_MODE == GPIO_MODE_OutPut_AF_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OutPut_AF_PP) || (PinConfig->GPIO_MODE == GPIO_MODE_OutPut_OD)|| (PinConfig->GPIO_MODE == GPIO_MODE_OutPut_PP))
	{
		//set CNFy[1:0]:(MODE[1:0])
		pin_config = ((((PinConfig->GPIO_MODE -4) <<2 ) | (PinConfig->GPIO_OutPut_Speed)) & 0x0F);

	}
	//if pin is input
	else
	{
		if( (PinConfig->GPIO_MODE == GPIO_MODE_InPut_Flo) || (PinConfig->GPIO_MODE == GPIO_MODE_Analog)  )
		{
			//set CNFy[1:0]:(MODE[1:0]00)
			pin_config = ((((PinConfig->GPIO_MODE ) << 2) | (0x00)) & 0x0F);
		}
		//consider as input float
		else if( PinConfig->GPIO_MODE == GPIO_MODE_AF_InPut)
		{
			//set CNFy[1:0]:(MODE[1:0]00)
			pin_config = ((((GPIO_MODE_InPut_Flo )<<2) | (0x00)) & 0x0F);
		}
		//pull up --pull down input
		else
		{
			pin_config = ((((GPIO_MODE_InPut_PD )<<2) | (0x00)) & 0x0F);
			if(PinConfig->GPIO_MODE == GPIO_MODE_InPut_PD)
			{
				//table 20 port bit config table PxODR 1
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else
			{
				//table 20 port bit config table PxODR 0
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}
	(*ConfigRegister) |=  ((pin_config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
}


/**============================================================================
 * @fn			: MCAL_GPIO_DeInit
 * @brief		: reset all GPIO registers
 * @param [in] 	: GPIOx(as x = {A,B,C,d,E})
 * retval		: none
 * note 		: none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef * GPIOx )
{
	//2ways ---- first
	/*
	GPIOx->BRR  = 0x00000000;
	GPIOx->BSRR = 0x00000000;
	GPIOx->CRH  = 0x44444444;
	GPIOx->CRL  = 0x44444444;
	//GPIOx->IDR  = (readonly);
	GPIOx->LCKR = 0x00000000;
	GPIOx->ODR  = 0x00000000;
	*/
	//second USE RESET CONTTRTOLLER
	//APB2 reset register  APB2RSTR
	//set and cleared by software
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |=(1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |=(1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |=(1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |=(1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR |=(1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}



}


/**============================================================================
 * @fn			: MCAL_GPIO_ReadPin
 * @brief		: Read specific pin
 * @param [in] 	: GPIOx(as x = {A,B,C,d,E})
 * @param [in] 	: PinNumber(1,2,3,..15) @ref GPIO_PINS_define
 * retval		: input pin value (based on @ref GPIO_PIN_state)
 * note 		: none
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef * GPIOx , uint16_t PinNumber)
{
	uint8_t BitStatus;
	if(((GPIOx->IDR)&PinNumber) != (uint32_t)GPIO_PIN_reset)
	{
		BitStatus = GPIO_PIN_set;
	}
	else
	{
		BitStatus = GPIO_PIN_reset;
	}
	return BitStatus;
}


/**============================================================================
 * @fn			: MCAL_GPIO_ReadPort
 * @brief		: Read specific port
 * @param [in] 	: GPIOx(as x = {A,B,C,d,E})
 * retval		: input port value
 * note 		: none
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx )
{
	uint16_t PortVal ;
	PortVal = (uint16_t)(GPIOx->IDR);
	return PortVal;
}


/**============================================================================
 * @fn			: MCAL_GPIO_WritePin
 * @brief		: Write at specific pin
 * @param [in] 	: GPIOx(as x = {A,B,C,d,E})
 * @param [in] 	: PinNumber(1,2,3,..15) @ref GPIO_PINS_define
 * @param [in] 	: value = pin value
 * retval		: none
 * note 		: none
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx , uint16_t PinNumber,uint8_t value)
{
	if(value != GPIO_PIN_reset)
	{
		//These bits are write-only and can be accessed in Word mode only.
		//0: No action on the corresponding ODRx bit
		//1: Set the corresponding ODRx bit
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else
	{
		//These bits are write-only and can be accessed in Word mode only.
		//0: No action on the corresponding ODRx bit
		//1: Reset the corresponding ODRx bit
		GPIOx->BRR =(uint32_t) PinNumber;
	}
}


/**============================================================================
 * @fn			: MCAL_GPIO_WritePin
 * @brief		: Write at specific port
 * @param [in] 	: GPIOx(as x = {A,B,C,d,E})
 * @param [in] 	: value = pin value
 * retval		: none
 * note 		: none
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx,uint32_t value )
{
	GPIOx->ODR = value;
}


/**============================================================================
 * @fn			: MCAL_GPIO_TogglePin
 * @brief		: Toggle specific pin
 * @param [in] 	: GPIOx(as x = {A,B,C,d,E})
 * @param [in] 	: PinNumber(1,2,3,..15) @ref GPIO_PINS_define
 * retval		: none
 * note 		: none
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef * GPIOx , uint16_t PinNumber)
{
	GPIOx->ODR ^= PinNumber;
}


/**============================================================================
 * @fn			: MCAL_GPIO_LockPin
 * @brief		: lock specific pin
 * @param [in] 	: GPIOx(as x = {A,B,C,d,E})
 * @param [in] 	: PinNumber(1,2,3,..15) @ref GPIO_PINS_define
 * retval		: ok if locked Error if it unlocke(@ref )
 * note 		: none
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOx , uint16_t PinNumber)
{
	//set LCKK
	volatile uint32_t temp = 1<<16;
	//set LCKY
	temp |= PinNumber;
	//write 1
	GPIOx->LCKR = temp;
	//write 0
	GPIOx->LCKR = PinNumber;
	//write 1
	GPIOx->LCKR = temp;
	//read  0
	temp = GPIOx->LCKR;
	//read  1
	if((uint32_t)(GPIOx->LCKR & 1<<16))
	{
		return GPIO_RETURN_LOCK_Enable;
	}
	else
	{
		return GPIO_RETURN_LOCK_Error;
	}

}









