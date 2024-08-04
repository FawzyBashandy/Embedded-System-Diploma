/*
 * ATmega32_Timer0.c
 *
 * Created: 31/01/2024 01:03:01 ص
 *  Author: fawzy
 */ 

#include "ATmega32_GPIO_Driver.h"
#include "ATmega32_Timer0.h"


uint32_t overflowCounter = 0;
void (*overflowCallback)(void);
void (*outputCompareMatchCallback)(void);

/*********************************
=========Helper Functions=========
*********************************/
void ConfigureOC0()
{
	pinConfig_t Pincfg;
	Pincfg.pinNumber  = GPIO_PIN_3;
	Pincfg.pinMode	  = GPIO_MODE_OUTPUT;
	MCAL_GPIO_Init(GPIOB,&Pincfg);
}

/*********************************
=========Supported APIs=========
*********************************/
/********************************/

/**
 * @brief  Initializes Timer0 with the specified configuration
 * @param  timerCFG: Pointer to a Timer0_Config_t structure that contains the configuration information for Timer0
 * @retval eStatus_t: Returns E_OK if successful, otherwise E_NOK if the configuration is invalid
 */
eStatus_t MCAL_TIMER0_Init(Timer0_Config_t* timerCFG)
{
    eStatus_t status = E_OK;
	
	if(NULL == timerCFG)
	{
		status = E_NOK;
	}/*Assert all the parameters in the configuration struct*/
    else if(!ASSERT_TIMER_CLK(timerCFG->ClockSource) || !ASSERT_TIMER_MODE(timerCFG->OperationMode) ||
    !ASSERT_TIMER_COM(timerCFG->CompareMode)     || !ASSERT_TIMER_TOIE(timerCFG->OverFlowInterrupt)  ||
    !ASSERT_TIMER_TOCIE(timerCFG->CompareMatchInterrupt)){
	    
	    status = E_NOK;
	}
	else
	{
		Timer0->TCCR0 = 0;
		Timer0->TCCR0 |= timerCFG->OperationMode;
		Timer0->TCCR0 |= timerCFG->CompareMode;
		
		/*Clear the interrupt mask bits*/
		Timer0->TIMSK &= ~(TIMER0_TIMSK_OCIE0_MSK | TIMER0_TIMSK_TOIE0_MSK);

		Timer0->TIMSK |= timerCFG->CompareMatchInterrupt;
		Timer0->TIMSK |= timerCFG->OverFlowInterrupt;
		
		if(Timer_COM_Disconnected != timerCFG->CompareMode)
		{
			ConfigureOC0();
		}
		
		if((Timer_TOCI_Enable == timerCFG->CompareMatchInterrupt ) || (Timer_TOI_Enable == timerCFG->OverFlowInterrupt))
		{
			sei();
		}
	}
	
	Timer0->TCCR0 |= timerCFG->ClockSource;
	return status;
}

/**
 * @brief  Stops Timer0 by disabling its clock source
 * @retval eStatus_t: Returns E_OK if successful
 */
eStatus_t MCAL_TIMER0_Stop()
{
    eStatus_t status = E_OK;
	
	/*Disable the clock to stop the timer*/
	Timer0->TCCR0 &= ~(TIMER0_TCCR_CS0_MSK | TIMER0_TCCR_CS1_MSK);
	
	return status;
}

/**
 * @brief  Retrieves the current compare value from Timer0
 * @param  compareVal: Pointer to a uint8_t variable where the current compare value will be stored
 * @retval eStatus_t: Returns E_OK if successful
 */
eStatus_t MCAL_TIMER0_GetCompare(uint8_t* compareVal)
{
	eStatus_t status = E_OK;
	 
	*compareVal = Timer0->OCR0;
	
	return status;
}

/**
 * @brief  Sets the compare value for Timer0
 * @param  compareVal: The new compare value to set
 * @retval eStatus_t: Returns E_OK if successful
 */
eStatus_t MCAL_TIMER0_SetCompare(uint8_t compareVal)
{
	eStatus_t status = E_OK;
	
	Timer0->OCR0 = compareVal;
	
	return status;
}

/**
 * @brief  Retrieves the current counter value from Timer0
 * @param  counterVal: Pointer to a uint8_t variable where the current counter value will be stored
 * @retval eStatus_t: Returns E_OK if successful
 */
eStatus_t MCAL_TIMER0_GetCounter(uint8_t* counterVal)
{
	eStatus_t status = E_OK;
	
	*counterVal = Timer0->TCNT0;
	
	return status;
}

/**
 * @brief  Sets the counter value for Timer0
 * @param  counterVal: The new counter value to set
 * @retval eStatus_t: Returns E_OK if successful
 */
eStatus_t MCAL_TIMER0_SetCounter(uint8_t counterVal)
{
	eStatus_t status = E_OK;
	
	Timer0->TCNT0 = counterVal;
	
	return status;
}

/**
 * @brief  Retrieves the overflow counter value
 * @param  overflowVal: Pointer to a uint32_t variable where the overflow counter value will be stored
 * @retval eStatus_t: Returns E_OK if successful
 */
eStatus_t MCAL_TIMER0_GetOverflow(uint32_t* overflowVal)
{
	eStatus_t status = E_OK;
	
	*overflowVal = overflowCounter;
	
	return status;
}

/**
 * @brief  Sets the overflow counter value
 * @param  overflowVal: The new overflow counter value to set
 * @retval eStatus_t: Returns E_OK if successful
 */
eStatus_t MCAL_TIMER0_SetOverflow(uint32_t overflowVal)
{
    eStatus_t status = E_OK;
	
    overflowCounter = overflowVal;
	
    return status;
}

/**
 * @brief  Registers a callback function for the Timer0 overflow interrupt
 * @param  callback: Pointer to the function to be called when an overflow interrupt occurs
 * @retval None
 */
void MCAL_TIMER0_CALLBACK_Overflow_INTERRUPT(void (*callback)(void))
{
	overflowCallback = callback;
}

/**
 * @brief  Registers a callback function for the Timer0 compare match interrupt
 * @param  callback: Pointer to the function to be called when a compare match interrupt occurs
 * @retval None
 */
void MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(void (*callback)(void))
{
	outputCompareMatchCallback = callback;
}


/**************************************************************************************************************************
===============================================
*               TIMER0 ISR functions
*===============================================
*/
// Overriding ISR of TIMER0

/*Timer/Counter0 Compare Match (Vector number in the datasheet - 1)*/
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void){
	
	outputCompareMatchCallback();
}

/*Timer/Counter0 Overflow*/
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void){

	overflowCounter++;
	overflowCallback();
}
