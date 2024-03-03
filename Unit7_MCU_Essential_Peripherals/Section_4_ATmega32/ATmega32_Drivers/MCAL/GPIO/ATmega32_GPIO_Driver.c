/*
 * ATmega32_GPIO_Driver.c
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */

/*
===============================================
*                   Includes
*===============================================
*/
#include "ATmega32.h"
#include "ATmega32_GPIO_Driver.h"
#include "Platform_Types.h"
#include <stdint.h>

/**************************************************************************************************************************
===============================================
*           APIs functions definitions
*===============================================
*/


/**================================================================
* @Fn			-MCAL_GPIO_Init
* @brief 		-This API initialize the GPIOx piny/s based on the pinConfig Parameter
* @param [in] 	-GPIOx 	  : where x can be (A .. E) to select the GPIO peripheral
* @param [in] 	-pinConfig: this parameter carry the configuration information to configure GPIOx(first parameter)
* @retval 		-N/A
* Note			-NONE
*/
void MCAL_GPIO_Init(GPIO_t *GPIOx,pinConfig_t *pinConfig)
{
	if(pinConfig->pinMode == GPIO_MODE_OUTPUT)
	{
		SET_BIT(GPIOx->DDR,pinConfig->pinNumber);
	}
	else
	{
		CLEAR_BIT(GPIOx->DDR,pinConfig->pinNumber);
		if(pinConfig->pinMode == GPIO_MODE_INPUT_PU)
		{
			SET_BIT(GPIOx->PORT,pinConfig->pinNumber); //Activate pull up through port register
		}
	}
}

/**================================================================
* @Fn			-MCAL_GPIO_Reset
* @brief 		-This API resets the GPIOx port
* @param [in] 	-GPIOx 	  : where x can be (A .. E) to select the GPIO peripheral
* @retval 		-N/A
* Note			-N/A
*/
void MCAL_GPIO_Reset(GPIO_t *GPIOx)
{
	GPIOx->DDR	= 0x0;
	GPIOx->PORT	= 0x0;
	GPIOx->DDR  = 0;
}


/**================================================================
* @Fn			-MCAL_GPIO_ReadPin
* @brief 		-This API reads a specific pin(pinNumber) from the GPIOx
* @param [in] 	-GPIOx 	  : where x can be (A .. E) to select the GPIO peripheral
* @param [in] 	-pinNumber: this parameter carries the pin to be read from the GPIOx, Pass value based on @ref GPIO_PIN_Define
* @retval 		-The logic(status)(data) of the specified pin, which can be a value of @ref GPIO_PIN_STATUS_Define
* Note			-N/A
*/
uint8_t MCAL_GPIO_ReadPin(GPIO_t *GPIOx , uint8_t pinNumber)
{
	if((READ_BIT(GPIOx->PIN , pinNumber)) != GPIO_PIN_STATUS_LOW)
	{
		return (uint8_t)GPIO_PIN_STATUS_HIGH;
	}
	else
	{
		return (uint8_t)GPIO_PIN_STATUS_LOW;
	}
}

/**================================================================
* @Fn			-MCAL_GPIO_ReadPort
* @brief 		-This API reads the data on GPIOx pins
* @param [in] 	-GPIOx 	  : where x can be (A .. E) to select the GPIO peripheral
* @retval 		-The logic(status)(data) of the specified PORT
* Note			-N/A
*/
uint16_t MCAL_GPIO_ReadPort(GPIO_t *GPIOx)
{
	return (uint8_t)GPIOx->PIN ;
}

/**================================================================
* @Fn			-MCAL_GPIO_WritePin
* @brief 		-This API write the data on GPIOx specified pin according to pinNumber
* @param [in] 	-GPIOx 	  : where x can be (A .. E) to select the GPIO peripheral
* @param [in] 	-pinNumber: this parameter carries the pin to be written from the GPIOx, Pass value based on @ref GPIO_PIN_Define
* @param [in] 	-logic	  : this parameter carries the data(logic) to be written on the selected GPIOx pin, Pass value based on @ref GPIO_PIN_STATUS_Define
* @retval 		-N/A
* Note			-N/A
*/
void  MCAL_GPIO_WritePin(GPIO_t *GPIOx , uint8_t pinNumber , uint8_t logic)
{
	if(logic == (uint8_t)GPIO_PIN_STATUS_HIGH)
	{
		SET_BIT(GPIOx->PORT,pinNumber);
	}
	else
	{
		CLEAR_BIT(GPIOx->PORT,pinNumber);
	}
}

/**================================================================
* @Fn			-MCAL_GPIO_WritePort
* @brief 		-This API write the data on GPIOx pins
* @param [in] 	-GPIOx 	  : where x can be (A .. E) to select the GPIO peripheral
* @param [in] 	-portData : this parameter carries the data to be written on the GPIOx PORT
* @retval 		-N/A
* Note			-N/A
*/
void  MCAL_GPIO_WritePort(GPIO_t *GPIOx , uint8_t portData)
{
	GPIOx->PORT = (uint8_t)portData;
}
/**================================================================
* @Fn            -MCAL_GPIO_WritePartialPort
* @brief         -This API writes data to a specific range of bits within a GPIO port,
*                 while preserving the state of bits outside this range.
* @param [in]    -GPIOx: where x can be (A .. E) to select the GPIO peripheral
* @param [in]    -startBit: the starting bit position within the port where data begins to be written (0..15)
* @param [in]    -endBit: the ending bit position within the port where data stops being written (0..15)
* @param [in]    -portData: this parameter carries the data to be written to the specified range of bits
*                 within the GPIOx PORT. The least significant bits of portData correspond to the startBit
*                 position, and only the bits within the range defined by startBit and endBit are considered.
* @retval        -N/A
* Note           -The bits outside the specified range (startBit to endBit) in the GPIOx port are unaffected.
*                -If startBit is greater than endBit or if endBit is out of the port's bit range, the function
*                 will not perform any operation. It's assumed that startBit and endBit are within the 0..15 range.
*/

void MCAL_GPIO_WritePartialPort(GPIO_t *GPIOx, uint8_t startBit, uint8_t endBit, uint8_t portData) {
    if (startBit > endBit || endBit >= 8) {
        // Invalid range, return or handle error
        return;
    }

    // Step 1: Generate mask for the range to modify
    uint8_t mask = ((1UL << (endBit - startBit + 1)) - 1) << startBit;

    // Step 2: Align the input data to the correct start position
    uint8_t alignedData = ((uint8_t)portData << startBit) & mask;

    // Step 3 & 4: Preserve bits outside the range and modify bits within the range
    uint8_t finalData = (GPIOx->PORT & ~mask) | alignedData;

    // Write the finalData to the Output Data Register (ODR)
    GPIOx->PORT = finalData;
}
/**================================================================
* @Fn			-MCAL_GPIO_TogglePin
* @brief 		-This API toggles the logic(status)(data) of a specified GPIOx Pin
* @param [in] 	-GPIOx 	  : where x can be (A .. E) to select the GPIO peripheral
* @param [in] 	-pinNumber: this parameter carries the pin to be toggled from the GPIOx, Pass value based on @ref GPIO_PIN_Define
* @retval 		-N/A
* Note			-N/A
*/
void  MCAL_GPIO_TogglePin(GPIO_t *GPIOx , uint8_t pinNumber)
{
	TOGGLE_BIT(GPIOx->PORT,pinNumber);
}
