/*
 * ADC.c
 *
 * Created: 7/1/2023 10:52:42 PM
 *  Author: hassa
 */ 


//---------
//Includes
//---------
#include "ADC.h"
		
//---------------
//macros function
//---------------	
void (*P_ADC_CallBack)();		


		
/**================================================================
 * @Fn			-MCAL_GPIO_init.
 * @brief	    -initialize the GPIOx PINy according to config instance cfg.
 * @param [in] 	-GPIOx: x can be (A...D) to select the GPIO peripheral.
 * @param [in] 	-cfg: pointer to GPIO_config that contains pin/port configuration.
 * @retval 		-none
 * Note			-none
 */
void MCAL_ADC_Init(ADC_config * cfg)
{
	ADC_->ADCSRA.bits.ADPS2_0 = cfg->ADC_Prescaler;
	ADC_->ADMUX.bits.MUX4_0 = cfg->ADC_Channel;
	ADC_->ADMUX.bits.REFS1_0 = cfg->ADC_RefSelect;
	ADC_->ADMUX.bits.ADLAR = cfg->ADC_AdjustResult;
	ADC_->ADCSRA.bits.ADIE = cfg->ADC_Interrupt;
	if(cfg->ADC_Interrupt == ADC_ENABLE_INTERRUPT ){
		ENABLE_INT();
		P_ADC_CallBack = cfg->P_ADC_CallBack_Fn;	
	}
	ADC_->ADCSRA.bits.ADEN = 0b1;
}



/**================================================================
 * @Fn			-MCAL_ADC_Deinit.
 * @brief	    -deinitialize the GPIOx PINy according to config instance cfg.
 * @param [in] 	-none
 * @retval 		-none
 * Note			-none
 */
void MCAL_ADC_Deinit()
{
	ADC_->ADCSRA.ADCSRA=0x00;
	ADC_->ADMUX.ADMUX=0x00;
}


/**================================================================
 * @Fn			-MCAL_ADC_ChangeChannel.
 * @brief	    -change channel in ADC
 * @param [in] 	-ChannelNo
 * @retval 		-none
 * Note			-none
 */
void MCAL_ADC_ChangeChannel(uint8 ChannelNo )
{
	ADC_->ADCSRA.bits.ADEN = 0b0;
	ADC_->ADMUX.bits.MUX4_0 = ChannelNo;
	ADC_->ADCSRA.bits.ADEN = 0b1;
}


/**================================================================
 * @Fn			-MCAL_ADC_Read.
 * @brief	    -read ADC 
 * @param [in] 	-none
 * @retval 		-none
 * Note			-none
 */
uint16 MCAL_ADC_Read()
{
	uint16 data;
	ADC_->ADCSRA.bits.ADSC = 0b1;
	while(ADC_->ADCSRA.bits.ADIF != 1);
	data = ADC_->ADCL_H;
	return data;		
}