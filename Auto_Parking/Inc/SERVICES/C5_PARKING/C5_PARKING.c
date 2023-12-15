/**
 * @file C5_PARKING.c
 * @author Your Name (email)
 * @brief
 * @version 0.1
 * @date 2023-09-15
 *
 */
/******************************************************************************
 * Includes
 *******************************************************************************/
#include "STD_TYPES.h"
#include "UTILS.h"
#include "SW_Delay.h"
#include "BIT_MATH.h"
#include "../SERVICES/C1_US_SLCT/C1_US_SLCT.h"
#include "../SERVICES/C3_VCLE_ALIGN/C3_VCLE_ALIGN.h"
#include "../SERVICES/C2_VCLE_CNTRL/C2_VCLE_CNTRL.h"
#include "C5_PARKING.h"





/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

#define PARKING_STEERING				(u16)210
#define PARKING_SPEED					(u16)140
#define PARKING_ZERO_STEERING			(u16)0
#define PARKING_ZERO_SPEED				(u16)0

#define MOVEMENT_DELAY					1000

/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/
#define BACK_RIGHT_THERSHOLD			4
#define BACK_THERSHOLD					16

/********alignment thresholds**************************************************/

#define FRONT_DISTANCE_THRESHOLD		2		
#define BACK_DISTANCE_THRESHOLD			2


/******************************************************************************
 * Typedefs
 *******************************************************************************/


typedef enum
{
	PARKING_NOK,
	PARKING_OK

}ParkingStat_t;


/******************************************************************************
 * Module Variable Definitions
 *******************************************************************************/




/******************************************************************************
 * Function Prototypes
 *******************************************************************************/



/******************************************************************************
 * Function Definitions
 *******************************************************************************/


void C5VCLEPRK_voidInitParking(void)
{

	/*initialize the US sensor select component*/
	APPC1_Init();
	/*initialize motion control component*/
	//C2VCONTROL_voidInit();

}




ERROR_t C5VCLEPRK_voidStartParking(void)
{

	u16 LOC_u16FrontDistance ;
	u16 LOC_u16BackDistance ;
	u16 LOC_u16FrontRightDistance ;
	u16 LOC_u16BackRightDistance ;

	ERROR_t US_ErrorStat	;
	ParkingStat_t ReturnEstatus = PARKING_OK;
	VCLE_State_t VehicleState = VCLE_NOT_ALINED_TURN_RIGHT ;

	US_ErrorStat = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
	if(US_ErrorStat != E_OK)
		return US_ErrorStat ;

	if(E_OK == US_ErrorStat)
	{

		/*********1st step in parking : the fornt wheels turn all way to the right and move backward******************/
		while ((BACK_RIGHT_THERSHOLD != LOC_u16BackRightDistance)&& (BACK_THERSHOLD != LOC_u16BackDistance)&& (E_OK == US_ErrorStat))
		{

			C2VCONTROL_voidChangeDirection(VCLE_RIGHT_BWD  , PARKING_SPEED);
			US_ErrorStat = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
			if(US_ErrorStat != E_OK)
				return US_ErrorStat ;

			//ReturnEstatus = PARKING_OK;

		}

		/*Stop the car after reaching the first motion threshold*/
		C2VCONTROL_voidChangeDirection(VCLE_STOP  , PARKING_ZERO_SPEED );
		/***********************************************************************************************/

		/*********First check if there is a success in motion one or not *********************************************/
		if(E_OK == US_ErrorStat)
			ReturnEstatus = PARKING_OK;
		else
			ReturnEstatus = PARKING_NOK;

		/***************************************************************************************************************/

		/*********2nd step in parking : the fornt wheels turn all way to the left and move backward******************/
		while ((BACK_THERSHOLD <= LOC_u16BackDistance) && (E_OK == US_ErrorStat) && (PARKING_OK ==  ReturnEstatus)  )
		{
			C2VCONTROL_voidChangeDirection(VCLE_LEFT_BWD  , PARKING_SPEED);
			US_ErrorStat = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
			if(US_ErrorStat != E_OK)
				return US_ErrorStat ;
		}
		/*Stop the car after reaching the SECOND motion threshold*/
		C2VCONTROL_voidChangeDirection(VCLE_STOP  , PARKING_ZERO_SPEED );
		/***********************************************************************************************/

		/*********second check if there is a success in motion Two or not *********************************************/
		if(E_OK == US_ErrorStat)
			ReturnEstatus = PARKING_OK;
		else
			ReturnEstatus = PARKING_NOK;

		/**************************************************************************************************************/



		/**************first check that parking is ok until this point************************************************/
		if (PARKING_OK == ReturnEstatus )
		{
			/*************Align the car in the parking spot****************************/
			/*Check alignment*/
			US_ErrorStat = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
			if(US_ErrorStat != E_OK)
				return US_ErrorStat ;
			VehicleState = C3_voidIsVehicleAlignment(LOC_u16FrontRightDistance , LOC_u16BackRightDistance);
			while ( (VCLE_ALINED != VehicleState ) &&  (E_OK == US_ErrorStat) )
			{
				/*in case the car needs to move forward right or backward left*/
				if( (VCLE_NOT_ALINED_TURN_RIGHT == VehicleState) && (FRONT_DISTANCE_THRESHOLD < LOC_u16FrontDistance))
				{
					C2VCONTROL_voidChangeDirection(VCLE_RIGHT_FWD  , PARKING_SPEED);

				}
				else if( (VCLE_NOT_ALINED_TURN_RIGHT == VehicleState) && (BACK_DISTANCE_THRESHOLD < LOC_u16BackDistance))
				{
					C2VCONTROL_voidChangeDirection(VCLE_LEFT_BWD  , PARKING_SPEED);

				}
				else if ((VCLE_NOT_ALINED_TURN_LEFT == VehicleState) && (FRONT_DISTANCE_THRESHOLD < LOC_u16FrontDistance))
				{
					C2VCONTROL_voidChangeDirection(VCLE_LEFT_FWD  , PARKING_SPEED);
				}
				else if ((VCLE_NOT_ALINED_TURN_LEFT == VehicleState) && (BACK_DISTANCE_THRESHOLD < LOC_u16BackDistance))
				{
					C2VCONTROL_voidChangeDirection(VCLE_RIGHT_BWD  , PARKING_SPEED);
				}


				US_ErrorStat = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
				if(US_ErrorStat != E_OK)
					return US_ErrorStat ;
				VehicleState = C3_voidIsVehicleAlignment(LOC_u16FrontRightDistance , LOC_u16BackRightDistance);

			}

			/*Checking if allignment takes place correctly or not*/
			if(E_OK == US_ErrorStat)
				ReturnEstatus = PARKING_OK;
			else
				ReturnEstatus = PARKING_NOK;
			/******************************************************************************/

		}
		else
		{
			C2VCONTROL_voidChangeDirection(VCLE_STOP  , PARKING_ZERO_SPEED );
			ReturnEstatus = PARKING_NOK;
		}

	}
	else
	{
		C2VCONTROL_voidChangeDirection(VCLE_STOP  , PARKING_ZERO_SPEED );
		ReturnEstatus = PARKING_NOK;
	}

	if(ReturnEstatus != PARKING_OK)
		US_ErrorStat = PARKING_FAILED ;
	return US_ErrorStat;

}
ERROR_t C5VCLEPRK_voidStartParkingM(void)
{
	u16 LOC_u16FrontDistance ;
	u16 LOC_u16BackDistance ;
	u16 LOC_u16FrontRightDistance ;
	u16 LOC_u16BackRightDistance ;

	ERROR_t LOC_xReturnError ;
	u8 LOC_u8IsParked = 0 ;
	LOC_xReturnError = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
	if(LOC_xReturnError != E_OK)
		return LOC_xReturnError ;
	// First Start Going Backright until the back sensor
	while((2*BACK_RIGHT_THERSHOLD < LOC_u16BackRightDistance)&& (2*BACK_THERSHOLD < LOC_u16BackDistance))
	{
		C2VCONTROL_voidChangeDirection(VCLE_RIGHT_BWD  , PARKING_SPEED);
		// Moving BWD RGHT For x ms
		delay_ms(50);
		// Stop With The Same Angle
		C2VCONTROL_voidChangeDirection(VCLE_RIGHT_BWD,0);

		// Check Distances
		LOC_xReturnError = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
		if(LOC_xReturnError != E_OK)
			return LOC_xReturnError ;

	}
	// Stop
	C2VCONTROL_voidChangeDirection(VCLE_STOP,0);
	LOC_xReturnError = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
	if(LOC_xReturnError != E_OK)
		return LOC_xReturnError ;
	while((BACK_THERSHOLD < LOC_u16BackDistance))
	{
		C2VCONTROL_voidChangeDirection(VCLE_LEFT_BWD  , PARKING_SPEED);
		// Moving BWD RGHT For x ms
		delay_ms(50);
		// Stop With The Same Angle
		C2VCONTROL_voidChangeDirection(VCLE_LEFT_BWD,0);
		// Check Distances
		LOC_xReturnError = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
		if(LOC_xReturnError != E_OK)
			return LOC_xReturnError ;
		if(_ABS_((LOC_u16FrontRightDistance-LOC_u16BackRightDistance)) == 3)
		{
			LOC_u8IsParked = 1 ;
			break ;
		}
	}
	// اعدل عجلك
	C2VCONTROL_voidChangeDirection(VCLE_STOP,0);

	if(LOC_u8IsParked != 1)
	{
		// Exit due to lowest distance in back
		// اعدل لقدام بجاااا
		LOC_xReturnError = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
		if(LOC_xReturnError != E_OK)
			return LOC_xReturnError ;
		while(_ABS_((LOC_u16FrontRightDistance-LOC_u16BackRightDistance)) > 3)
		{
			// اعدل لقدام
			C2VCONTROL_voidChangeDirection(VCLE_RIGHT_FWD  , PARKING_SPEED);
			delay_ms(50);
			// Check Distances
			LOC_xReturnError = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
			if(LOC_xReturnError != E_OK)
				return LOC_xReturnError ;
		}
	}
	return LOC_xReturnError;
}

ERROR_t C5VCLEPRK_voidStartParking3(void)
{
	ERROR_t LOC_xReturnError ;
	u16 LOC_u16FrontDistance ;
	u16 LOC_u16BackDistance ;
	u16 LOC_u16FrontRightDistance ;
	u16 LOC_u16BackRightDistance ;
	u8 LOC_u8AlignmentDiffer ;
	(void)LOC_u8AlignmentDiffer;
	u8 StartParkingPrecedure = 0 ;

	// Stop Vehicle
	C2VCONTROL_voidChangeDirection(VCLE_STOP,0);

	// Evaluate First Impression
	LOC_xReturnError = C4_StaticGetFourDistance(&LOC_u16FrontDistance , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
	if(LOC_xReturnError != E_OK)
		return LOC_xReturnError ;
	LOC_u8AlignmentDiffer = _ABS_((LOC_u16FrontRightDistance-LOC_u16BackRightDistance)) ;
	// Suppose That Front, Back Distance are so big and FR, RR are aligned so start parking scenario
//	if(LOC_u16FrontDistance > 20 && LOC_u16BackDistance > 20 && LOC_u8AlignmentDiffer < 3)
//	{
//		StartParkingPrecedure = 1 ;
//	}
//	else
//	{
//		StartParkingPrecedure = 0 ;
//	}

	StartParkingPrecedure = 1 ;

	if(StartParkingPrecedure == 1)
	{
		// First Movement The Vehicle
		C2VCONTROL_voidChangeDirection(  VCLE_LEFT_FWD , PARKING_SPEED);
		while(LOC_u16BackDistance > (2*BACK_THERSHOLD)  && LOC_u16BackRightDistance > (2*BACK_RIGHT_THERSHOLD))
		{
			LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
			if(LOC_xReturnError != E_OK)
				return LOC_xReturnError ;

		}
		C2VCONTROL_voidChangeDirection(VCLE_STOP,0);
		delay_ms((MOVEMENT_DELAY));

		// Now Vehicle is stops at angle ~45 with slot
		LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
		if(LOC_xReturnError != E_OK)
			return LOC_xReturnError ;

		C2VCONTROL_voidChangeDirection(VCLE_RIGHT_BWD  , PARKING_SPEED);
		while(LOC_u16BackDistance > BACK_THERSHOLD && StartParkingPrecedure != 2)
		{
			// Stop With The Same Angle
			LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
			if(LOC_xReturnError != E_OK)
				return LOC_xReturnError ;
			// عشان لو لبست
			while (LOC_u16BackDistance >= 1000 || LOC_u16BackRightDistance >= 1000 || LOC_u16FrontRightDistance >= 1000)
			{
				// The vehicle on wall :)
				C2VCONTROL_voidChangeDirection(VCLE_FWD  , PARKING_SPEED);
				delay_ms((MOVEMENT_DELAY/2));
				C2VCONTROL_voidChangeDirection(VCLE_STOP  , PARKING_SPEED);
				LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
				if(LOC_xReturnError != E_OK)
					return LOC_xReturnError ;
			}
			// Check End Point From Loop
			LOC_u8AlignmentDiffer = _ABS_((LOC_u16FrontRightDistance-LOC_u16BackRightDistance)) ;
			if(LOC_u8AlignmentDiffer <= 3 && LOC_u16FrontRightDistance < BACK_RIGHT_THERSHOLD )
			{
				StartParkingPrecedure = 2 ;
			}
		}

		C2VCONTROL_voidChangeDirection(VCLE_STOP,0);
		delay_ms((MOVEMENT_DELAY));

		if(StartParkingPrecedure == 1)
		{
			// Exit Due to Back Distance Isn't Enough
			// Start Alignment Procedure
		}
		else // StartParkingPrecedure == 2
		{
			// Exit Due to Parking Is Complete
			// Then Go Forward Until Back Distance == Front Distance
		}
//		// Now Vehicle is stops at angle ~45 with slot
//		LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
//		if(LOC_xReturnError != E_OK)
//			return LOC_xReturnError ;
//		while(LOC_u16BackDistance > BACK_THERSHOLD && StartParkingPrecedure != 2)
//		{
//			C2VCONTROL_voidChangeDirection(VCLE_LEFT_BWD  , PARKING_SPEED);
//			delay_ms(MOVEMENT_DELAY);
//			// Stop With The Same Angle
//			C2VCONTROL_voidChangeDirection(VCLE_LEFT_BWD,0);
//			LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
//			if(LOC_xReturnError != E_OK)
//				return LOC_xReturnError ;
//			// عشان لو لبست
//			while (LOC_u16BackDistance >= 1000 || LOC_u16BackRightDistance >= 1000 || LOC_u16FrontRightDistance >= 1000)
//			{
//				// The vehicle on wall :)
//				C2VCONTROL_voidChangeDirection(VCLE_FWD  , PARKING_SPEED);
//				delay_ms((MOVEMENT_DELAY/2));
//				LOC_xReturnError = C4_StaticGetFourDistance(NULL , &LOC_u16BackDistance , &LOC_u16FrontRightDistance , &LOC_u16BackRightDistance);
//				if(LOC_xReturnError != E_OK)
//					return LOC_xReturnError ;
//			}
//			// Check End Point From Loop
//			LOC_u8AlignmentDiffer = _ABS_((LOC_u16FrontRightDistance-LOC_u16BackRightDistance)) ;
//			if(LOC_u8AlignmentDiffer <= 3)
//			{
//				StartParkingPrecedure = 2 ;
//			}
//			delay_ms((MOVEMENT_DELAY/5));
//		}
//		delay_ms((MOVEMENT_DELAY));
//
//		if(StartParkingPrecedure == 1)
//		{
//			// Exit Due to Back Distance Isn't Enough
//			// Start Alignment Procedure
//		}
//		else // StartParkingPrecedure == 2
//		{
//			// Exit Due to Parking Is Complete
//			// Then Go Forward Until Back Distance == Front Distance
//		}
	}

	return LOC_xReturnError;
}

/************************************* End of File ******************************************/
