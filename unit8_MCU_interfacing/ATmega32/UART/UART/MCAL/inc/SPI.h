/*
 * SPI.h
 *
 * Created: 6/26/2023 11:44:30 AM
 *  Author: hassa
 */ 


#ifndef SPI_H_
#define SPI_H_


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//============== Includes ==============
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#include "Atmega32.h"
#include "GPIO.h"
#include "EXTI.h"



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== Type Definitions ==========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	uint8_t SPIE;	//Bit 7 – SPIE: SPI Interrupt Enable -> This bit causes the SPI interrupt to be executed
					//Specified @ref SPIE_define
					
	uint8_t SPE;	//Bit 6 – SPE: SPI Enable -> When the SPE bit is written to one, the SPI is enabled
					//Specified @ref SPE_define
					
	uint8_t DORD;	//Bit 5 – DORD: Data Order -> When the DORD bit is written to one, the LSB of the data word is transmitted first.
					//When the DORD bit is written to zero, the MSB of the data word is transmitted first.
					//Specified @ref DORD_define
	
	uint8_t MSTR;	//Bit 4 – MSTR: Master/Slave Select -> This bit selects Master SPI mode & Slave SPI mode
					//Specified @ref MSTR_define
	
	uint8_t CPOL;	//Bit 3 – CPOL: Clock Polarity -> When this bit is written to one, SCK is high when idle. When CPOL is written to zero, SCK is low when idle.
					//Specified @ref CPOL_define
					
	uint8_t CPHA;	//Bit 2 – CPHA: Clock Phase -> (CPHA) determine if data is sampled on the leading (first) or trailing (last) edge of SCK.
					//Specified @ref CPHA_define
					
	uint8_t SPRn;	//Bits 1:0 – SPRn: SPI Clock Rate Select -> These two bits control the SCK rate of the device configured as a Master
					//Specified @ref SPRn_define
					//Note : if the double SPI Speed Bit is set all rates will be doubled (rate * 2)
					
	uint8_t SPI2X;	//Bit 0 – SPI2X: Double SPI Speed Bit -> When this bit is written logic one the SPI speed (SCK Frequency) will be doubled
					//Specified @ref SPI2X_define
					
	void (*PSPI_CallBack)(void);	//Interrupt callback function				
}SPI_CFG_t;



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//== Macros Configuration References ==
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


//@ref SPIE_define
//SPCR Bit 7 – SPIE: SPI Interrupt Enable
#define SPIE_Enable		(1 << 7)	
#define SPIE_Disable	0			


//@ref SPE_define
//SPCR Bit 6 – SPE: SPI Enable
#define SPE_Enable		(1 << 6)
#define SPE_Disable		0		

	
//@ref DORD_define			
//SPCR Bit 5 – DORD: Data Order
#define DORD_LSB		(1 << 5)
#define DORD_MSB		0


//@ref MSTR_define
//SPCR Bit 4 – MSTR: Master/Slave Select
#define MSTR_Master		(1 << 4)
#define	MSTR_Slave		0


//@ref CPOL_define
//SPCR Bit 3 – CPOL: Clock Polarity
#define CPOL_High	(1 << 3)	//SCK is high when idle
#define CPOL_Low		0		//SCK is low when idle


//@ref CPHA_define
//SPCR Bit 2 – CPHA: Clock Phase
#define CPHA_FirstEdge		0			//Sampling at the first edge
#define CPHA_SecondEdge		(1 << 2)	//Sampling at the second edge


//@ref SPRn_define
//SPCR Bits 1:0 – SPRn: SPI Clock Rate Select
#define SPRn_4		0b00	//fosc/4  if SPI2X = 1  fosc/2
#define SPRn_16		0b01	//fosc/16  if SPI2X = 1  fosc/8
#define SPRn_64		0b10	//fosc/64  if SPI2X = 1  fosc/32
#define SPRn_128	0b11	//fosc/128  if SPI2X = 1  fosc/64



//@ref SPI2X_define
//SPSR Bit 0 – SPI2X: Double SPI Speed Bit
#define SPI2X_Enable		(1 << 0)	//written logic one the SPI speed (SCK Frequency) will be doubled
 #define SPI2X_Disable		0
 



//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//========== APIs Supported by "MCAL UART DRIVER" ===========
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

/**================================================================
* @Fn - MCAL_SPI_Init
* @brief - Initialize SPI
* @param[in] - SPI pin configurations
*/
void MCAL_SPI_Init(SPI_CFG_t *SPI_CFG);



/**================================================================
* @Fn - MCAL_SPI_Reset
* @brief - Reset SPI
*/
void MCAL_SPI_Reset(void);



/**================================================================
* @Fn - MCAL_SPI_GPIO_SetPins
* @brief - Set the GPIO pins according to the chosen SPI
* @param[in] - SPI pin configurations
*/
void MCAL_SPI_GPIO_SetPins(SPI_CFG_t *SPI_CFG);



/**================================================================
* @Fn - MCAL_SPI_SendData
* @brief - Send data from the microcontroller to another peripheral cross SPI
* @param[in] - Pointer to the buffer used to store data
* @param[in] - SPI pin configurations
*/
void MCAL_SPI_SendData(uint16_t PBuffer , SPI_CFG_t *SPI_CFG);



/**================================================================
* @Fn - MCAL_SPI_ReceiveData
* @brief - Receive data from a particular peripheral to microcontroller cross SPI
* @param[in] - Pointer to the buffer used to store data
*/
void MCAL_SPI_ReceiveData(uint16_t *PBuffer , SPI_CFG_t *SPI_CFG);



#endif /* SPI_H_ */