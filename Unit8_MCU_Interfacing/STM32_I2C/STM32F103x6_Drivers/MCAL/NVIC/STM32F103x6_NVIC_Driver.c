/*
**************************************************************************************************************************
* file         : stm32f103x6_NVIC.c
* brief        : This file contains functions to configure the NVIC for the stm32f103x6 cortex-m3.
* Author       : Fawzy Bashandy
* Created on   : Feb 20, 2024
**************************************************************************************************************************
*/

/*
*===============================================
*                   Includes
*===============================================
*/

#include <NVIC/STM32F103x6_NVIC_Driver.h>
#include <BitMath.h>


/**************************************************************************************************************************
*===============================================
*            APIs functions definitions
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
void MCAL_NVIC_EnableIRQ(uint8 IRQn)
{
    uint8 register_index = IRQn / 32;

    SET_BIT(NVIC_ISER_BASE[register_index], (IRQn % 32));
}

/*
======================================================================================================================
* @Func_name    :   MCAL_NVIC_Disable_IRQ
* @brief        :   Disables the interrupt with the specified interrupt request number.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   none.
* Note          :   You need to write one on the required IRQ bit to clear it and disable the interrupt.
*               :   When you write on this register using the traditional |= method you will disable all the interrupts
*               :   in this register as writing one on the required IRQ bit will disable it.
======================================================================================================================
*/
void MCAL_NVIC_DisableIRQ(uint8 IRQn)
{
    uint8 register_index = IRQn / 32;

    NVIC_ICER_BASE[register_index]= 1 << (IRQn % 32);
}

/*
=====================================================================================================================
* @Func_name    :   MCAL_NVIC_GetPendingIRQ
* @brief        :   Return true (IRQ-Number) if IRQn is pending.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   Return true (IRQ-Number) if IRQn is pending and zero otherwise.
* Note          :   none.
=====================================================================================================================
*/
uint8 MCAL_NVIC_GetPendingIRQ (uint8 IRQn)
{
    uint8 register_index = IRQn / 32;

    return READ_BIT(NVIC_ISPR_BASE[register_index], (IRQn % 32));
}

/*
=====================================================================================================================
* @Func_name    :   MCAL_NVIC_SetPendingIRQ
* @brief        :   Set the IRQ number to be pending.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   none.
* Note          :   none.
=====================================================================================================================
*/
void MCAL_NVIC_SetPendingIRQ (uint8 IRQn)
{
    uint8 register_index = IRQn / 32;

    SET_BIT(NVIC_ISPR_BASE[register_index], (IRQn % 32));
}

/*
=====================================================================================================================
* @Func_name    :   MCAL_NVIC_ClearPendingIRQ
* @brief        :   Clear the IRQ number pending status.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   none.
* Note          :   The pending request is cleared by writing one the bit.
=====================================================================================================================
*/
void MCAL_NVIC_ClearPendingIRQ (uint8 IRQn)
{
    uint8 register_index = IRQn / 32;

    NVIC_ICPR_BASE[register_index] = 1 <<  (IRQn % 32);
}

/*
======================================================================================================================
* @Func_name    :   MCAL_NVIC_GetActive
* @brief        :   Return the IRQ number of the active interrupt.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   Return true (IRQ-Number) if IRQn is active and zero otherwise.
* Note          :   none.
======================================================================================================================
*/
uint8 MCAL_NVIC_GetActive (uint8 IRQn)
{
    uint8 register_index = IRQn / 32;

    return READ_BIT(NVIC_IABR_BASE[register_index], (IRQn % 32));
}

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
void MCAL_NVIC_SetPriority (uint8 IRQn, uint8 priority)
{
    uint8 register_index = IRQn / 4, shift;
    shift = (((IRQn % 4) * 8) + 4);

    /*Clear the bits*/
    NVIC_IPR_BASE[register_index] &= ~(0xF << shift);

    /*Set the new priority value*/
    NVIC_IPR_BASE[register_index] |= (priority & 0xF) << shift;
}

/*
======================================================================================================================
* @Func_name    :   MCAL_NVIC_GetPriority
* @brief        :   Return the priority of the IRQ number.
* @param [in]   :   IRQn: specifies the interrupt request number must be a value of @ref NVIC_MODULE_IVT_INDEX
* @return_value :   Priority level of the IRQ.
* Note          :   none.
======================================================================================================================
*/
uint8 MCAL_NVIC_GetPriority (uint8 IRQn)
{
    uint8 register_index = IRQn / 4, priority, shift;
    shift = (((IRQn % 4) * 8) + 4);
    priority = (NVIC_IPR_BASE[register_index] & (0xF << shift)) >> shift;

    return priority;
}
