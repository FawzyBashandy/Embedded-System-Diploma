/*
 * STM32_F103C6_GPIO_Driver.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */

#ifndef STM32_F103C6_GPIO_DRIVER_H_
#define STM32_F103C6_GPIO_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103C6.h"
#include "Platform_Types.h"
#include <stdint.h>

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint16_t pinNumber;			    /*Specify the pin that will be configured
					   	  	  	  	  This paramerter must be a value of @ref GPIO_PIN_Define*/

	uint8_t  pinMode;   			/*Specify the required operating mode of the selected pin
						  	  	  	  This Parameter must be a value of @ref GPIO_MODE_Define*/

	uint8_t  outputModeSpeed;    	/*Specify the required speed in case of pin is chosen to be output
							   	      This Parameter must be a value of @ref GPIO_OUTPUT_SPEED_Define*/
}pinConfig_t;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref GPIO_PIN_Define
#define GPIO_PIN_0				0x00000001UL 	//Write to select pin 0
#define GPIO_PIN_1				0x00000002UL	//Write to select pin 1
#define GPIO_PIN_2				0x00000004UL 	//Write to select pin 2
#define GPIO_PIN_3				0x00000008UL	//Write to select pin 3
#define GPIO_PIN_4				0x00000010UL	//Write to select pin 4
#define GPIO_PIN_5				0x00000020UL	//Write to select pin 5
#define GPIO_PIN_6				0x00000040UL	//Write to select pin 6
#define GPIO_PIN_7				0x00000080UL 	//Write to select pin 7
#define GPIO_PIN_8				0x00000100UL	//Write to select pin 8
#define GPIO_PIN_9				0x00000200UL	//Write to select pin 9
#define GPIO_PIN_10				0x00000400UL	//Write to select pin 10
#define GPIO_PIN_11				0x00000800UL	//Write to select pin 11
#define GPIO_PIN_12				0x00001000UL	//Write to select pin 12
#define GPIO_PIN_13				0x00002000UL	//Write to select pin 13
#define GPIO_PIN_14				0x00004000UL	//Write to select pin 14
#define GPIO_PIN_15				0x00008000UL	//Write to select pin 15


//@ref GPIO_MODE_Define
#define GPIO_MODE_Analog			0			//Write to Configure pin as Analog
#define GPIO_MODE_INPUT_FLO			1			//Write to Configure pin as Floating Input
#define GPIO_MODE_INPUT_PU			2			//Write to Configure pin as Pull-up Input
#define GPIO_MODE_INPUT_PD			3			//Write to Configure pin as Pull-down Input
#define GPIO_MODE_OUTPUT_PP			4			//Write to Configure pin as Push-Pull Output
#define GPIO_MODE_OUTPUT_OD			5			//Write to Configure pin as Open-Drain Output
#define GPIO_MODE_AF_OUTPUT_PP		6			//Write to Configure pin as Push-Pull Alternative function Output
#define GPIO_MODE_AF_OUTPUT_OD		7			//Write to Configure pin as Open-Drain Alternative function Output
#define GPIO_MODE_AF_INPUT			8			//Write to Configure pin as Push-Pull Alternative function Output

//@ref GPIO_OUTPUT_SPEED_Define

#define GPIO_OUTPUT_SPEED_10MHZ		1			//Write to configure output pin's speed as 10MHZ
#define GPIO_OUTPUT_SPEED_2MHZ      2			//Write to configure output pin's speed as 2MHZ
#define GPIO_OUTPUT_SPEED_50MHZ		3			//Write to configure output pin's speed as 50MHZ

//@ref GPIO_PIN_STATUS_Define
#define GPIO_PIN_STATUS_HIGH        1			//Indicating logical 1 or high or vcc
#define GPIO_PIN_STATUS_LOW			0			//Indicating logical 0 or Low or gnd

//@ref GPIO_STATUS_Define
#define GPIO_STATUS_OK      	    1			//Indicating Successful operation
#define GPIO_STATUS_ERROR			0			//Indicating Error in operation


#define GPIO_LOCK_PIN				16			//Used for Locking conf of a pin
/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
void MCAL_GPIO_Init(GPIO_t *GPIOx,pinConfig_t *pinConfig);
void MCAL_GPIO_Reset(GPIO_t *GPIOx);

uint8_t  MCAL_GPIO_ReadPin(GPIO_t *GPIOx , uint16_t pinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_t *GPIOx);

void  MCAL_GPIO_WritePin(GPIO_t *GPIOx , uint16_t pinNumber , uint8_t logic);
void  MCAL_GPIO_WritePort(GPIO_t *GPIOx , uint16_t portData);

void  MCAL_GPIO_TogglePin(GPIO_t *GPIOx , uint16_t pinNumber);

uint8_t  MCAL_GPIO_LockPin(GPIO_t *GPIOx,uint16_t pinNumber);
#endif /* STM32_F103C6_GPIO_DRIVER_H_ */
