/*
 * STM32_F103C6_RCC_Driver.h
 *
 *  Created on: Feb 30, 2024
 *      Author: Fawzy Bashandy
 */
/**************************************************************************************************************************
* note: This module is intended for use with the STM32F103xx microcontroller series, but may be adapted for use with
* other compatible processors.
**************************************************************************************************************************
*/
#ifndef STM32_F103x6_NVIC_DRIVER_H_
#define STM32_F103x6_NVIC_DRIVER_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include <STM32F103C6.h>
#include <Platform_Types.h>

/**************************************************************************************************************************
*=========================================================
*         Macros Configuration References
*=========================================================
*/

/*-------------------@ref NVIC_MODULE_IVT_INDEX---------------------*/
#define NVIC_WWDG_IVT_INDEX                     0
#define NVIC_PVD_IVT_INDEX                      1
#define NVIC_TAMPER_IVT_INDEX                   2
#define NVIC_RTC_IVT_INDEX                      3
#define NVIC_FLASH_IVT_INDEX                    4
#define NVIC_RCC_IVT_INDEX                      5
#define NVIC_EXTI0_IVT_INDEX                    6
#define NVIC_EXTI1_IVT_INDEX                    7
#define NVIC_EXTI2_IVT_INDEX                    8
#define NVIC_EXTI3_IVT_INDEX                    9
#define NVIC_EXTI4_IVT_INDEX                    10
#define NVIC_DMA1_Channel1_IVT_INDEX            11
#define NVIC_DMA1_Channel2_IVT_INDEX            12
#define NVIC_DMA1_Channel3_IVT_INDEX            13
#define NVIC_DMA1_Channel4_IVT_INDEX            14
#define NVIC_DMA1_Channel5_IVT_INDEX            15
#define NVIC_DMA1_Channel6_IVT_INDEX            16
#define NVIC_DMA1_Channel7_IVT_INDEX            17
#define NVIC_ADC1_2_IVT_INDEX                   18
#define NVIC_USB_HP_CAN_TX_IVT_INDEX            19
#define NVIC_USB_LP_CAN_RX0_IVT_INDEX           20
#define NVIC_CAN_RX1_IVT_INDEX                  21
#define NVIC_CAN_SCE_IVT_INDEX                  22
#define NVIC_EXTI9_5_IVT_INDEX                  23
#define NVIC_TIM1_BRK_TIM9_IVT_INDEX            24
#define NVIC_TIM1_UP_TIM10_IVT_INDEX            25
#define NVIC_TIM1_TRG_COM_TIM11_IVT_INDEX       26
#define NVIC_TIM1_CC_IVT_INDEX                  27
#define NVIC_TIM2_IVT_INDEX                     28
#define NVIC_TIM3_IVT_INDEX                     29
#define NVIC_TIM4_IVT_INDEX                     30
#define NVIC_I2C1_EV_IVT_INDEX                  31
#define NVIC_I2C1_ER_IVT_INDEX                  32
#define NVIC_I2C2_EV_IVT_INDEX                  33
#define NVIC_I2C2_ER_IVT_INDEX                  34
#define NVIC_SPI1_IVT_INDEX                     35
#define NVIC_SPI2_IVT_INDEX                     36
#define NVIC_USART1_IVT_INDEX                   37
#define NVIC_USART2_IVT_INDEX                   38
#define NVIC_USART3_IVT_INDEX                   39
#define NVIC_EXTI15_10_IVT_INDEX                40
#define NVIC_RTCAlarm_IVT_INDEX                 41
#define NVIC_USBWakeUp_IVT_INDEX                42
#define NVIC_TIM8_BRK_TIM12_IVT_INDEX           43
#define NVIC_TIM8_UP_TIM13_IVT_INDEX            44
#define NVIC_TIM8_TRG_COM_TIM14_IVT_INDEX       45
#define NVIC_TIM8_CC_IVT_INDEX                  46
#define NVIC_ADC3_IVT_INDEX                     47
#define NVIC_FSMC_IVT_INDEX                     48
#define NVIC_SDIO_IVT_INDEX                     49
#define NVIC_TIM5_IVT_INDEX                     50
#define NVIC_SPI3_IVT_INDEX                     51
#define NVIC_UART4_IVT_INDEX                    52
#define NVIC_UART5_IVT_INDEX                    53
#define NVIC_TIM6_IVT_INDEX                     54
#define NVIC_TIM7_IVT_INDEX                     55
#define NVIC_DMA2_Channel1_IVT_INDEX            56
#define NVIC_DMA2_Channel2_IVT_INDEX            57
#define NVIC_DMA2_Channel3_IVT_INDEX            58
#define NVIC_DMA2_Channel4_5_IVT_INDEX          59

/*-------------------@ref NVIC_PRIORITY_DEFINE---------------------*/
#define NVIC_PRIORITY_0       0    /*The Highest possible priority*/
#define NVIC_PRIORITY_1       1
#define NVIC_PRIORITY_2       2
#define NVIC_PRIORITY_3       3
#define NVIC_PRIORITY_4       4
#define NVIC_PRIORITY_5       5
#define NVIC_PRIORITY_6       6
#define NVIC_PRIORITY_7       7
#define NVIC_PRIORITY_8       8
#define NVIC_PRIORITY_9       9
#define NVIC_PRIORITY_10      10
#define NVIC_PRIORITY_11      11
#define NVIC_PRIORITY_12      12
#define NVIC_PRIORITY_13      13
#define NVIC_PRIORITY_14      14
#define NVIC_PRIORITY_15      15    /*The Lowest possible priority*/

/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL NVIC DRIVER"
*===============================================
*/

/*
======================================================================================================================
* @Func_name    :   MCAL_NVIC_Enable_IRQ
* @brief        :   Enables the interrupt with the specified interrupt request number.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   none.
* Note          :   none.
======================================================================================================================
*/
void MCAL_NVIC_EnableIRQ(uint8 IRQn);

/*
======================================================================================================================
* @Func_name    :   MCAL_NVIC_Disable_IRQ
* @brief        :   Disables the interrupt with the specified interrupt request number.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   none.
* Note          :   You need to write one on the required IRQ bit to clear it and disable the interrupt.
======================================================================================================================
*/
void MCAL_NVIC_DisableIRQ(uint8 IRQn);

/*
=====================================================================================================================
* @Func_name    :   MCAL_NVIC_GetPendingIRQ
* @brief        :   Return true (IRQ-Number) if IRQn is pending.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   Return true (IRQ-Number) if IRQn is pending and zero otherwise.
* Note          :   none.
=====================================================================================================================
*/
uint8 MCAL_NVIC_GetPendingIRQ (uint8 IRQn);

/*
=====================================================================================================================
* @Func_name    :   MCAL_NVIC_SetPendingIRQ
* @brief        :   Set the IRQ number to be pending.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   none.
* Note          :   none.
=====================================================================================================================
*/
void MCAL_NVIC_SetPendingIRQ (uint8 IRQn);

/*
=====================================================================================================================
* @Func_name    :   MCAL_NVIC_ClearPendingIRQ
* @brief        :   Clear the IRQ number pending status.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   none.
* Note          :   The pending request is cleared by writing one the bit.
=====================================================================================================================
*/
void MCAL_NVIC_ClearPendingIRQ (uint8 IRQn);

/*
======================================================================================================================
* @Func_name    :   MCAL_NVIC_GetActive
* @brief        :   Return the IRQ number of the active interrup.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   Return true (IRQ-Number) if IRQn is active and zero otherwise.
* Note          :   none.
======================================================================================================================
*/
uint8 MCAL_NVIC_GetActive (uint8 IRQn);

/*
======================================================================================================================
* @Func_name    :   MCAL_NVIC_SetPriority
* @brief        :   Set priority for IRQn.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @param [in]   :   priority: specifies the priority of the IRQ must be a value of @ref NVIC_PRIORITY_DEFINE.
* @return_value :   none.
* Note          :   none.
======================================================================================================================
*/
void MCAL_NVIC_SetPriority (uint8 IRQn, uint8 priority);

/*
======================================================================================================================
* @Func_name    :   MCAL_NVIC_GetPriority
* @brief        :   Return the priorityof the IRQ number.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   Priority level of the IRQ.
* Note          :   none.
======================================================================================================================
*/
uint8 MCAL_NVIC_GetPriority (uint8 IRQn);

#endif
