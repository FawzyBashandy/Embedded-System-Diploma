/*
 * STM32_F103C6_RCC_Driver.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */

#ifndef STM32_F103C6_RCC_DRIVER_H_
#define STM32_F103C6_RCC_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include <BitMath.h>
#include <Platform_Types.h>
#include <STM32F103C6.h>
#include <stdint.h>

//-----------------------------
//General Macros
//-----------------------------

#define RCC_BUS_AHB   (0b01 << 30) //Where bits 30 , 31 are reserved for any clk register
#define RCC_BUS_APB1  (0b10 << 30)
#define RCC_BUS_APB2  (0b11 << 30)

#define HSI_CLK 	  8000000UL

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint32_t PeripheralNo;			    /*Specify the peripheral to be configured
					   	  	  	  	  	  This parameter must be a value of @ref RCC_Peripheral_Define*/

	uint8_t Action;						/*Specify the action IN CASE OF CLK configuration only
					   	  	  	  	  	  This parameter must be a value of @ref RCC_ACTION_Define*/
}RCC_Config_t;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref RCC_Peripheral_Define

// AHB Peripherals
#define RCC_PERIPHERAL_DMA1     (RCC_BUS_AHB  | (1 << 0))
#define RCC_PERIPHERAL_DMA2     (RCC_BUS_AHB  | (1 << 1))
#define RCC_PERIPHERAL_SRAM     (RCC_BUS_AHB  | (1 << 2))
#define RCC_PERIPHERAL_FLITF    (RCC_BUS_AHB  | (1 << 4))
#define RCC_PERIPHERAL_CRC      (RCC_BUS_AHB  | (1 << 6))
#define RCC_PERIPHERAL_FSMC     (RCC_BUS_AHB  | (1 << 8))
#define RCC_PERIPHERAL_SDIO     (RCC_BUS_AHB  | (1 << 10))

// APB2 Peripherals
#define RCC_PERIPHERAL_AFIO     (RCC_BUS_APB2 | (1 << 0))
#define RCC_PERIPHERAL_IOPA     (RCC_BUS_APB2 | (1 << 2))
#define RCC_PERIPHERAL_IOPB     (RCC_BUS_APB2 | (1 << 3))
#define RCC_PERIPHERAL_IOPC     (RCC_BUS_APB2 | (1 << 4))
#define RCC_PERIPHERAL_IOPD     (RCC_BUS_APB2 | (1 << 5))
#define RCC_PERIPHERAL_IOPE     (RCC_BUS_APB2 | (1 << 6))
#define RCC_PERIPHERAL_IOPF     (RCC_BUS_APB2 | (1 << 7))
#define RCC_PERIPHERAL_IOPG     (RCC_BUS_APB2 | (1 << 8))
#define RCC_PERIPHERAL_ADC1     (RCC_BUS_APB2 | (1 << 9))
#define RCC_PERIPHERAL_ADC2     (RCC_BUS_APB2 | (1 << 10))
#define RCC_PERIPHERAL_TIM1     (RCC_BUS_APB2 | (1 << 11))
#define RCC_PERIPHERAL_SPI1     (RCC_BUS_APB2 | (1 << 12))
#define RCC_PERIPHERAL_TIM8     (RCC_BUS_APB2 | (1 << 13))
#define RCC_PERIPHERAL_USART1   (RCC_BUS_APB2 | (1 << 14))
#define RCC_PERIPHERAL_ADC3     (RCC_BUS_APB2 | (1 << 15))
#define RCC_PERIPHERAL_TIM9     (RCC_BUS_APB2 | (1 << 19))
#define RCC_PERIPHERAL_TIM10    (RCC_BUS_APB2 | (1 << 20))
#define RCC_PERIPHERAL_TIM11    (RCC_BUS_APB2 | (1 << 21))

// APB1 Peripherals
#define RCC_PERIPHERAL_TIM2     (RCC_BUS_APB1 | (1 << 0))
#define RCC_PERIPHERAL_TIM3     (RCC_BUS_APB1 | (1 << 1))
#define RCC_PERIPHERAL_TIM4     (RCC_BUS_APB1 | (1 << 2))
#define RCC_PERIPHERAL_TIM5     (RCC_BUS_APB1 | (1 << 3))
#define RCC_PERIPHERAL_TIM6     (RCC_BUS_APB1 | (1 << 4))
#define RCC_PERIPHERAL_TIM7     (RCC_BUS_APB1 | (1 << 5))
#define RCC_PERIPHERAL_TIM12    (RCC_BUS_APB1 | (1 << 6))
#define RCC_PERIPHERAL_TIM13    (RCC_BUS_APB1 | (1 << 7))
#define RCC_PERIPHERAL_TIM14    (RCC_BUS_APB1 | (1 << 8))
#define RCC_PERIPHERAL_WWDG     (RCC_BUS_APB1 | (1 << 11))
#define RCC_PERIPHERAL_SPI2     (RCC_BUS_APB1 | (1 << 12))
#define RCC_PERIPHERAL_SPI3     (RCC_BUS_APB1 | (1 << 13))
#define RCC_PERIPHERAL_USART2   (RCC_BUS_APB1 | (1 << 14))
#define RCC_PERIPHERAL_USART3   (RCC_BUS_APB1 | (1 << 15))
#define RCC_PERIPHERAL_UART4    (RCC_BUS_APB1 | (1 << 16))
#define RCC_PERIPHERAL_UART5    (RCC_BUS_APB1 | (1 << 17))
#define RCC_PERIPHERAL_I2C1     (RCC_BUS_APB1 | (1 << 18))
#define RCC_PERIPHERAL_I2C2     (RCC_BUS_APB1 | (1 << 19))
#define RCC_PERIPHERAL_USB      (RCC_BUS_APB1 | (1 << 20))
#define RCC_PERIPHERAL_CAN      (RCC_BUS_APB1 | (1 << 21))
#define RCC_PERIPHERAL_BKP      (RCC_BUS_APB1 | (1 << 27))
#define RCC_PERIPHERAL_PWR      (RCC_BUS_APB1 | (1 << 28))

//@ref RCC_ACTION_Define

#define RCC_ACTION_ENABLECLK	0	//Enable clk for specified peripheral
#define RCC_ACTION_DISABLECLK	1	//Disable clk for specified peripheral
#define RCC_ACTION_RESET		2	//USE For RESET ONLY
/*
* ===============================================
* APIs Supported by "MCAL RCC DRIVER"
* ===============================================
*/
void MCAL_RCC_EnablePeripheralClock(RCC_Config_t * Perix);
void MCAL_RCC_DisablePeripheralClock(RCC_Config_t * Perix);
uint32_t MCAL_RCC_GetSYSCLKFrequency(void);// Retrieves the system clock frequency.
uint32_t MCAL_RCC_GetHCLKFrequency(void);// Retrieves the AHB clock frequency.
uint32_t MCAL_RCC_GetPCLK1Frequency(void);//: Retrieves the APB1 clock frequency.
uint32_t MCAL_RCC_GetPCLK2Frequency(void);// Retrieves the APB2 clock frequency.
void MCAL_RCC_ResetPeripheral(RCC_Config_t * Perix);//: Resets a specific peripheral.

#endif /* STM32_F103C6_RCC_DRIVER_H_ */
