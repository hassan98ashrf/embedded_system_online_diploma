/*
 * RCC_PRIV.h
 *
 *  Created on: Nov 21, 2023
 *      Author: remaa
 */

#ifndef MCAL_GPIO_GPIO_PRIV_H_
#define MCAL_GPIO_GPIO_PRIV_H_




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

/*          REGISTERS IN EACH MODULE    */
typedef struct
{
    u32 MODER  ;
    u32 OTYPER  ;
    u32 OSPEEDR  ;
    u32 PUPDR  ;
    u32 IDR ;
    u32 ODR ;
    u32 BSRR  ;
    u32 LCKR ;
    u32 AFRL ;
    u32 AFRH ;
    u32 BRR ;

}volatile *const GPIO_Regs_t ;




/******************************************************************************
* Macros
*******************************************************************************/

		/*		REGISTER BOUNDARY ADDRESSES FOR PORT A, B AND C		*/
#define GPIOA_BASE_ADDRESS					0x48000000
#define GPIOB_BASE_ADDRESS					0x48000400
#define GPIOC_BASE_ADDRESS					0x48000800
#define GPIOD_BASE_ADDRESS					0x48000C00


/*			REGISTERS ADDRESSES FOR Port A 					*/

#define GPIOA  ((GPIO_Regs_t)GPIOA_BASE_ADDRESS)

/*			REGISTERS ADDRESSES FOR Port B 					*/
#define GPIOB  ((GPIO_Regs_t)GPIOB_BASE_ADDRESS)

/*			REGISTERS ADDRESSES FOR Port C 					*/

#define GPIOC  ((GPIO_Regs_t)GPIOC_BASE_ADDRESS)

/*			REGISTERS ADDRESSES FOR Port D					*/

#define GPIOD  ((GPIO_Regs_t)GPIOD_BASE_ADDRESS)



/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Module Variable Definitions
*******************************************************************************/




/******************************************************************************
* Private Function Prototypes
*******************************************************************************/



#endif /* MCAL_RCC_RCC_PRIV_H_ */
