/*
 * RCC_IF.h
 *
 *  Created on: Nov 20, 2023
 *      Author: remaa
 */

#ifndef MCAL_RCC_RCC_IF_H_
#define MCAL_RCC_RCC_IF_H_




/******************************************************************************
* Includes
*******************************************************************************/
#include "UTILIS.h"
#include "STD_TYPES.h"




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
    RCC_AHB ,
    RCC_APB1 ,
    RCC_APB2
}Bus_t ;



/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * @brief This function is used to enable the clock for the chosen perpheral
 * @param Copy_BusId is the Bus type
 * @param Copy_u8BperId is the peripheral number
 */
void RCC_voidEnableClock(Bus_t Copy_BusId, u8 Copy_u8BperId) ;

/**
 * @brief This function is used to disable the clock for the chosen perpheral
 * @param Copy_BusId is the Bus type
 * @param Copy_u8BperId is the peripheral number
 */
void RCC_voidDisableClock(Bus_t Copy_BusId, u8 Copy_u8BperId) ;


/**
 * @brief This Function is used to init CPU Clock / AHB Bus Clock / ABP1/2 Clock
 */
void RCC_voidInitSysClocks(void);




#endif /* MCAL_RCC_RCC_IF_H_ */
