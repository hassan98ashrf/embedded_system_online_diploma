/*
 * CTRL_CAR.c
 *
 *  Created on: Nov 21, 2023
 *      Author: remaa
 */


/******************************************************************************
 * Includes
 *******************************************************************************/

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/UTILIS.h"
#include "../MCAL/RCC/RCC_IF.h"
#include "../MCAL/GPIO/GPIO_IF.h"
#include "../MCAL/PWM/PWM_IF.h"
#include "DC.h"
#include "CTRL_CAR.h"


/******************************************************************************
 * Module Private Vars
 *******************************************************************************/
static DCMotor_Cfg _Global_Back_Motor ;
static DCMotor_Cfg _Global_Front_Motor ;




/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/

#define CENTER_OF_STEERING	90

#define MOTOR_ZERO_SPEED       (u16)0
#define FRONT_MOTOR_SPEED	   (u16)(180)




/******************************************************************************
 * Typedefs
 *******************************************************************************/




/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/




/******************************************************************************
 * Function Prototypes
 *******************************************************************************/




/******************************************************************************
 * Function Definitions
 *******************************************************************************/
void C2VCONTROL_voidInit(void)
{
	//_Global_Back_Motor
	_Global_Back_Motor.Timerx      = Timer3 ;
	_Global_Back_Motor.CHANNEL_x   = CHANNEL_1 ;
	_Global_Back_Motor.CW_Port     = C2_MOT1_CW_PORT ;
	_Global_Back_Motor.CW_Pin      = C2_MOT1_CW_PIN  ;
	_Global_Back_Motor.CCW_Port    = C2_MOT1_CCW_PORT ;
	_Global_Back_Motor.CCW_Pin     = C2_MOT1_CCW_PIN  ;

	//_Global_Front_Motor
	_Global_Front_Motor.Timerx      = Timer3 ;
	_Global_Front_Motor.CHANNEL_x   = CHANNEL_2 ;
	_Global_Front_Motor.CW_Port     = C2_MOT2_CW_PORT ;
	_Global_Front_Motor.CW_Pin      = C2_MOT2_CW_PIN  ;
	_Global_Front_Motor.CCW_Port    = C2_MOT2_CCW_PORT ;
	_Global_Front_Motor.CCW_Pin     = C2_MOT2_CCW_PIN  ;

	// Inits
	DCMOTOR_voidInit(&_Global_Back_Motor); 	 // For Right Motor
	DCMOTOR_voidInit(&_Global_Front_Motor);  // For Left Motor


	// LEDs As Output
	GPIO_voidSetPinDirection(BACK_RIGHT_LED_PORT, BACK_RIGHT_LED_PIN, GPIO_OUTPUT_LOW_SPD_PUSH_PULL);
	GPIO_voidSetPinValue(BACK_RIGHT_LED_PORT, BACK_RIGHT_LED_PIN, LOW);
	GPIO_voidSetPinDirection(BACK_LEFT_LED_PORT, BACK_LEFT_LED_PIN, GPIO_OUTPUT_LOW_SPD_PUSH_PULL);
	GPIO_voidSetPinValue(BACK_LEFT_LED_PORT, BACK_LEFT_LED_PIN, LOW);
}

void C2VCONTROL_voidChangeDirection(VCLE_Dir_t VCLE_x , u16 copy_u16VcleSpeed)
{
	switch (VCLE_x)
	{
	case VCLE_FWD:
		/* code */
		//FRONT MOTOR
		// DCMOTOR_voidSetSpeed(& 	_Global_Front_Motor, MOTOR_ZERO_SPEED);    // Already Stopped
		DCMOTOR_voidSetDirection(& 	_Global_Front_Motor, MTR_STOP);
		//BACK MOTOR
		DCMOTOR_voidSetDirection(& 	_Global_Back_Motor, MTR_ROTATE_CW);
		DCMOTOR_voidSetSpeed(& 	_Global_Back_Motor, copy_u16VcleSpeed);
		break;

	case VCLE_BWD:
		/* code */
		//FRONT MOTOR
		// DCMOTOR_voidSetSpeed(& 	_Global_Front_Motor, MOTOR_ZERO_SPEED);	// Already Stopped
		DCMOTOR_voidSetDirection(& 	_Global_Front_Motor, MTR_STOP);
		//BACK MOTOR
		DCMOTOR_voidSetDirection(& 	_Global_Back_Motor, MTR_ROTATE_CCW);
		DCMOTOR_voidSetSpeed(& 	_Global_Back_Motor, copy_u16VcleSpeed);
		break;


	case VCLE_RIGHT_FWD:
		/* code */
		//FRONT MOTOR
		DCMOTOR_voidSetDirection(& 	_Global_Front_Motor, MTR_ROTATE_CW);
		DCMOTOR_voidSetSpeed(& 	_Global_Front_Motor, FRONT_MOTOR_SPEED);
		//BACK MOTOR
		DCMOTOR_voidSetDirection(& 	_Global_Back_Motor, MTR_ROTATE_CW);
		DCMOTOR_voidSetSpeed(& 	_Global_Back_Motor, copy_u16VcleSpeed);

		// LEDs
		GPIO_voidSetPinValue(BACK_RIGHT_LED_PORT, BACK_RIGHT_LED_PIN, HIGH);
		GPIO_voidSetPinValue(BACK_LEFT_LED_PORT, BACK_LEFT_LED_PIN, LOW);

		break;

	case VCLE_RIGHT_BWD:
		/* code */
		//FRONT MOTOR
		DCMOTOR_voidSetDirection(& 	_Global_Front_Motor, MTR_ROTATE_CW);
		DCMOTOR_voidSetSpeed(& 	_Global_Front_Motor, FRONT_MOTOR_SPEED);
		//BACK MOTOR
		DCMOTOR_voidSetDirection(& 	_Global_Back_Motor, MTR_ROTATE_CCW);
		DCMOTOR_voidSetSpeed(& 	_Global_Back_Motor, copy_u16VcleSpeed);

		// LEDs
		GPIO_voidSetPinValue(BACK_RIGHT_LED_PORT, BACK_RIGHT_LED_PIN, HIGH);
		GPIO_voidSetPinValue(BACK_LEFT_LED_PORT, BACK_LEFT_LED_PIN, LOW);
		break;

	case VCLE_LEFT_BWD:
		/* code */
		//FRONT MOTOR
		DCMOTOR_voidSetDirection(& 	_Global_Front_Motor, MTR_ROTATE_CCW);
		DCMOTOR_voidSetSpeed(& 	_Global_Front_Motor, FRONT_MOTOR_SPEED);
		//BACK MOTOR
		DCMOTOR_voidSetDirection(& 	_Global_Back_Motor, MTR_ROTATE_CCW);
		DCMOTOR_voidSetSpeed(& 	_Global_Back_Motor, copy_u16VcleSpeed);

		// LEDs
		GPIO_voidSetPinValue(BACK_RIGHT_LED_PORT, BACK_RIGHT_LED_PIN, LOW);
		GPIO_voidSetPinValue(BACK_LEFT_LED_PORT, BACK_LEFT_LED_PIN, HIGH);

		break;

	case  VCLE_LEFT_FWD :
		/* code */
		//FRONT MOTOR
		DCMOTOR_voidSetDirection(& 	_Global_Front_Motor, MTR_ROTATE_CCW);
		DCMOTOR_voidSetSpeed(& 	_Global_Front_Motor, FRONT_MOTOR_SPEED);
		//BACK MOTOR
		DCMOTOR_voidSetDirection(& 	_Global_Back_Motor, MTR_ROTATE_CW);
		DCMOTOR_voidSetSpeed(& 	_Global_Back_Motor, copy_u16VcleSpeed);
		// LEDs
		GPIO_voidSetPinValue(BACK_RIGHT_LED_PORT, BACK_RIGHT_LED_PIN, LOW);
		GPIO_voidSetPinValue(BACK_LEFT_LED_PORT, BACK_LEFT_LED_PIN, HIGH);
		break;
	case VCLE_STOP:
		/* code */
		//FRONT MOTOR
		DCMOTOR_voidSetDirection(& _Global_Front_Motor, MTR_STOP)	;
		//BACK MOTOR
		DCMOTOR_voidSetSpeed(& 	_Global_Back_Motor, MOTOR_ZERO_SPEED);

		// LEDs
		GPIO_voidSetPinValue(BACK_RIGHT_LED_PORT, BACK_RIGHT_LED_PIN, LOW);
		GPIO_voidSetPinValue(BACK_LEFT_LED_PORT, BACK_LEFT_LED_PIN, LOW);
		break;
	default:
		break;
	}
}
