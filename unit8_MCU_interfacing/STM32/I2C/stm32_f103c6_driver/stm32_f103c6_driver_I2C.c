/*
 * stm32_f103c6_driver_I2C.c
 *
 *  Created on: Jun 26, 2023
 *      Author: hassa
 */


//		|-----------------------------------------------|
//		|===================Includes====================|
//		|-----------------------------------------------|

#include "stm32_f103c6_driver_I2C.h"
#include "stm32_f103c6_driver_RCC.h"




//================================
//GENERIC VARIABLES
//================================
I2C_CFG_t *GP_I2C_CFG[2] ={NULL , NULL};



//================================
//GENERIC function
//================================
enum I2C_INDEX{
	I2C1_INDEX,
	I2C2_INDEX
};




void MCAL_I2C_Init(I2C_TypeDef *I2Cx ,I2C_CFG_t *I2C_CFG ){
	uint16_t Freq;
	uint8_t tmpFreq , tmpCCR;
	//SPI CLOCK ENABLE
	if(I2Cx == I2C1){
		GP_I2C_CFG [I2C1_INDEX] = I2C_CFG;
		RCC_I2C1_CLK_EN();
	}
	else if (I2Cx == I2C2){
		GP_I2C_CFG [I2C2_INDEX] = I2C_CFG;
		RCC_I2C2_CLK_EN();
	}


	//Set the frequency

	//	• Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	//Bits 5:0 FREQ[5:0]: Peripheral clock frequency
	Freq = MCAL_RCC_GET_PCLK1_FRQ();
	tmpFreq = Freq / 1000000;

	I2Cx->CR2 = (I2Cx->CR2 & ~I2C_CR2_FREQ_Msk) | tmpFreq;

	if (I2C_CFG->Speed_Mode == Speed_Mode_SM){
		//	• Configure the clock control registers
		// CCR = fclk1 / (2 * fi2c)
		tmpCCR = Freq / (I2C_CFG->I2C_FREQ << 1);
		I2Cx->CCR = (I2Cx->CCR & ~((uint32_t)0x7FF)) | tmpCCR;
		I2Cx->CCR = (I2Cx->CCR & ~((uint32_t)(1 << 15))) | I2C_CFG->Speed_Mode;
		//	• Configure the rise time register
		I2Cx->TRISE = (I2Cx->TRISE & ~((uint16_t)0x3F)) | (tmpFreq + 1);

		//	• Program the I2C_CR1 register to enable the peripheral


		//	• Set the START bit in the I2C_CR1 register to generate a Start condition The peripheral input clock frequency must be at least:

		//	• 2 MHz in Sm mode

		//	• 4 MHz in Fm mode
	}
	else if (I2C_CFG->Speed_Mode == Speed_Mode_FM){
		//	• Configure the clock control registers
		// CCR = fclk1 / (2 * fi2c)

		//	• Configure the rise time register


		//	• Program the I2C_CR1 register to enable the peripheral


		//	• Set the START bit in the I2C_CR1 register to generate a Start condition The peripheral input clock frequency must be at least:

		//	• 2 MHz in Sm mode

		//	• 4 MHz in Fm mode
	}

	I2Cx->CR1 = (I2Cx->CR1 & ~(1 << 7)) | I2C_CFG->NOSTRETCH;

	I2Cx->CR1 = (I2Cx->CR1 & ~(1 << 10)) | I2C_CFG->ACK;

	I2Cx->CR1 = (I2Cx->CR1 & ~(1 << 6)) | I2C_CFG->ENGC;

	if(I2C_CFG->I2C_Slave_Address.ADDMODE == ADDMODE_7BIT){

		I2Cx->OAR1 = (I2Cx->OAR1 & ~(I2C_OAR1_ADDMODE_Msk)) |  I2C_CFG->I2C_Slave_Address.ADDMODE ;
		I2Cx->OAR1 = (I2Cx->OAR1 & ~(I2C_OAR1_ADD1_Msk)) |  I2C_CFG->I2C_Slave_Address.Primary_address << 1 ;
		if(I2C_CFG->I2C_Slave_Address.ENDUAL == ENDUAL_Enable){
			I2Cx->OAR2 = (I2Cx->OAR2 & ~I2C_OAR2_ENDUAL_Msk) | I2C_CFG->I2C_Slave_Address.ENDUAL;
			I2Cx->OAR2 = (I2Cx->OAR2 & ~I2C_OAR2_ADD2_Msk) | I2C_CFG->I2C_Slave_Address.Secondary_address << 1;
		}
	}
	else if (I2C_CFG->I2C_Slave_Address.ADDMODE == ADDMODE_10BIT){
		I2Cx->OAR1 = (I2Cx->OAR1 & ~(I2C_OAR1_ADDMODE_Msk)) |  I2C_CFG->I2C_Slave_Address.ADDMODE ;
		I2Cx->OAR1 = (I2Cx->OAR1 & ~(I2C_OAR1_ADD1_Msk)) |  I2C_CFG->I2C_Slave_Address.Primary_address;
	}

	if(I2C_CFG->P_Slave_Event_CallBack != NULL){
		I2Cx->CR2 |= I2C_CR2_ITERREN;
		I2Cx->CR2 |= I2C_CR2_ITBUFEN;
		I2Cx->CR2 |= I2C_CR2_ITEVTEN;
	}
	I2Cx->CR1 = (I2Cx->CR1 & ~(I2C_CR1_PE_Msk)) | I2C_CR1_PE;

}


void MCAL_I2C_Reset(I2C_TypeDef *I2Cx ){
	if(I2Cx == I2C1){
		NVIC_IRQ31_I2C1_EV_DISABLE;
		NVIC_IRQ32_I2C1_ER_DISABLE;
		RCC_I2C1_RESET();

	}
	else if (I2Cx == I2C2){

		NVIC_IRQ33_I2C2_EV_DISABLE;
		NVIC_IRQ34_I2C2_ER_DISABLE;
		RCC_I2C2_RESET();
	}
}

void MCAL_I2C_GPIO_SetPins(I2C_TypeDef *I2Cx ){
	GPIO_PinConfig_t gpiocfg;
	if(I2Cx == I2C1){
		//PB6 I2C1_SCL
		//PB7 I2C1_SDA
		gpiocfg.GPIO_PinNumber = GPIO_PIN_6;
		gpiocfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		gpiocfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &gpiocfg);

		gpiocfg.GPIO_PinNumber = GPIO_PIN_7;
		gpiocfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		gpiocfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &gpiocfg);
	}
	else if (I2Cx == I2C2){

		//PB10 I2C2_SCL
		//PB11 I2C2_SDA
		gpiocfg.GPIO_PinNumber = GPIO_PIN_10;
		gpiocfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		gpiocfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &gpiocfg);

		gpiocfg.GPIO_PinNumber = GPIO_PIN_11;
		gpiocfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		gpiocfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &gpiocfg);
	}

}

//Polling mechanism

FlagStatus I2C_GetFlagStatus (I2C_TypeDef *I2Cx ,Status flag ){
	volatile uint32_t dummyRead;
	FlagStatus BitStatus = Reset;
	uint32_t flag1 =0,flag2 = 0;
	uint32_t lastEvent = 0;

	switch (flag){
	case I2C_FLAG_BUSY :
	{
		if(I2Cx->SR2 & I2C_SR2_BUSY)
			BitStatus = Set;
		else
			BitStatus = Reset;
		break;
	}
	case EV5 :
	{
		if(I2Cx->SR1 & I2C_SR1_SB)
			BitStatus = Set;
		else
			BitStatus = Reset;
		break;
	}
	case EV6 :
		{
			if(I2Cx->SR1 & I2C_SR1_ADDR)
				BitStatus = Set;
			else
				BitStatus = Reset;
			dummyRead = I2Cx->SR2;
			break;
		}
	case MASTER_BYTE_TRANSMITTING :
			{
				flag1 = I2Cx->SR1;
				flag2 = I2Cx->SR2;
				flag2 = flag2 << 16;
				lastEvent = (flag1 | flag2) & (uint32_t )0x00FFFFFF;

				if((lastEvent & flag )== flag)
							BitStatus = Set;
						else
							BitStatus = Reset;
				break;
			}
	case EV8 :
	case EV8_1 :
	{
		if(I2Cx->SR1 & I2C_SR1_TXE)
			BitStatus = Set;
		else
			BitStatus = Reset;
		break;
	}
	case EV7 :
	{
		if(I2Cx->SR1 & I2C_SR1_RXNE)
			BitStatus = Set;
		else
			BitStatus = Reset;
		break;
	}
	}
	return BitStatus;
}

void I2C_GenerateSTART(I2C_TypeDef *I2Cx , FunctionalState new_state ,  Reapeted_Start start){

	if(start != repeated_start){
		while(I2C_GetFlagStatus (I2Cx ,I2C_FLAG_BUSY ));
	}
	if(new_state != Disable){
		I2Cx->CR1 |= I2C_CR1_START;
	}
	else {
		I2Cx->CR1 &= ~I2C_CR1_START;
	}

}

void I2C_SendAddress(I2C_TypeDef * I2Cx , uint16_t Address , I2C_Direction direction){

	Address = Address << 1;
	if (direction == Read){
		Address |= 1;
	}
	else {
		Address &= ~((uint16_t)1);
	}
	I2Cx->DR = Address;
}

void I2C_GenerateStop(I2C_TypeDef *I2Cx,  FunctionalState new_state){
	if(new_state == Enable){
		I2Cx->CR1 |= I2C_CR1_STOP;
	}
	else{
		I2Cx->CR1 &= ~I2C_CR1_STOP;
	}
}
void MCAL_I2C_Master_Tx(I2C_TypeDef *I2Cx , uint16_t devAddr , uint8_t *dataOut , uint32_t datalen , Stop_Condition stop , Reapeted_Start start){

	int i;

	I2C_GenerateSTART(I2Cx , Enable , start);

	while(!(I2C_GetFlagStatus (I2Cx ,EV5)));


	 I2C_SendAddress(I2Cx , devAddr , Write);

	 while(!I2C_GetFlagStatus (I2Cx ,EV6));

	 while(!I2C_GetFlagStatus (I2Cx ,MASTER_BYTE_TRANSMITTING));

	 for(i = 0 ; i < datalen ; i++){

		 I2Cx->DR = dataOut[i];
		 while(!I2C_GetFlagStatus (I2Cx ,EV8));
	 }

	 if(stop == withstop){
		 I2C_GenerateStop(I2Cx, Enable);
	 }


}
void MCAL_I2C_Master_Rx(I2C_TypeDef *I2Cx , uint16_t devAddr , uint8_t *dataOut , uint32_t datalen , Stop_Condition stop , Reapeted_Start start){

	int i;

	I2C_GenerateSTART(I2Cx , Enable , start);

	while(!I2C_GetFlagStatus (I2Cx ,EV5));


	I2C_SendAddress(I2Cx , devAddr , Read);

	while(!I2C_GetFlagStatus (I2Cx ,EV6));

	I2C_Ackolage_Config(I2Cx , Enable);
	if(datalen){
		for(i = datalen ; i > 1 ; i--){
			while(!I2C_GetFlagStatus (I2Cx ,EV7));
			*dataOut = I2Cx->DR;
			dataOut++;
		}
		I2C_Ackolage_Config(I2Cx , Disable);
	}
	if(stop == withstop){
		 I2C_GenerateStop(I2Cx, Enable);
	}
}

void MCAL_I2C__SlaveSendData(I2C_TypeDef * I2Cx , uint8_t data){

	I2Cx->DR = data;


}


void MCAL_I2C__SlaveReceiveData(I2C_TypeDef * I2Cx ){

 (uint8_t)I2Cx->DR;

}


void I2C1_EV_IRQHandler(void){



}


void I2C1_ER_IRQHandler(void){


}


void I2C2_EV_IRQHandler(void){
	// volatile uint32_t dummy_Read;
	 I2C_TypeDef * I2Cx = I2C1;
	 uint32_t temp1 ,temp2 ,temp3;

	 temp1 = I2Cx->CR2 & I2C_CR2_ITEVTEN;
	 temp2 = I2Cx->CR2 & I2C_CR2_ITBUFEN;

	 temp3 = I2Cx->SR1 & I2C_SR1_STOPF;



}


void I2C2_ER_IRQHandler(void){

}


