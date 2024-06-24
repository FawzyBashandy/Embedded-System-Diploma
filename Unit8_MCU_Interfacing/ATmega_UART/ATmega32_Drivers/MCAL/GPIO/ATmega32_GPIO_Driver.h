/*
 * ATmega32_GPIO_Driver.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */

#ifndef ATMEGA32_GPIO_DRIVER_H_
#define ATMEGA32_GPIO_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include "BitMath.h"
#include "Platform_Types.h"
#include "ATmega32.h"
#include <stdint.h>
//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint16_t pinNumber;			    /*Specify the pin that will be configured
					   	  	  	  	  This parameter must be a value of @ref GPIO_PIN_Define*/

	uint8_t  pinMode;   			/*Specify the required operating mode of the selected pin
						  	  	  	  This Parameter must be a value of @ref GPIO_MODE_Define*/
}pinConfig_t;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref GPIO_PIN_Define
#define GPIO_PIN_0				0 	//Write to select pin 0
#define GPIO_PIN_1				1	//Write to select pin 1
#define GPIO_PIN_2				2 	//Write to select pin 2
#define GPIO_PIN_3				3	//Write to select pin 3
#define GPIO_PIN_4				4	//Write to select pin 4
#define GPIO_PIN_5				5	//Write to select pin 5
#define GPIO_PIN_6				6	//Write to select pin 6
#define GPIO_PIN_7				7 	//Write to select pin 7
#define GPIO_PIN_ALL			16	//Write to select all pins on the selected port

//@ref GPIO_MODE_Define
#define GPIO_MODE_INPUT_FLO			1			//Write to Configure pin as Floating Input
#define GPIO_MODE_INPUT_PU			2			//Write to Configure pin as Pull-up Input
#define GPIO_MODE_OUTPUT			4			//Write to Configure pin as Push-Pull Output



//@ref GPIO_PIN_STATUS_Define
#define GPIO_PIN_STATUS_HIGH        1			//Indicating logical 1 or high or vcc
#define GPIO_PIN_STATUS_LOW			0			//Indicating logical 0 or Low or gnd

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
void MCAL_GPIO_Init(GPIO_t *GPIOx,pinConfig_t *pinConfig);
void MCAL_GPIO_Reset(GPIO_t *GPIOx);

uint8_t  MCAL_GPIO_ReadPin(GPIO_t *GPIOx , uint8_t pinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_t *GPIOx);

void  MCAL_GPIO_WritePin(GPIO_t *GPIOx , uint8_t pinNumber , uint8_t logic);
void  MCAL_GPIO_WritePort(GPIO_t *GPIOx , uint8_t portData);
void  MCAL_GPIO_WritePartialPort(GPIO_t *GPIOx ,uint8_t startBit , uint8_t endBit, uint8_t portData);

void  MCAL_GPIO_TogglePin(GPIO_t *GPIOx , uint8_t pinNumber);

#endif /* ATMEGA32_GPIO_DRIVER_H_ */
