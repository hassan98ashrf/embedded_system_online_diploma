/*
 * stm32_f103c6driver_I2C.h
 *
 *  Created on: Jun 26, 2023
 *      Author: hassa
 */

#ifndef INC_STM32_F103C6_DRIVER_I2C_H_
#define INC_STM32_F103C6_DRIVER_I2C_H_

//================================
//INCLUDES
//================================
#include "stm32_f103c6.h"
#include "stm32_f103c6_driver_GPIO.h"
#include "stm32_f103c6_driver_RCC.h"


//================================
//GENERIC macros
//================================
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING		((uint32_t) 0x00070080)


//================================
//GENERIC VARIABLES
//================================
struct S_I2C_Slave_Address{
	uint16_t  ENDUAL;		//Dual addressing mode enable
							//0: Only OAR1 is recognized in 7-bit addressing mode
							//1: Both OAR1 and OAR2 are recognized in 7-bit addressing mode
							//Sepecified @ref ENDUAL_define

	uint16_t ADDMODE;		//Addressing mode (slave mode)
							//0: 7-bit slave address (10-bit address not acknowledged)
							//1: 10-bit slave address (7-bit address not acknowledged)
							//Sepecified @ref ADDMODE_define

	uint16_t Primary_address;
	uint8_t Secondary_address;
};



typedef enum{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,		//the APP layer should send the data (I2C_SlaveSendData) in the
	I2C_EV_DATA_RCV			//the APP layer should read the data (I2C_SlaveReceiveData) in
} Slave_State;


typedef enum {
	withstop,
	withoutstop
}Stop_Condition;


typedef enum{
	start,
	repeated_start
}Reapeted_Start;


typedef enum {
	Disable = 0,
	Enable = 1
}FunctionalState;

typedef enum {
	Reset = 0,
	Set = 1
}FlagStatus;

typedef enum{
	I2C_FLAG_BUSY = 0,
	EV5,
	EV6,
	EV7,
	EV8,
	EV8_1,
	MASTER_BYTE_TRANSMITTING = ((uint32_t) 0x00070080),
}Status;

typedef enum {
	Read = 0,
	Write = 1
}I2C_Direction;



//================================
//GENERIC FUNCTIONS
//================================



//================================
//Type Definitions
//================================
typedef struct{
	uint32_t Speed_Mode; 	//I2C master mode selection Fast mode or Standard mode
							//Specified @ ref Speed_Mode_define

	uint32_t I2C_FREQ;		//@ref I2C_FREQ_deine

	uint32_t NOSTRETCH;		//Clock stretching disable (Slave mode)
								//This bit is used to disable clock stretching in slave mode when ADDR or BTF flag is set, untilit is reset by software.
								//Specefied @ref NOSTRETCH_define

	uint32_t SMBUS;			//SMBus mode
							//This bit is used to select the mode (I2C mode or SMBUS mode)
							//Specefied @ref SMBUS_define

	struct S_I2C_Slave_Address I2C_Slave_Address;

	uint32_t ACK;		//Acknowledge enable
						//This bit is set and cleared by software and cleared by hardware when PE=0.
						//Specified @ref ACK_define



	uint32_t ENGC;		//General call enable
						//0: General call disabled. Address 00h is NACKed.
						//1: General call enabled. Address 00h is ACKed.
						//Specefied @ref ENGC_define

	void (* P_Slave_Event_CallBack)(Slave_State state);
}I2C_CFG_t;



//================================
//Macros Configuration References
//================================

//@ ref Speed_Mode_define
#define Speed_Mode_FM		(1 << 15)
#define Speed_Mode_SM		0

//@ref I2C_FREQ_deine
#define I2C_FREQ_SM_50K		0x50000U
#define I2C_FREQ_SM_100K	100000U
#define I2C_FREQ_FM_200K	200000U
#define I2C_FREQ_FM_400K	400000U

//@ref NOSTRETCH_define
#define NOSTRETCH_Enable	0
#define NOSTRETCH_Disable	I2C_CR1_NOSTRETCH

//@ref SMBUS_define
#define SMBUS_I2C			0
#define SMBUS_smbus			I2C_CR1_SMBUS

//@ref ENDUAL_define
#define ENDUAL_Enable		I2C_OAR2_ENDUAL
#define ENDUAL_Disable		0

//@ref ADDMODE_define
#define ADDMODE_7BIT		0
#define ADDMODE_10BIT		I2C_OAR1_ADDMODE

//@ref ACK_define
#define ACK_Enable			I2C_CR1_ACK
#define ACK_Disable			0

//@ref ENGC_define
#define ENGC_Enable			I2C_CR1_ENGC
#define ENGC_Disable		0



/*
 * =======================================================================================
 * 							APIs Supported by "MCAL GPIO DRIVER"
 * =======================================================================================
 */


void MCAL_I2C_Init(I2C_TypeDef *I2Cx ,I2C_CFG_t *I2C_CFG );


void MCAL_I2C_Reset(I2C_TypeDef *I2Cx );

void MCAL_I2C_GPIO_SetPins(I2C_TypeDef *I2Cx );


//Polling mechanism
void MCAL_I2C_Master_Tx(I2C_TypeDef *I2Cx , uint16_t devAddr , uint8_t *dataOut , uint32_t datalen , Stop_Condition stop , Reapeted_Start start);
void MCAL_I2C_Master_Rx(I2C_TypeDef *I2Cx , uint16_t devAddr , uint8_t *dataOut , uint32_t datalen , Stop_Condition stop , Reapeted_Start start);


//Interrupt mechanism
void MCAL_I2C__SlaveSendData(I2C_TypeDef * I2Cx , uint8_t data);
void MCAL_I2C__SlaveReceiveData(I2C_TypeDef * I2Cx );

//		|-----------------------------------------------|
//		|================GENERIC APIs===================|
//		|-----------------------------------------------|

void I2C_GenerateSTART(I2C_TypeDef* I2Cx , FunctionalState new_state ,  Reapeted_Start start);
FlagStatus I2C_GetFlagStatus (I2C_TypeDef *I2Cx ,Status flag );
void I2C_SendAddress(I2C_TypeDef * I2Cx , uint16_t Address , I2C_Direction direction);
void I2C_GenerateStop(I2C_TypeDef *I2Cx,  FunctionalState new_state);
void I2C_Ackolage_Config(I2C_TypeDef *I2Cx , FunctionalState new_state);




#endif /* INC_STM32_F103C6_DRIVER_I2C_H_ */
