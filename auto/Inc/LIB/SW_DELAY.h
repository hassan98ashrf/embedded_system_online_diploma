/*
 * SW_DELAY.h
 *
 *  Created on: Nov 20, 2023
 *      Author: remaa
 */

#ifndef LIB_SW_DELAY_H_
#define LIB_SW_DELAY_H_

#define SW_DELAY 		1
#define STK_DELAY		2

#define DELAY_BASED_ON    STK_DELAY


void delay_init(void);
void delay_us(u32 microseconds);
void delay_ms(u32 milliseconds);

#endif /* LIB_SW_DELAY_H_ */
