/*
 * ATmega32_ADC.c
 *
 * Created: 31/01/2024 01:03:01 ص
 *  Author: fawzy
 */ 

#include "ATmega32_ADC.h"
#include "ATmega32_GPIO_Driver.h"
#include "BitMath.h"

ADC_Config_t *ADCconfg;
void (*EOC_Callback)(void);


/*********************************
=========Helper Functions=========
*********************************/


/*********************************
=========Supported APIs=========
*********************************/
/********************************/

/**
 * @brief  Initializes the ADC with the specified configuration
 * @param  ADCcfg: Pointer to the ADC configuration structure
 * @retval eStatus_t: Status of the initialization (E_OK or E_NOK)
 */
eStatus_t MCAL_ADC_Init(ADC_Config_t* ADCcfg)
{
	eStatus_t status = E_OK;
	ADCconfg = ADCcfg;
	if(NULL == ADCcfg)
	{
		status = E_NOK;
	}
	else if(!ASSERT_ADC_CLK(ADCcfg->Clock)|| 
			!ASSERT_ADC_InputChannel(ADCcfg->inputChannel) || !ASSERT_ADC_MODE(ADCcfg->conversionMode)	|| 
			!ASSERT_ADC_ReferenceVoltage(ADCcfg->referenceVoltage) || !ASSERT_ADC_Trigger(ADCcfg->conversionTriggerEvent))
	{
		status = E_NOK;
	}
	else
	{
		ADC->ADMUX = 0x00;
		ADC->ADCSRA |= ADCcfg->Clock;
		ADC->ADCSRA |= ADCcfg->conversionMode;
		if(AutoTriggerConversion == ADCcfg->conversionMode)
		{
			SFIOR	&= ~(SFIOR_ADTS0 | SFIOR_ADTS1 | SFIOR_ADTS2);
			SFIOR	|= (ADCcfg->conversionTriggerEvent)<<SFIOR_ADATSource_POS;

		}
		ADC->ADMUX  |= ADCcfg->dataAdjustment;
		ADC->ADMUX	|= ADCcfg->inputChannel;
		ADC->ADMUX	|= ADCcfg->referenceVoltage;
		ADC->ADCSRA |= ADC_ADCSRA_ADEN_MSK; //ADC Enable
	}
	return status;
}

/**
 * @brief  Resets the ADC to its default state
 * @retval eStatus_t: Status of the reset operation (E_OK)
 */
eStatus_t MCAL_ADC_Reset()
{
	eStatus_t status = E_OK;
	
	ADC->ADMUX	= 0x00;
	ADC->ADCSRA	= 0x00;
	SFIOR		&= ~(SFIOR_ADTS0 | SFIOR_ADTS1 | SFIOR_ADTS2);
	
	return status;
}

/**
 * @brief  Starts the ADC conversion process wehere single or autotrigger
 * @retval eStatus_t: Status of the start operation (E_OK)
 */
eStatus_t MCAL_ADC_startConversion()
{
    eStatus_t status = E_OK;
	if(AutoTriggerConversion ==ADCconfg->conversionMode && !READ_BIT(ADC->ADCSRA , ADC_ADCSRA_ADATE_MSK))
	{
		ADC->ADCSRA |= ADC_ADCSRA_ADATE_MSK;
	}
	ADC->ADCSRA |= ADC_ADCSRA_ADSC_MSK;
	return status;
}

/**
 * @brief  Stops the automatic ADC conversion process
 * @retval eStatus_t: Status of the stop operation (E_OK)
 */
eStatus_t MCAL_ADC_autoConversionStop()
{
	eStatus_t status = E_OK;

	/*Wait for current conversion process.*/
	while(READ_BIT(ADC->ADCSRA, ADC_ADCSRA_ADSC_MSK) && !READ_BIT(ADC->ADCSRA, ADC_ADCSRA_ADIF_MSK));

	CLEAR_BIT(ADC->ADCSRA, ADC_ADCSRA_ADATE_MSK);

	return status;
}

/**
 * @brief  Changes the input channel of the ADC
 * @param  channel: The new ADC input channel to be set
 * @retval eStatus_t: Status of the change operation (E_OK or E_NOK)
 */
eStatus_t MCAL_ADC_changeInputChannel(eADC_InputChannel channel)
{		
	eStatus_t status = E_NOK;
	
	if(!ASSERT_ADC_InputChannel(channel))
	{
		status = E_NOK;
	}
	else
	{
		//Wait for Current conversion
		while(READ_BIT(ADC->ADCSRA,ADC_ADCSRA_ADSC_MSK));
		
		MCAL_ADC_autoConversionStop();
		CLEAR_BITS(ADC->ADMUX , ADC_ADMUX_MUX0_MSK , 0x11111);
		ADC->ADMUX |= channel;
		
		MCAL_ADC_startConversion();//Resume conversion after changing channel
	}
	return status;
}

/**
 * @brief  Retrieves the ADC conversion result
 * @param  pBuffer: Pointer to the variable where the conversion result will be stored
 * @retval eStatus_t: Status of the retrieval operation (E_OK or E_NOK)
 */
eStatus_t MCAL_ADC_getConversionResult(uint16_t *pBuffer)
{
	eStatus_t status = E_OK;

	if(NULL == pBuffer)
	{
		status = E_NOK;
	}
	else
	{
		//Wait for end of conversion flag
		while(!(ADC->ADCSRA & ADC_ADCSRA_ADIF_MSK));
		if(RightAdjusted == ADCconfg->dataAdjustment)
		{
			*pBuffer = (ADC->ADCL);
			*pBuffer = *pBuffer | (ADC->ADCH << 8);
		}
		else //Left adjusted
		{
			*pBuffer = (ADC->ADCL >> 6) | (ADC->ADCH << 8);
		}
		
		//Clear ADIF Flag by writing 1
		ADC->ADCSRA |= ADC_ADCSRA_ADIF_MSK;
	}
	return status;
}

/**
 * @brief  Registers a callback function for the end of ADC conversion interrupt
 * @param  callback: Pointer to the function to be called when the conversion completes
 * @retval eStatus_t: Status of the registration operation (E_OK or E_NOK)
 */
eStatus_t MCAL_ADC_setEndOfConversion_CALLBACK(void (*callback)(void))
{
	eStatus_t status = E_OK;
	
	if(NULL == callback)
	{
		status = E_NOK;
	}
	else
	{
		EOC_Callback = callback;
		ADC->ADCSRA |= ADC_ADCSRA_ADIE_MSK;
		sei(); //Enable Global interrupt
	}
	return status;
}


/**************************************************************************************************************************
===============================================
*               ADC ISR functions
*===============================================
*/
// Overriding ISR of ADC

/**
 * @brief  ADC conversion complete ISR
 * @note   Calls the registered end-of-conversion callback function
 */
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void){
	
	if(EOC_Callback)
	{
		EOC_Callback();
	}
}
