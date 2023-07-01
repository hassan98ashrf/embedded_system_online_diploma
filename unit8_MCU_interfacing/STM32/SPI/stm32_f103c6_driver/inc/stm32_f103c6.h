/*
 * stm32_f103c6.h
 *
 *  Created on: Jun 16, 2023
 *      Author: hassa
 */

#ifndef INC_STM32_F103C6_H_
#define INC_STM32_F103C6_H_

//-----------------------------
//Includes
//-----------------------------

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define FLASH_Memory_BASE 							0x08000000UL
#define System_Memory_BASE 							0x1FFFF000UL
#define SRAM_Memory_BASE 							0x20000000UL
#define OPTION_Bytes_BASE							0x1FFFF800UL


#define Peripherals_BASE 							0x40000000UL

#define Cortex_M3_Internal_Peripherals_BASE 		0xE0000000UL

#define NVIC_BASE 									0xE000E100UL
#define NVIC_STIR_BASR 								0xE000EF00

#define NVIC_ISER0									*(volatile uint32_t *)(NVIC_BASE + 0x0)
#define NVIC_ISER1									*(volatile uint32_t *)(NVIC_BASE + 0x4)
#define NVIC_ISER2									*(volatile uint32_t *)(NVIC_BASE + 0x8)

#define NVIC_ICER0									*(volatile uint32_t *)(NVIC_BASE + 0x80)
#define NVIC_ICER1									*(volatile uint32_t *)(NVIC_BASE + 0x84)
#define NVIC_ICER2									*(volatile uint32_t *)(NVIC_BASE + 0x88)

#define NVIC_ISPR0									*((volatile uint32_t*)(NVIC_BASE + 0x100))
#define NVIC_ISPR1									*((volatile uint32_t*)(NVIC_BASE + 0x104))
#define NVIC_ISPR2									*((volatile uint32_t*)(NVIC_BASE + 0x108))

#define NVIC_ICPR0									*((volatile uint32_t*)(NVIC_BASE + 0x180))
#define NVIC_ICPR1									*((volatile uint32_t*)(NVIC_BASE + 0x184))
#define NVIC_ICPR2									*((volatile uint32_t*)(NVIC_BASE + 0x188))

#define NVIC_IABR0									*((volatile uint32_t*)(NVIC_BASE + 0x200))
#define NVIC_IABR1									*((volatile uint32_t*)(NVIC_BASE + 0x204))
#define NVIC_IABR2									*((volatile uint32_t*)(NVIC_BASE + 0x208))

#define NVIC_STIR									*((volatile uint32_t*)(NVIC_STIR_BASR + 0xE00))

//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------
//RCC
#define FSMC								0xA0000000UL
#define USB_OTG_FS							0x50000000UL
#define Ethernet							0x40028000UL
#define CRC									0x40023000UL
#define FLASH_Memory_Interface				0x40022000UL
#define RCC_BASE 							0x40021000UL
#define DMA2 								0x40020400UL
#define DMA1 								0x40020000UL
#define SDIO 								0x40018000UL

//#define RCC_BASE              				(Peripherals_BASE + 0x00021000UL)


//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------
#define TIM11_timer							0x40015400UL
#define TIM10_timer							0x40015000UL
#define TIM9_timer							0x40014C00UL
#define ADC3								0x40013C00UL
#define USART1_BASE							0x40013800UL
#define TIM8_timer							0x40013400UL
#define SPI1_BASE							0x40013000UL
#define TIM1_timer							0x40012C00UL
#define ADC2								0x40012800UL
#define ADC1								0x40012400UL

//GPIO
//A,B fully included in LQFP48 Package
#define GPIOA_BASE 							0x40010800UL
#define GPIOB_BASE 							0x40010C00UL


//C,D Partial  included in LQFP48 Package
#define GPIOC_BASE 							0x40011000UL
#define GPIOD_BASE 							0x40011400UL


//E not  included in LQFP48 Package
#define GPIOE_BASE 							0x40011800UL

//EXTI
#define EXTI_BASE 							0x40010400UL

//AFIO
#define AFIO_BASE 							0x40010000UL


//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------
#define USART1_BASE							0x40013800UL
#define USART2_BASE							0x40004400UL
#define USART3_BASE							0x40004800UL
#define SPI2_BASE							0x40003800UL
#define I2C2_BASE 							0x40005800UL
#define I2C1_BASE 							0x40005400UL
//======================================================================

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Peripheral register
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t  CRL ;
	volatile uint32_t  CRH ;
	volatile uint32_t  IDR ;
	volatile uint32_t  ODR ;
	volatile uint32_t  BSRR ;
	volatile uint32_t  BRR ;
	volatile uint32_t  LCKR ;
}GPIO_TypeDef;





//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t  CR ;
	volatile uint32_t  CFGR ;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	volatile uint32_t  IMR ;
	volatile uint32_t  EMR ;
	volatile uint32_t  RSTR ;
	volatile uint32_t  FTSR ;
	volatile uint32_t  SWIER ;
	volatile uint32_t  PR ;

}EXTI_TypeDef;


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t  EVCR ;
	volatile uint32_t  MAPR ;
	volatile uint32_t EXTICR[4]  ;
	 uint32_t  		   RESERVED0 ; //0x18
	volatile uint32_t  MAPR2 ; // 0x1c


}AFIO_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: UART
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct
{
	volatile uint32_t  SR ;
	volatile uint32_t  DR ;
	volatile uint32_t  BRR ;
	volatile uint32_t  CR1 ;
	volatile uint32_t  CR2 ;
	volatile uint32_t  CR3 ;
	volatile uint32_t  GTPR ;


}USART_TypeDef;



//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
}SPI_TypeDef;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: I2C
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
}I2C_TypeDef;

//==============================================================


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA      					((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB      					((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC      					((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD      					((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE      					((GPIO_TypeDef *)GPIOE_BASE)

#define RCC      					((RCC_TypeDef *)RCC_BASE)

#define EXTI      					((EXTI_TypeDef *)EXTI_BASE)

#define AFIO      					((AFIO_TypeDef *)AFIO_BASE)

#define USART1      				((USART_TypeDef *)USART1_BASE)
#define USART2      				((USART_TypeDef *)USART2_BASE)
#define USART3      				((USART_TypeDef *)USART3_BASE)

#define SPI1						((SPI_TypeDef*)SPI1_BASE)
#define SPI2						((SPI_TypeDef*)SPI2_BASE)
//==============================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1<<6)

#define AFIO_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1<<0)

#define RCC_USART1_CLK_EN()	(RCC->APB2ENR |= 1<<14)
#define RCC_USART2_CLK_EN()	(RCC->APB1ENR |= 1<<17)
#define RCC_USART3_CLK_EN()	(RCC->APB1ENR |= 1<<18)

#define RCC_SPI1_CLK_EN()   (RCC->APB2ENR |= 1<<12)
#define RCC_SPI2_CLK_EN()   (RCC->APB1ENR |= 1<<14)

#define RCC_I2C1_CLK_EN()   (RCC->APB2ENR |= 1<<21)
#define RCC_I2C2_CLK_EN()   (RCC->APB1ENR |= 1<<22)

//reset
#define RCC_USART1_RESET()	(RCC->APB2RSTR |= 1<<14)
#define RCC_USART2_RESET()	(RCC->APB1RSTR |= 1<<17)
#define RCC_USART3_RESET()	(RCC->APB1RSTR |= 1<<18)

#define RCC_SPI1_RESET()   (RCC->APB2RSTR |= 1<<12)
#define RCC_SPI2_RESET()   (RCC->APB1RSTR |= 1<<14)

#define RCC_I2C1_RESET()   (RCC->APB1RSTR |= 1<<21)
#define RCC_I2C2_RESET()   (RCC->APB1RSTR |= 1<<22)

//==============================================================

//-*-*-*-*-*-*-*-*-*-*-*-
//IVT
//-*-*-*-*-*-*-*-*-*-*-*
//EXtTI
#define		EXTI0_IRQ		6
#define		EXTI1_IRQ		7
#define		EXTI2_IRQ		8
#define		EXTI3_IRQ		9
#define		EXTI4_IRQ		10
#define		EXTI5_IRQ		23
#define		EXTI6_IRQ		23
#define		EXTI7_IRQ		23
#define		EXTI8_IRQ		23
#define		EXTI9_IRQ		23
#define		EXTI10_IRQ		40
#define		EXTI11_IRQ		40
#define		EXTI12_IRQ		40
#define		EXTI13_IRQ		40
#define		EXTI14_IRQ		40
#define		EXTI15_IRQ		40

//USART
#define		USART1_IRQ		37
#define		USART2_IRQ		38
#define		USART3_IRQ		39

//SPI
#define SPI1_IRQ		35
#define SPI2_IRQ		36

//I2C
#define I2C1_EV_IRQ		31
#define I2C1_ER_IRQ		32
#define I2C2_EV_IRQ		33
#define I2C2_ER_IRQ		34


//-*-*-*-*-*-*-*-*-*-*-*-
//NVIC ENABLE DIISABLE MACROS
//-*-*-*-*-*-*-*-*-*-*-*
#define NVIC_IRQ6_EXTI0_Enable			(NVIC_ISER0 |=(1<<6))
#define NVIC_IRQ7_EXTI1_Enable			(NVIC_ISER0 |=(1<<7))
#define NVIC_IRQ8_EXTI2_Enable			(NVIC_ISER0 |=(1<<8))
#define NVIC_IRQ9_EXTI3_Enable			(NVIC_ISER0 |=(1<<9))
#define NVIC_IRQ10_EXTI4_Enable			(NVIC_ISER0 |=(1<<10))
#define NVIC_IRQ23_EXTI5_9_Enable		(NVIC_ISER0 |=(1<<23))
#define NVIC_IRQ40_EXTI10_15_Enable		(NVIC_ISER1 |=(1<<8))//40-32=8

#define NVIC_IRQ6_EXTI0_Disable			(NVIC_ICER0 |=(1<<6))
#define NVIC_IRQ7_EXTI1_Disable			(NVIC_ICER0 |=(1<<7))
#define NVIC_IRQ8_EXTI2_Disable			(NVIC_ICER0 |=(1<<8))
#define NVIC_IRQ9_EXTI3_Disable			(NVIC_ICER0 |=(1<<9))
#define NVIC_IRQ10_EXTI4_Disable		(NVIC_ICER0 |=(1<<10))
#define NVIC_IRQ23_EXTI5_9_Disable		(NVIC_ICER0 |=(1<<23))
#define NVIC_IRQ40_EXTI10_15_Disable	(NVIC_ICER1 |=(1<<8))//40-32=8


//USART
/*
#define NVIC_IRQ37_USART1_Enable		(NVIC_ISER1 |=(1<<(USART1_IRQ -32))  //note +32 ICER1  USART1_IRQ -32
#define NVIC_IRQ38_USART2_Enable		(NVIC_ISER1 |=(1<<(USART2_IRQ -32))
#define NVIC_IRQ39_USART3_Enable		(NVIC_ISER1 |=(1<<(USART3_IRQ -32))

#define NVIC_IRQ37_USART1_Disable		(NVIC_ISER1 |=(1<<(USART1_IRQ -32))  //note +32 ICER1  USART1_IRQ -32
#define NVIC_IRQ38_USART2_Disable		(NVIC_ISER1 |=(1<<(USART2_IRQ -32))
#define NVIC_IRQ39_USART3_Disable		(NVIC_ISER1 |=(1<<(USART3_IRQ -32))
*/
#define	NVIC_IRQ37_USART1_Enable		(NVIC_ISER1 |= 1<<5)//37-32=5
#define	NVIC_IRQ38_USART2_Enable		(NVIC_ISER1 |= 1<<6)//38-32=6
#define	NVIC_IRQ39_USART3_Enable		(NVIC_ISER1 |= 1<<7)//39-32=7

#define	NVIC_IRQ37_USART1_Disable		(NVIC_ICER1 |= 1<<5)//37-32=5
#define	NVIC_IRQ38_USART2_Disable		(NVIC_ICER1 |= 1<<6)//38-32=6
#define	NVIC_IRQ39_USART3_Disable		(NVIC_ICER1 |= 1<<7)//39-32=7

//SPI
#define NVIC_IRQ35_SPI1_Enable		(NVIC_ISER1 |= 1 << 3)  //35-32
#define NVIC_IRQ36_SPI2_Enable		(NVIC_ISER1 |= 1 << 4)  //36-32

#define NVIC_IRQ35_SPI1_Disable		(NVIC_ICER1 |= 1 << 3)	//35-32
#define NVIC_IRQ36_SPI2_Disable		(NVIC_ICER1 |= 1 << 4)	//36-32


#endif /* INC_STM32_F103C6_H_ */
