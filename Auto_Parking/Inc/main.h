/*
 * main.h
 *
 *  Created on: Sep 23, 2023
 *      Author: Abnaby
 */

#ifndef MAIN_H_
#define MAIN_H_

/***********************************  Macros  *****************************************/

/*
 * @brief This Macro is used to Log errors to SYS_MNGR
 */
#define LOG_ERROR(VAR_NAME)	 if(VAR_NAME != E_OK || VAR_NAME != NO_SLOT || VAR_NAME != PARKING_FAILED) 					\
								{ 															\
								  DIGMngr_voidLoggError(LOC_xReturnErrorState, 0);			\
								} 															\
								else 														\
								{															\
									DIGMngr_voidLoggError(LOC_xReturnErrorState, 1);		\
								}



/*
 * @brief This Enum is Used to Define Vehicle Working States
 */
typedef enum
{
	USR_CONTROLLED,
	PARKING_MODE
}VehicleStates_t;
#endif /* MAIN_H_ */
