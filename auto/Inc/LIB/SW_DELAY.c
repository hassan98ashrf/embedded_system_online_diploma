/*
 * SW_DELAY.c
 *
 *  Created on: Nov 20, 2023
 *      Author: remaa
 */


#include <LIB/STD_TYPES.h>
#include "RCC_IF.h"

#if DELAY_BASED_ON == STK_DELAY
#include "STK_IF.h"
#endif
#include "SW_Delay.h"

void delay_init(void)
{
#if DELAY_BASED_ON == STK_DELAY
    STK_voidInit();
#endif

}
void delay_us(u32 microseconds)
{
    // Calculate the number of loops required for the delay
	//u32 loops = (8 * microseconds) / 3; // 8 MHz sysclk
	u32 loops = (8 * microseconds) / 10;
    for (volatile u32 i = 0; i < loops; ++i)
    {
        __asm("NOP");
    }
}

void delay_ms(u32 milliseconds)
{
    // Calculate the number of loops required for the delay
	//u32 loops = (8000 * milliseconds) / 1000; // 8 MHz sysclk
	u32 loops = (8000 * milliseconds) / 10;
    for (volatile u32 i = 0; i < loops; ++i)
    {
        __asm("NOP");
    }
}
