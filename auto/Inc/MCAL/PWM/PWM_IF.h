/*
 * RCC_IF.h
 *
 *  Created on: Nov 20, 2023
 *      Author: remaa
 */

#ifndef MCAL_PWM_PWM_IF_H_
#define MCAL_PWM_PWM_IF_H_



/******************************************************************************
* Includes
*******************************************************************************/
#include "UTILIS.h"



/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/




/******************************************************************************
* Configuration Constants
*******************************************************************************/




/******************************************************************************
* Macros
*******************************************************************************/




/******************************************************************************
* Typedefs
*******************************************************************************/


typedef enum
{
    DIR_UPCOUNTING = 0 ,
    DIR_DOWNCOUNTING = (1 << 4)

}TIMxDir_t;

typedef enum
{
    PWM_NOT_USED = 0 ,
    PWM_MODE_1 = (0b110) ,
    PWM_MODE_2 = (0b111)

}PWM_Mode_t;


typedef enum
{
    CHANNEL_NOT_USED = 0 ,
    CHANNEL_MODE_PWM
}ChannelConfig_t ;





typedef struct
{
    TIMx_t  Timerx  ;
    TIMxDir_t   DIR_xCOUNTING ;
    u32         TIMx_u32TopValue ; // For Tim3 u16
    PWM_Mode_t  TIMx_PWM_Mode_CHx[4];   // For Each Channel
}PWM_Config_t;


/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * @brief This Function is used to init the PWM Module
 *
 * @param copy_TIMx the TIMx Number @ref TIMx enum
 */
void PWM_voidInit(PWM_Config_t * p_userConfig);


/**
 * @brief This Function is used to Set duty cycle on selected pin
 *
 * @param copy_u16DutyCycle Duty Cycle
 */
void PWM_voidSetDutyCycle(PWM_Config_t * p_userConfig , u16 copy_u16DutyCycle , Channel_ID_t CHANNEL_x);



#endif /* MCAL_RCC_RCC_IF_H_ */
