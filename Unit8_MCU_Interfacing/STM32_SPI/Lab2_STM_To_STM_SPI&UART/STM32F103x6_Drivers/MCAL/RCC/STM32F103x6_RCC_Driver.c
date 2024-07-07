/*
 * STM32_F103C6_RCC_Driver.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */
#include "STM32F103C6.h"
#include "STM32F103x6_RCC_Driver.h"

// Define prescalers
const uint16_t AHPPrescalar[16] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 4, 8, 16, 64, 128, 256, 512};
const uint8_t APBPrescalar[8] = {1, 1, 1, 1, 2, 4, 8, 16};
/*********************************
=========Helper Functions=========
*********************************/
void RCC_ExtractInfo(RCC_Config_t * Perix , uint32_t * BusType , uint32_t * Peripheral)
{
	*BusType = Perix->PeripheralNo & 0xC0000000; //Extract bus type first

	*Peripheral = Perix->PeripheralNo & 0x3FFFFFFF; //Extract peripheral bits
}
/*********************************
=========Supported APIs=========
*********************************/

/**
 * @Fn          - MCAL_RCC_EnablePeripheralClock
 * @brief       - Enables the clock for the specified peripheral.
 * @param [in]  - Perix: Pointer to RCC_Config_t structure that specifies the peripheral to be enabled.
 * @retval      - None
 * Note         - The peripheral must be a value of @ref RCC_Peripheral_Define
 */
void MCAL_RCC_EnablePeripheralClock(RCC_Config_t * Perix)
{
	uint32_t BusType;
	uint32_t Peripheral;
	RCC_ExtractInfo(Perix, &BusType, &Peripheral);
	switch (BusType)
	{
	case RCC_BUS_AHB:
		RCC->AHBENR |= Peripheral;
		break;
	case RCC_BUS_APB2:
		RCC->APB2ENR |= Peripheral;
		break;
	case RCC_BUS_APB1:
		RCC->APB1ENR |= Peripheral;
		break;
	}
}

/**================================================================
 * @Fn          - MCAL_RCC_DisablePeripheralClock
 * @brief       - Disables the clock for the specified peripheral.
 * @param [in]  - Perix: Pointer to RCC_Config_t structure that specifies the peripheral to be disabled.
 * @retval      - None
 * Note         - The peripheral must be a value of @ref RCC_Peripheral_Define
 */
void MCAL_RCC_DisablePeripheralClock(RCC_Config_t * Perix)
{
	uint32_t BusType;
	uint32_t Peripheral;
	RCC_ExtractInfo(Perix, &BusType, &Peripheral);
	switch (BusType)
	{
	case RCC_BUS_AHB:
		RCC->AHBENR &= ~Peripheral;
		break;
	case RCC_BUS_APB2:
		RCC->APB2ENR &= ~Peripheral;
		break;
	case RCC_BUS_APB1:
		RCC->APB1ENR &= ~Peripheral;
		break;
	}
}

/**================================================================
 * @Fn          - MCAL_RCC_GetSYSCLKFrequency
 * @brief       - Returns the system clock frequency.
 * @retval      - System clock frequency in Hz.
 * Note         - Assumes the system clock is configured to use the HSI.
 */
uint32_t MCAL_RCC_GetSYSCLKFrequency(void)
{
	//Assume we only working on HSI Clock
	return (uint32_t)(HSI_CLK);
}

/**================================================================
 * @Fn          - MCAL_RCC_GetHCLKFrequency
 * @brief       - Returns the AHB clock frequency.
 * @retval      - AHB clock frequency in Hz.
 */
uint32_t MCAL_RCC_GetHCLKFrequency(void)
{
	return MCAL_RCC_GetSYSCLKFrequency() / AHPPrescalar[(RCC->CFGR >> 4) & 0xF];
}

/**================================================================
 * @Fn          - MCAL_RCC_GetPCLK1Frequency
 * @brief       - Returns the APB1 clock frequency.
 * @retval      - APB1 clock frequency in Hz.
 */
uint32_t MCAL_RCC_GetPCLK1Frequency(void)
{
	return MCAL_RCC_GetHCLKFrequency() / APBPrescalar[(RCC->CFGR >> 8) & 0xF];
}

/**================================================================
 * @Fn          - MCAL_RCC_GetPCLK2Frequency
 * @brief       - Returns the APB2 clock frequency.
 * @retval      - APB2 clock frequency in Hz.
 */
uint32_t MCAL_RCC_GetPCLK2Frequency(void)
{
	return MCAL_RCC_GetHCLKFrequency() / APBPrescalar[(RCC->CFGR >> 11) & 0xF];
}

/**================================================================
 * @Fn          - MCAL_RCC_ResetPeripheral
 * @brief       - Resets the specified peripheral.
 * @param [in]  - Perix: Pointer to RCC_Config_t structure that specifies the peripheral to be reset.
 * @retval      - None
 * Note         - Only APB1 and APB2 peripherals can be reset.
 */
void MCAL_RCC_ResetPeripheral(RCC_Config_t * Perix)
{
	uint32_t BusType;
	uint32_t Peripheral;
	RCC_ExtractInfo(Perix, &BusType, &Peripheral);
	switch (BusType)
	{
	case RCC_BUS_APB2:
		RCC->APB2RSTR |= Peripheral;
		break;
	case RCC_BUS_APB1:
		RCC->APB1RSTR |= Peripheral;
		break;
	}
}
