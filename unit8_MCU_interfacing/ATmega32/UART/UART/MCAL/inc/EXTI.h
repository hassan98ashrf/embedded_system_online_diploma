/*
 * EXTI.h
 *
 * Created: 6/26/2023 11:42:24 AM
 *  Author: hassa
 */ 


#ifndef EXTI_H_
#define EXTI_H_


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//============== Includes ==============
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#include "Atmega32.h"
#include "GPIO.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== Type Definitions ==========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

typedef struct  {
	
	unsigned char INT_NUM;			//Which interrupt u need to use
									//Specified @ref INT_NUM_define
	
	
	unsigned char EXTI_State;		//Enable or disable the external interrupt 
									//Specified @ref EXTI_State_define
									
									
	unsigned char Trigger_Case;		//Defines the trigger case if the interrupt Rising or falling or low level 
									//Specified @ref Trigger_Case_define 
									//Note : If low level interrupt is selected, the low level must be held until the
									//completion of the currently executing instruction to generate an interrupt.
									
									//Note : INT0 & INT1 have the same configurations (low level , rising , falling) BUT
									//INT2 has different configurations (rising , falling)ONLY  
									//To use INT0 or INT1 use macros with suffx INT0_1
									//To use INT2 use macros with suffx INT2 
									
	
	void(*P_INT_CallBack)(void);	//Interrupt handler function
		
}EXTI_CFG_t;



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//== Macros Configuration References ==
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//@ref Trigger_Case_define
#define Trigger_Case_LowLevel_INT0_1	0b00
#define Trigger_Case_FallingEdge_INT0_1	0b10
#define Trigger_Case_RisingEdge_INT0_1	0b11
#define Trigger_Case_LogicChange_INT0_1	0b01
#define Trigger_Case_FalingEdge_INT2	0		
#define Trigger_Case_RisingEdge_INT2	1


//@ref EXTI_State_define
#define EXTI_State_Enable				1
#define EXTI_State_Disable				0


//@ref INT_NUM_define
#define INT_NUM_0						0
#define INT_NUM_1						1
#define INT_NUM_2						2



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== APIs Supported by "MCAL UART DRIVER" ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

/**================================================================
* @Fn - MCAL_EXTI_INIT
* @brief - Initialize the external interrupt
* @param[in] - External interrupt configuration 
* @param[out] - GPIO pin in the specific port (in the last parameter)
*               takes values @ref GPIO_PinNumber  @ref GPIO_MODE  @ref GPIO_FREQ
*/

void MCAL_EXTI_INIT( EXTI_CFG_t* EXTI_CFG);



/**================================================================
* @Fn - MCAL_EXTI_RESET
* @brief - Initialize the portx
* @param[in] - GPIO port
* @param[out] - GPIO pin in the specific port (in the last parameter)
*               takes values @ref GPIO_PinNumber  @ref GPIO_MODE  @ref GPIO_FREQ
*/
void MCAL_EXTI_RESET(unsigned char INT_NUM);



/**================================================================
* @Fn - MCAL_GPIO_INIT
* @brief - Initialize the portx
* @param[in] - GPIO port
* @param[out] - GPIO pin in the specific port (in the last parameter)
*               takes values @ref GPIO_PinNumber  @ref GPIO_MODE  @ref GPIO_FREQ
*/
void MCAL_EXTI_GPIO_CFG(unsigned char INT_NUM);




#endif /* EXTI_H_ */