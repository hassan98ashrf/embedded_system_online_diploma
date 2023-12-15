/*
 * FIND_PARKING.h
 *
 *  Created on: Nov 21, 2023
 *      Author: remaa
 */

#ifndef SERVICE_FIND_PARKING_FIND_PARKING_H_
#define SERVICE_FIND_PARKING_FIND_PARKING_H_




/******************************************************************************
* Includes
*******************************************************************************/




/******************************************************************************
* User Configuration
*******************************************************************************/




/******************************************************************************
* Preprocessor Constants
 *******************************************************************************/




/******************************************************************************
* Configuration Constants
*******************************************************************************/




/******************************************************************************
* Macros
*******************************************************************************/

#define MIN_DISTANCE_TO_BE_IN_PARKING_LANE           12         // MARGIN Used when going forward right

#define MIN_DEPTH_TO_DETECT_SLOT                     30         // Depth of slot



#define MIN_FRONT_DISTANCE_IN_PARKING                5          // Min Front Distance for safty


#define FIND_SLOT_SPEED                              130       // Speed of vechile while finding slot



/******************************************************************************
* Typedefs
*******************************************************************************/


/******************************************************************************
* Variables
*******************************************************************************/




/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * @brief This Function Will Initialize the Component 4 : Find Parking Slot
 *
 */
void C4SLTFIND_voidInit(void);


/**
 * @brief This Function When Called the vehicle Start Search for parking slot
 *
 * @details The vehicle will goes to the rightmost and start searching for a sutiable slot
 */
ERROR_t C4SLTFIND_voidSearchingforSlotFull(void);


ERROR_t C4SLTFIND_voidSearchingforSlot(void);



#endif /* SERVICE_FIND_PARKING_FIND_PARKING_H_ */
