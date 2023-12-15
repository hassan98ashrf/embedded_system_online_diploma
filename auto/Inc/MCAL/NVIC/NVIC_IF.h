/*
 * RCC_IF.h
 *
 *  Created on: Nov 20, 2023
 *      Author: remaa
 */

#ifndef MCAL_NVIC_NVIC_IF_H_
#define MCAL_NVIC_NVIC_IF_H_



#include "STD_TYPES.h"

void nvic_enableInterrupt(u8 intId);
void nvic_disableInterrupt(u8 intId);

void nvic_setPendingFlag(u8 intId);
void nvic_clearPendingFlag(u8 intId);

boolean nvic_readActiveFlag(u8 intId);



#endif /* MCAL_RCC_RCC_IF_H_ */
