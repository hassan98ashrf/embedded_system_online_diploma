/*
 * stm32_f103c6_driver_EXTI.c
 *
 *  Created on: Jun 16, 2023
 *      Author: hassa
 */


#include "stm32_f103c6_driver_EXTI.h"
#include "stm32_f103c6.h"
#include "stm32_f103c6_driver_GPIO.h"
//================================
//GENERIC variables
//================================
void (*GP_IRQ_CallBack[15])(void);


//================================
//GENERIC macros
//================================
#define AFIO_GPIO_EXTI_Mapping(x)	( (x==GPIOA)?0:\
									  (x==GPIOB)?1:\
									  (x==GPIOC)?2:\
									  (x==GPIOD)?3:0)



//================================
//GENERIC FUNCTIONS
//================================
void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable;
		//break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable;
		//break;
	}
}

void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable;
	//	break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable;
		//break;
	}
}





void Update_EXTI(EXTI_PinConfig_t *EXTI_Config)
{
	//1- config GPIO to be AF input
	GPIO_PinConfig_t PinCfg;
	//update GPIO pin tto be Floating inputtt
	PinCfg.GPIO_PinNumber =EXTI_Config-> EXTI_PIN.GPIO_PIN;
	PinCfg.GPIO_MODE =GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_Config ->EXTI_PIN .GPIO_Port,&PinCfg);

	//2- update AFIO to route bettwwn EXTI liine with ports ABCD
	uint8_t AFIO_EXTICR_index= EXTI_Config -> EXTI_PIN.EIT_InputLineNumber /4;
	uint8_t AFIO_EXTICR_Position = (EXTI_Config-> EXTI_PIN.EIT_InputLineNumber % 4)*4;

	//clear 4 bit

	AFIO-> EXTICR[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_Position);
	AFIO-> EXTICR[AFIO_EXTICR_index] |=  ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port)&0xF)<< AFIO_EXTICR_Position);


	//3- update rising or falling register
	EXTI->RSTR &= ~(1<<EXTI_Config->EXTI_PIN.EIT_InputLineNumber);
	EXTI->FTSR &= ~(1<<EXTI_Config->EXTI_PIN.EIT_InputLineNumber);

	if(EXTI_Config->Trigger_case == EXIT_Trigger_RISING)
	{
		EXTI->RSTR |= (1<<EXTI_Config->EXTI_PIN.EIT_InputLineNumber);

	}else if(EXTI_Config->Trigger_case == EXIT_Trigger_FALLING)
	{
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EIT_InputLineNumber);
	}else if(EXTI_Config->Trigger_case == EXIT_Trigger_RISING_FALLING)
	{
		EXTI->RSTR |= (1<<EXTI_Config->EXTI_PIN.EIT_InputLineNumber);
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EIT_InputLineNumber);
	}

	//4- update IRQ handlling callback

	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.EIT_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;


	//5- enable disable IRQ&NVIC
	if(EXTI_Config->IRQ_EN == EXIT_IRQ_Enable)
	{
		EXTI->IMR |=(1<<EXTI_Config->EXTI_PIN.EIT_InputLineNumber);
		Enable_NVIC(EXTI_Config->EXTI_PIN.EIT_InputLineNumber);
	}else
	{
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_PIN.EIT_InputLineNumber);
		Disable_NVIC(EXTI_Config->EXTI_PIN.EIT_InputLineNumber);

	}

}


/**================================================================
 * @Fn				-MCAL_EXTI_GPIO_DeInit
 * @brief 			-reset exti register and nvic
 * @retval 			-none
 * Note				-noe
 */
void MCAL_EXTI_GPIO_DeInit(void)
{
	EXTI->EMR	 = 0x00000000;
	EXTI->FTSR	 = 0x00000000;
	EXTI->IMR 	 = 0x00000000;
	EXTI->RSTR 	 = 0x00000000;
	EXTI->SWIER  = 0x00000000;
	//clear by right 1
	EXTI->PR 	 = 0xFFFFFFFF;

	//DISALE EXTI FROM  NVIC
	NVIC_IRQ6_EXTI0_Disable		;
	NVIC_IRQ7_EXTI1_Disable		;
	NVIC_IRQ8_EXTI2_Disable		;
	NVIC_IRQ9_EXTI3_Disable		;
	NVIC_IRQ10_EXTI4_Disable	;
	NVIC_IRQ23_EXTI5_9_Disable	;
	NVIC_IRQ40_EXTI10_15_Disable;

}



/**================================================================
 * @Fn				-MCAL_GPIO_Init
 * @brief 			-initialize EXTI from specific GPIO and mask/trigger
 * @param [in] 		-EXTI config set b @ref EXTI_define,EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 			-none
 * Note				-this function at start programming
 */
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}

/**================================================================
 * @Fn				-MCAL_EXTI_GPIO_Update
 * @brief 			-initialize EXTI from specific GPIO and mask/trigger
 * @param [in] 		-EXTI config set b @ref EXTI_define,EXTI_Trigger_define and EXTI_IRQ_define
 * @retval 			-none
 * Note				-this function at run time programming
 */
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);

}

//================================
//ISR FUNCTIONS
//================================


void EXTI0_IRQHandler(void)
{
	//clean by write 1
	EXTI->PR |= 1<<0;
	GP_IRQ_CallBack[0]();;
}

void EXTI1_IRQHandler(void)
{
	//clean by write 1
	EXTI->PR |= 1<<1;
	GP_IRQ_CallBack[1]();;
}
void EXTI2_IRQHandler(void)
{
	//clean by write 1
	EXTI->PR |= 1<<2;
	GP_IRQ_CallBack[2]();;
}
void EXTI3_IRQHandler(void)
{
	//clean by write 1
	EXTI->PR |= 1<<3;
	GP_IRQ_CallBack[3]();;
}
void EXTI4_IRQHandler(void)
{
	//clean by write 1
	EXTI->PR |= 1<<4;
	GP_IRQ_CallBack[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<<5){EXTI->PR |= 1<<5	;	GP_IRQ_CallBack[5]();	}
	if(EXTI->PR & 1<<6){EXTI->PR |= 1<<6	;	GP_IRQ_CallBack[6]();	}
	if(EXTI->PR & 1<<7){EXTI->PR |= 1<<7	;	GP_IRQ_CallBack[7]();	}
	if(EXTI->PR & 1<<8){EXTI->PR |= 1<<8	;	GP_IRQ_CallBack[8]();	}
	if(EXTI->PR & 1<<9){EXTI->PR |= 1<<9	;	GP_IRQ_CallBack[9]();	}

}


void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & 1<<10){EXTI->PR |= 1<<10	;	GP_IRQ_CallBack[10]();	}
	if(EXTI->PR & 1<<11){EXTI->PR |= 1<<11	;	GP_IRQ_CallBack[11]();	}
	if(EXTI->PR & 1<<12){EXTI->PR |= 1<<12	;	GP_IRQ_CallBack[12]();	}
	if(EXTI->PR & 1<<13){EXTI->PR |= 1<<13	;	GP_IRQ_CallBack[13]();	}
	if(EXTI->PR & 1<<14){EXTI->PR |= 1<<14	;	GP_IRQ_CallBack[14]();	}
	if(EXTI->PR & 1<<15){EXTI->PR |= 1<<15	;	GP_IRQ_CallBack[15]();	}

}



