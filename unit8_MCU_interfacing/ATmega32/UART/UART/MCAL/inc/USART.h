/*
 * USART.h
 *
 * Created: 6/26/2023 11:30:43 AM
 *  Author: hassa
 */ 


#ifndef USART_H_
#define USART_H_

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//============== Includes ==============
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#include "Atmega32.h"
#include "GPIO.h"
#include "EXTI.h"


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== Type Definitions ==========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef struct{
	
	uint8_t INT_CASE;			//Enable the interrupt of the USART or not
								//Specified @ref INT_CASE_define
	
	uint8_t USART_ENABLE;		//Enable the USART
								//Specified @ref USART_ENABLE_define
								
	uint8_t MPCM_Case;			//Enable or disable the Multi-processor Communication Mode 
								//Specified @ref MPCM_Case_define
	
	uint8_t CLK_MODE;			//Defines which used clock mode synchronous or Asynchronous 
								//Specified @ref CLK_MODE_define	
	
	uint8_t Device_SYNCH_MODE;	//Define which device mode used master or slave
								//Specified @ref Device_SYNCH_MODE_define
							
	uint8_t Device_ASYNCH_MODE;	//Define which device mode used normal speed or double speed
								//Specified @ref Device_ASYNCH_MODE_define							
	
	uint8_t BaudRate;			//Defines the baud rate if the asynchronous clock mode
								//Specified @ref BaudRate_define
	
	uint8_t DataSize;			//Defines the effective data size transmitted
								//Specified @ref DataSize_define
								//NOTE : Data size 5:8 specified in register UCSRC bits UCSZ1 UCSZ0
								//BUT Data size 9 specified in register UCSRB bit UCSZ2 & register UCSRC bits UCSZ1 UCSZ0
							
								
	uint8_t Parity;				//Defines the parity bit if used even or odd
								//Specified @ref Parity_define
	
	uint8_t StopBits;			//Defines the count of the stop bits
								//Specified @ref StopBits_define
	
	uint8_t ClockPolarity;		//Defines the polarity of the clock in synchronous mode rising edge or falling edge 
								//Specified @ref ClockPolarity_define
	
	void(*P_USART_CallBack[3])(void);
}USART_CFG_t;




//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//== Macros Configuration References ==
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//@ref INT_CASE_define
#define INT_CASE_Enable				1
#define INT_CASE_Disable			0


//@ref USART_ENABLE_define
//UCSRB->RXEN_4 , TXEN_3
#define USART_ENABLE_TX				0b01	
#define USART_ENABLE_RX				0b10
#define USART_ENABLE_TX_RX			0b11


//@ref MPCM_Case_define
//UCSRA->0
#define MPCM_Case_Enable			1	
#define MPCM_Case_Disable			0	


//@ref CLK_MODE_define
//UCSRC->6
#define CLK_MODE_SYNCH				1	
#define CLK_MODE_ASYNCH				0	


//@ref Device_SYNCH_MODE_define
#define Device_SYNCH_MODE_Master	1
#define Device_SYNCH_MODE_Salve		0

//@ref Device_ASYNCH_MODE_define
//UCSRA->1
#define Device_ASYNCH_MODE_NormalSpeed	0
#define Device_ASYNCH_MODE_DoubleSpeed	1


//@ref BaudRate_define	
//UBRRL , UBBRH->[0:3]	
//1000000HZ	normal speed	
#define BaudRate_1MHZ_NORM_2400		25
#define BaudRate_1MHZ_NORM_4800		12
#define BaudRate_1MHZ_NORM_9600		6
#define BaudRate_1MHZ_NORM_14400	3
#define BaudRate_1MHZ_NORM_19200	2
#define BaudRate_1MHZ_NORM_28800	1
#define BaudRate_1MHZ_NORM_38400	1
#define BaudRate_1MHZ_NORM_57600	0



//1000000HZ double speed
#define BaudRate_1MHZ_DOUB_2400		51
#define BaudRate_1MHZ_DOUB_4800		25
#define BaudRate_1MHZ_DOUB_9600		12
#define BaudRate_1MHZ_DOUB_14400	8
#define BaudRate_1MHZ_DOUB_19200	6
#define BaudRate_1MHZ_DOUB_28800	3
#define BaudRate_1MHZ_DOUB_38400	2
#define BaudRate_1MHZ_DOUB_57600	1
#define BaudRate_1MHZ_DOUB_76800	1
#define BaudRate_1MHZ_DOUB_115200	0



//2000000HZ	normal speed
#define BaudRate_2MHZ_NORM_2400		51
#define BaudRate_2MHZ_NORM_4800		25
#define BaudRate_2MHZ_NORM_9600		12
#define BaudRate_2MHZ_NORM_14400	8
#define BaudRate_2MHZ_NORM_19200	6
#define BaudRate_2MHZ_NORM_28800	3
#define BaudRate_2MHZ_NORM_38400	2
#define BaudRate_2MHZ_NORM_57600	1
#define BaudRate_2MHZ_NORM_76800	1
#define BaudRate_2MHZ_NORM_115200	0



//2000000HZ double speed
#define BaudRate_2MHZ_DOUB_2400		103
#define BaudRate_2MHZ_DOUB_4800		51
#define BaudRate_2MHZ_DOUB_9600		25
#define BaudRate_2MHZ_DOUB_14400	16
#define BaudRate_2MHZ_DOUB_19200	12
#define BaudRate_2MHZ_DOUB_28800	8
#define BaudRate_2MHZ_DOUB_38400	6
#define BaudRate_2MHZ_DOUB_57600	3
#define BaudRate_2MHZ_DOUB_76800	2
#define BaudRate_2MHZ_DOUB_115200	1
#define BaudRate_2MHZ_DOUB_250000	0

//4000000HZ	normal speed
#define BaudRate_4MHZ_NORM_2400		103
#define BaudRate_4MHZ_NORM_4800		51
#define BaudRate_4MHZ_NORM_9600		25
#define BaudRate_4MHZ_NORM_14400	16
#define BaudRate_4MHZ_NORM_19200	12
#define BaudRate_4MHZ_NORM_28800	8
#define BaudRate_4MHZ_NORM_38400	6
#define BaudRate_4MHZ_NORM_57600	3
#define BaudRate_4MHZ_NORM_76800	2
#define BaudRate_4MHZ_NORM_115200	1
#define BaudRate_4MHZ_NORM_230400	0
#define BaudRate_4MHZ_NORM_250000	0


//4000000HZ double speed
#define BaudRate_4MHZ_DOUB_2400		207
#define BaudRate_4MHZ_DOUB_4800		103
#define BaudRate_4MHZ_DOUB_9600		51
#define BaudRate_4MHZ_DOUB_14400	34
#define BaudRate_4MHZ_DOUB_19200	25
#define BaudRate_4MHZ_DOUB_28800	16
#define BaudRate_4MHZ_DOUB_38400	12
#define BaudRate_4MHZ_DOUB_57600	8
#define BaudRate_4MHZ_DOUB_76800	6
#define BaudRate_4MHZ_DOUB_115200	3
#define BaudRate_4MHZ_DOUB_230400	1
#define BaudRate_4MHZ_DOUB_250000 	1
#define BaudRate_4MHZ_DOUB_500000 	0


//8000000HZ	normal speed
#define BaudRate_8MHZ_NORM_2400		207
#define BaudRate_8MHZ_NORM_4800		103
#define BaudRate_8MHZ_NORM_9600		51
#define BaudRate_8MHZ_NORM_14400	34
#define BaudRate_8MHZ_NORM_19200	25
#define BaudRate_8MHZ_NORM_28800	16
#define BaudRate_8MHZ_NORM_38400	12
#define BaudRate_8MHZ_NORM_57600	8
#define BaudRate_8MHZ_NORM_76800	6
#define BaudRate_8MHZ_NORM_115200	3
#define BaudRate_8MHZ_NORM_230400	1
#define BaudRate_8MHZ_NORM_250000	1
#define BaudRate_8MHZ_NORM_500000 	0

//8000000HZ double speed
#define BaudRate_8MHZ_DOUB_2400		416
#define BaudRate_8MHZ_DOUB_4800		207
#define BaudRate_8MHZ_DOUB_9600		103
#define BaudRate_8MHZ_DOUB_14400	68
#define BaudRate_8MHZ_DOUB_19200	51
#define BaudRate_8MHZ_DOUB_28800	34
#define BaudRate_8MHZ_DOUB_38400	25
#define BaudRate_8MHZ_DOUB_57600	16
#define BaudRate_8MHZ_DOUB_76800	12
#define BaudRate_8MHZ_DOUB_115200	8
#define BaudRate_8MHZ_DOUB_230400 	3
#define BaudRate_8MHZ_DOUB_250000 	3
#define BaudRate_8MHZ_DOUB_500000 	1
#define BaudRate_8MHZ_DOUB_1000000 	0


//16000000HZ	normal speed
#define BaudRate_16MHZ_NORM_2400	416	
#define BaudRate_16MHZ_NORM_4800	207
#define BaudRate_16MHZ_NORM_9600	103
#define BaudRate_16MHZ_NORM_14400	68
#define BaudRate_16MHZ_NORM_19200	51
#define BaudRate_16MHZ_NORM_28800	34
#define BaudRate_16MHZ_NORM_38400	25
#define BaudRate_16MHZ_NORM_57600	16
#define BaudRate_16MHZ_NORM_76800	12
#define BaudRate_16MHZ_NORM_115200	8
#define BaudRate_16MHZ_NORM_230400	3
#define BaudRate_16MHZ_NORM_250000	3
#define BaudRate_16MHZ_NORM_500000 	1
#define BaudRate_16MHZ_NORM_1000000 0

//16000000HZ double speed
#define BaudRate_16MHZ_DOUB_2400	832	
#define BaudRate_16MHZ_DOUB_4800	416
#define BaudRate_16MHZ_DOUB_9600	207	
#define BaudRate_16MHZ_DOUB_14400	138	
#define BaudRate_16MHZ_DOUB_19200	103	
#define BaudRate_16MHZ_DOUB_28800	68	
#define BaudRate_16MHZ_DOUB_38400	51	
#define BaudRate_16MHZ_DOUB_57600	34	
#define BaudRate_16MHZ_DOUB_76800	25	
#define BaudRate_16MHZ_DOUB_115200	16
#define BaudRate_16MHZ_DOUB_230400	8
#define BaudRate_16MHZ_DOUB_250000	7
#define BaudRate_16MHZ_DOUB_500000 	3
#define BaudRate_16MHZ_DOUB_1000000 1


//20000000HZ normal speed
#define BaudRate_20MHZ_NORM_2400	520
#define BaudRate_20MHZ_NORM_4800	259
#define BaudRate_20MHZ_NORM_9600	129
#define BaudRate_20MHZ_NORM_14400	86
#define BaudRate_20MHZ_NORM_19200	64
#define BaudRate_20MHZ_NORM_28800	42
#define BaudRate_20MHZ_NORM_38400	32
#define BaudRate_20MHZ_NORM_57600	21
#define BaudRate_20MHZ_NORM_76800	15
#define BaudRate_20MHZ_NORM_115200	10
#define BaudRate_20MHZ_NORM_230400	4
#define BaudRate_20MHZ_NORM_250000	4

//20000000HZ double speed
#define BaudRate_20MHZ_DOUB_2400	1041
#define BaudRate_20MHZ_DOUB_4800	520
#define BaudRate_20MHZ_DOUB_9600	259
#define BaudRate_20MHZ_DOUB_14400	173
#define BaudRate_20MHZ_DOUB_19200	129
#define BaudRate_20MHZ_DOUB_28800	86
#define BaudRate_20MHZ_DOUB_38400	64
#define BaudRate_20MHZ_DOUB_57600	42
#define BaudRate_20MHZ_DOUB_76800	32
#define BaudRate_20MHZ_DOUB_115200	21
#define BaudRate_20MHZ_DOUB_230400	10
#define BaudRate_20MHZ_DOUB_250000	9
#define BaudRate_20MHZ_DOUB_500000 	4
//___________________________________________	


		
		
//@ref DataSize_define
//UCSRC->1,2
#define DataSize_5	0b00
#define DataSize_6	0b01
#define DataSize_7	0b10
#define DataSize_8	0b11
//UCSRB->2
#define DataSize_9	0b111


//@ref Parity_define
//UCSRC->4,5
#define Parity_Disable		0b00
#define Parity_EN_EVEN		0b10
#define Parity_EN_ODD		0b11


//@ref StopBits_define
//UCSRC->3
#define StopBits_1BIT	0
#define StopBits_2BITs	1


//@ref ClockPolarity_define
//UCSRC->0
#define ClockPolarity_Faling	0
#define ClockPolarity_Rising	1



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== APIs Supported by "MCAL UART DRIVER" ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

/**================================================================
* @Fn - MCAL_USART_Init
* @brief - Initialize USART
* @param[in] - USART pin configurations
*/
void MCAL_USART_Init(USART_CFG_t *USART_CFG);



/**================================================================
* @Fn - MCAL_USART_Reset
* @brief - Reset USART
*/
void MCAL_USART_Reset(void);



/**================================================================
* @Fn - MCAL_USART_GPIO_SetPins
* @brief - Set the GPIO pins according to the chosen USART
* @param[in] - USART pin configurations
*/
void MCAL_USART_GPIO_SetPins(USART_CFG_t *USART_CFG);



/**================================================================
* @Fn - MCAL_USART_SendData
* @brief - Send data from the microcontroller to another peripheral cross USART
* @param[in] - Pointer to the buffer used to store data
* @param[in] - USART pin configurations
*/
void MCAL_USART_SendData(uint16_t *PBuffer , USART_CFG_t *USART_CFG);



/**================================================================
* @Fn - MCAL_USART_ReceiveData
* @brief - Receive data from a particular peripheral to microcontroller cross USART
* @param[in] - Pointer to the buffer used to store data
* @param[in] - USART pin configurations
*/
void MCAL_USART_ReceiveData(uint16_t *PBuffer , USART_CFG_t *USART_CFG);




#endif /* USART_H_ */