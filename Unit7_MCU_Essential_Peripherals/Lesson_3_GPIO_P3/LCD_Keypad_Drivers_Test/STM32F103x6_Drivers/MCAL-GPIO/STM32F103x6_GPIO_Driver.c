/*
 * STM32_F103C6_GPIO_Driver.c
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */
#include "STM32F103x6_GPIO_Driver.h"

#include "Platform_Types.h"
#include <stdint.h>

#include "STM32F103C6.h"

uint8_t getShiftPosition(uint16_t pinNumber)
{
	switch(pinNumber)
	{
		case GPIO_PIN_0:
		{
			return 0;
			break;
		}
		case GPIO_PIN_1:
		{
			return 4;
			break;
		}
		case GPIO_PIN_2:
		{
			return 8;
			break;
		}
		case GPIO_PIN_3:
		{
			return 12;
			break;
		}
		case GPIO_PIN_4:
		{
			return 16;
			break;
		}
		case GPIO_PIN_5:
		{
			return 20;
			break;
		}
		case GPIO_PIN_6:
		{
			return 24;
			break;
		}
		case GPIO_PIN_7:
		{
			return 28;
			break;
		}
		case GPIO_PIN_8:
		{
			return 0;
			break;
		}
		case GPIO_PIN_9:
		{
			return 4;
			break;
		}
		case GPIO_PIN_10:
		{
			return 8;
			break;
		}
		case GPIO_PIN_11:
		{
			return 12;
			break;
		}
		case GPIO_PIN_12:
		{
			return 16;
			break;
		}
		case GPIO_PIN_13:
		{
			return 20;
			break;
		}
		case GPIO_PIN_14:
		{
			return 24;
			break;
		}
		case GPIO_PIN_15:
		{
			return 28;
			break;
		}
	}
	return 0; //Error STATE
}
/**================================================================
* @Fn			-MCAL_GPIO_Init
* @brief 		-This API initialize the GPIOx piny/s based on the pinConfig Parameter
* @param [in] 	-GPIOx 	  : where x can be (A .. E) to select the GPIO peripheral
* @param [in] 	-pinConfig: this parameter carry the configuration information to configure GPIOx(first parameter)
* @retval 		-N/A
* Note			- Stm32F103C6 MCU has GPIO A,B,C,D,E Modules,
* 				->But LQFP48 Package has only GPIO A,B,PART of C/D exported as external PINS from the MCU
*/				// You must set the GPIO_OUTPUT_MODE_SPEED in case of configuring pin as output
void MCAL_GPIO_Init(GPIO_t *GPIOx,pinConfig_t *pinConfig)
{
	vuint32_t * configReg = (pinConfig->pinNumber < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH ;
	uint8_t shiftPosition = getShiftPosition(pinConfig->pinNumber);
	uint8_t configVal = 0;
	if(pinConfig->pinMode < 4) //Normal input mode
	{
		switch(pinConfig->pinMode)
		{
			case GPIO_MODE_Analog:
			{
				configVal = 0b0000;
				break;
			}
			case GPIO_MODE_INPUT_FLO:
			{
				configVal = 0b0100;
				break;
			}
			case GPIO_MODE_INPUT_PU:
			{
				configVal = 0b1000;							//configure it as input
				SET_BIT(GPIOx->ODR,pinConfig->pinNumber);  //Enable PULL-UP
				break;
			}
			case GPIO_MODE_INPUT_PD:
			{
				configVal = 0b1000;							 //configure it as input
				CLEAR_BIT(GPIOx->ODR,pinConfig->pinNumber); //Enable PULL-Down
				break;
			}
		}
	}
	else if(pinConfig->pinMode == GPIO_MODE_AF_INPUT)
	{
		configVal = 0b0100; //Set as floating input (from TRM)
	}
	else //OUTPUT
	{
		configVal = ((pinConfig->pinMode - 4) << 2) | (pinConfig->outputModeSpeed & 0x0F);
	}
	*configReg = (*configReg & (~(0b1111 << shiftPosition))) | (configVal << shiftPosition);
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
    if(GPIOx == GPIOA) {
    	SET_BIT(RCC->APB2RSTR,2);
    	CLEAR_BIT(RCC->APB2RSTR,2);
    }
    else if(GPIOx == GPIOB) {
    	SET_BIT(RCC->APB2RSTR,3);
    	CLEAR_BIT(RCC->APB2RSTR,3);
    }
    else if(GPIOx == GPIOC) {
    	SET_BIT(RCC->APB2RSTR,4);
    	CLEAR_BIT(RCC->APB2RSTR,4);
    }
    else if(GPIOx == GPIOD) {
    	SET_BIT(RCC->APB2RSTR,5);
    	CLEAR_BIT(RCC->APB2RSTR,5);
    }
    else if(GPIOx == GPIOE) {
    	SET_BIT(RCC->APB2RSTR,6);
    	CLEAR_BIT(RCC->APB2RSTR,6);
    }
}


/**================================================================
* @Fn			-MCAL_GPIO_ReadPin
* @brief 		-This API reads a specific pin(pinNumber) from the GPIOx
* @param [in] 	-GPIOx 	  : where x can be (A .. E) to select the GPIO peripheral
* @param [in] 	-pinNumber: this parameter carries the pin to be read from the GPIOx, Pass value based on @ref GPIO_PIN_Define
* @retval 		-The logic(status)(data) of the specified pin, which can be a value of @ref GPIO_PIN_STATUS_Define
* Note			-N/A
*/
uint8_t MCAL_GPIO_ReadPin(GPIO_t *GPIOx , uint16_t pinNumber)
{
	if((READ_BIT(GPIOx->IDR , pinNumber)) != GPIO_PIN_STATUS_LOW)
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
	return (uint16_t)GPIOx->IDR;
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
void  MCAL_GPIO_WritePin(GPIO_t *GPIOx , uint16_t pinNumber , uint8_t logic)
{
	if(logic == (uint8_t)GPIO_PIN_STATUS_HIGH)
	{
		SET_BIT(GPIOx->ODR,pinNumber);
	}
	else
	{
		CLEAR_BIT(GPIOx->ODR,pinNumber);
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
void  MCAL_GPIO_WritePort(GPIO_t *GPIOx , uint16_t portData)
{
	GPIOx->ODR = (uint32_t)portData;
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

void MCAL_GPIO_WritePartialPort(GPIO_t *GPIOx, uint8_t startBit, uint8_t endBit, uint16_t portData) {
    if (startBit > endBit || endBit >= 16) {
        // Invalid range, return or handle error
        return;
    }

    // Step 1: Generate mask for the range to modify
    uint32_t mask = ((1UL << (endBit - startBit + 1)) - 1) << startBit;

    // Step 2: Align the input data to the correct start position
    uint32_t alignedData = ((uint32_t)portData << startBit) & mask;

    // Step 3 & 4: Preserve bits outside the range and modify bits within the range
    uint32_t finalData = (GPIOx->ODR & ~mask) | alignedData;

    // Write the finalData to the Output Data Register (ODR)
    GPIOx->ODR = finalData;
}
/**================================================================
* @Fn			-MCAL_GPIO_TogglePin
* @brief 		-This API toggles the logic(status)(data) of a specified GPIOx Pin
* @param [in] 	-GPIOx 	  : where x can be (A .. E) to select the GPIO peripheral
* @param [in] 	-pinNumber: this parameter carries the pin to be toggled from the GPIOx, Pass value based on @ref GPIO_PIN_Define
* @retval 		-N/A
* Note			-N/A
*/
void  MCAL_GPIO_TogglePin(GPIO_t *GPIOx , uint16_t pinNumber)
{
	TOGGLE_BIT(GPIOx->ODR,pinNumber);
}

/**================================================================
* @Fn			-MCAL_GPIO_LockPin
* @brief 		-This API Locks(Freezes) the configuration of a specified GPIOx Pin
* @param [in] 	-GPIOx 	  : where x can be (A .. E) to select the GPIO peripheral
* @param [in] 	-pinNumber: this parameter carries the pin to be toggled from the GPIOx, Pass value based on @ref GPIO_PIN_Define
* @retval 		-N/A
* Note			-N/A
*/
uint8_t  MCAL_GPIO_LockPin(GPIO_t *GPIOx,uint16_t pinNumber)
{
    uint8_t status;
    SET_BIT(GPIOx->LCKR,pinNumber);
    /*Write 1*/
    SET_BIT(GPIOx->LCKR,GPIO_LOCK_PIN);
    /*Write 0*/
    CLEAR_BIT(GPIOx->LCKR,GPIO_LOCK_PIN);
    /*Write 1*/
    SET_BIT(GPIOx->LCKR,GPIO_LOCK_PIN);
    /*Read 0*/
    status = READ_BIT(GPIOx->LCKR,GPIO_LOCK_PIN);
    /*Read 1 if successful*/
    status = READ_BIT(GPIOx->LCKR,GPIO_LOCK_PIN);

    return status;
}
