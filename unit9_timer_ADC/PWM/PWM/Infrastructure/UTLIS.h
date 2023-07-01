/*
 * UTLIS.h
 *
 * Created: 7/1/2023 5:31:48 PM
 *  Author: hassa
 */ 


#ifndef UTLIS_H_
#define UTLIS_H_



//UTILITS
#define SET_BIT(PORT, BIT)			(PORT |=  (1<<BIT))
#define CLEAR_BIT(PORT, BIT)		(PORT &= ~(1<<BIT))
#define TOGGLE_BIT(PORT, BIT)		(PORT ^=  (1<<BIT))
#define READ_BIT(PORT, BIT)			((PORT>>BIT)&(0x01))




#endif /* UTLIS_H_ */