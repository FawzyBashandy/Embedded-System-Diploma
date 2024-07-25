/*
 * STM32_F103C6_USART_Driver.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */
#include <STM32F103C6.h>
#include <USART/STM32F103x6_USART_Driver.h>
#include <RCC/STM32F103x6_RCC_Driver.h>
#include <NVIC/STM32F103x6_NVIC_Driver.h>

#include "../GPIO/STM32F103x6_GPIO_Driver.h"
USART_Config_t * Global_USARTcfg[3];

void (* p_IRQ_callback_USART1[11] )(void);
void (* p_IRQ_callback_USART2[11] )(void);
void (* p_IRQ_callback_USART3[11] )(void);

/*********************************
=========Helper Functions=========
*********************************/
void UART_BRR_Calculations(USART_Config_t * USARTx, uint32_t *DIVMantissa, uint32_t *DIVFraction)
{

	uint32_t Fclk,USARTDIV_MUL100,DIVMantissa_MUL100;
	if(USARTx->USARTx == USART1)
	{
		Fclk = MCAL_RCC_GetPCLK2Frequency();
	}
	else
	{
		Fclk = MCAL_RCC_GetPCLK1Frequency();
	}
	USARTDIV_MUL100 = (100*Fclk/(16 * USARTx->BaudRate));

	*DIVMantissa = (uint32_t)(USARTDIV_MUL100 / 100);
	DIVMantissa_MUL100 = *DIVMantissa * 100;
	*DIVFraction = ((USARTDIV_MUL100 - DIVMantissa_MUL100)*16)/100;
}

void ConfigureMapped_GPIO_PINS(USART_Config_t * USARTx)
{
    // Recommended configuration for IO_Pins:
    // USARTx_TX -> Full duplex (Alternate function push-pull)
    // USARTx_RX -> Full duplex (Input floating / Input pull-up) refer to page 167 in TRM
    pinConfig_t cfg;

    if (USARTx->USARTx == USART1)
    {
        Global_USARTcfg[0] = USARTx;
        switch (USARTx->TxRx_Mode)
        {
            case USART_TxRxMode_Transmiting:
                cfg.pinNumber = GPIO_PIN_9;
                cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
                cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
                MCAL_GPIO_Init(GPIOA, &cfg);
                break;
            case USART_TxRxMode_Receiving:
                cfg.pinNumber = GPIO_PIN_10;
                cfg.pinMode = GPIO_MODE_INPUT_FLO;
                MCAL_GPIO_Init(GPIOA, &cfg);
                break;
            default:
                cfg.pinNumber = GPIO_PIN_9;
                cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
                cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
                MCAL_GPIO_Init(GPIOA, &cfg);

                cfg.pinNumber = GPIO_PIN_10;
                cfg.pinMode = GPIO_MODE_INPUT_FLO;
                MCAL_GPIO_Init(GPIOA, &cfg);
                break;
        }
    }
    else if (USARTx->USARTx == USART2)
    {
        Global_USARTcfg[1] = USARTx;
        switch (USARTx->TxRx_Mode)
        {
            case USART_TxRxMode_Transmiting:
                cfg.pinNumber = GPIO_PIN_2;
                cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
                cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
                MCAL_GPIO_Init(GPIOA, &cfg);
                break;
            case USART_TxRxMode_Receiving:
                cfg.pinNumber = GPIO_PIN_3;
                cfg.pinMode = GPIO_MODE_INPUT_FLO;
                MCAL_GPIO_Init(GPIOA, &cfg);
                break;
            default:
                cfg.pinNumber = GPIO_PIN_2;
                cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
                cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
                MCAL_GPIO_Init(GPIOA, &cfg);

                cfg.pinNumber = GPIO_PIN_3;
                cfg.pinMode = GPIO_MODE_INPUT_FLO;
                MCAL_GPIO_Init(GPIOA, &cfg);
                break;
        }
    }
    else // USART3
    {
        Global_USARTcfg[2] = USARTx;
        switch (USARTx->TxRx_Mode)
        {
            case USART_TxRxMode_Transmiting:
                cfg.pinNumber = GPIO_PIN_10;
                cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
                cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
                MCAL_GPIO_Init(GPIOB, &cfg);
                break;
            case USART_TxRxMode_Receiving:
                cfg.pinNumber = GPIO_PIN_11;
                cfg.pinMode = GPIO_MODE_INPUT_FLO;
                MCAL_GPIO_Init(GPIOB, &cfg);
                break;
            default:
                cfg.pinNumber = GPIO_PIN_10;
                cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
                cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
                MCAL_GPIO_Init(GPIOB, &cfg);

                cfg.pinNumber = GPIO_PIN_11;
                cfg.pinMode = GPIO_MODE_INPUT_FLO;
                MCAL_GPIO_Init(GPIOB, &cfg);
                break;
        }
    }
}

void USART_IRQHandler(USART_t *USARTx, void (*p_IRQ_callback[])(void))
{
    uint16 TempBuff;

    if ((USARTx->SR & USART_SR_FE) || (USARTx->SR & USART_SR_ORE) || (USARTx->SR & USART_SR_NE) &&
        (USARTx->CR3 & USART_CR3_EIE))
    {
        TempBuff = (uint16)USARTx->DR;
        if (p_IRQ_callback[USART_IRQ_ERROR])
        {
            p_IRQ_callback[USART_IRQ_ERROR]();
        }
    }

    if ((USARTx->SR & USART_SR_IDLE) && (USARTx->CR1 & USART_CR1_IDLEIE))
    {
        TempBuff = (uint16)USARTx->DR;
        if (p_IRQ_callback[USART_IRQ_IDLE])
        {
            p_IRQ_callback[USART_IRQ_IDLE]();
        }
    }

    if ((USARTx->SR & USART_SR_RXNE) && (USARTx->CR1 & USART_CR1_RXNEIE))
    {
        if (p_IRQ_callback[USART_IRQ_RXNE])
        {
            p_IRQ_callback[USART_IRQ_RXNE]();
        }
    }

    if ((USARTx->SR & USART_SR_TXE) && (USARTx->CR1 & USART_CR1_TXEIE))
    {
        if (p_IRQ_callback[USART_IRQ_TXE])
        {
            p_IRQ_callback[USART_IRQ_TXE]();
        }
    }

    if ((USARTx->SR & USART_SR_TC) && (USARTx->CR1 & USART_CR1_TCIE))
    {
        USARTx->SR &= ~(USART_SR_TC);
        if (p_IRQ_callback[USART_IRQ_TC])
        {
            p_IRQ_callback[USART_IRQ_TC]();
        }
    }

    if ((USARTx->SR & USART_SR_PE) && (USARTx->CR1 & USART_CR1_PEIE))
    {
        TempBuff = USARTx->DR;
        if (p_IRQ_callback[USART_IRQ_PE])
        {
            p_IRQ_callback[USART_IRQ_PE]();
        }
    }

    if ((USARTx->SR & USART_SR_CTS) && (USARTx->CR3 & USART_CR3_CTSIE))
    {
        USARTx->SR &= ~(USART_SR_CTS);
        if (p_IRQ_callback[USART_IRQ_CTS])
        {
            p_IRQ_callback[USART_IRQ_CTS]();
        }
    }
}
/*********************************
=========Supported APIs=========
*********************************/
/*
======================================================================================================================
* @Func_name   :   MCAL_USART_Init
* @brief       :   Initialization of the specified USART instance using the specified parameters in the config structure.
* @param [in]  :   USARTx: specifies the USART configuration structure to be initialized. Can be (USART1, USART2, or USART3).
* @param [in]  :   config: specifies the configuration parameters for the specified USART instance.
* @return      :   none.
* Note         :   To enable any of the interrupts use the function "MCAL_USART_Enable_Interrupt".
======================================================================================================================
*/
void MCAL_USART_Init(USART_Config_t * USARTx)
{
	uint32_t DIVMantissa , DIVFraction;

	USARTx->USARTx->CR1 |= USART_CR1_UE;		//Write UE to enable USART

	USARTx->USARTx->CR1 &= ~(USART_CR1_M);           /*Clear the word length bit*/
	USARTx->USARTx->CR1 |= USARTx->WordLength;

	USARTx->USARTx->CR2 &= ~(USART_CR2_STOP);        /*Clear the stop bits*/
	USARTx->USARTx->CR2 |= USARTx->StopBitsLength;

	UART_BRR_Calculations(USARTx, &DIVMantissa, &DIVFraction);
	USARTx->USARTx->BRR |= (DIVFraction & 0xF);
	USARTx->USARTx->BRR |= (DIVMantissa << 4);

	USARTx->USARTx->CR1 &= ~(USART_CR1_PCE | USART_CR1_PS); /*Clear the parity bits*/
	USARTx->USARTx->CR1 |= (USARTx->Parity);

	ConfigureMapped_GPIO_PINS(USARTx); //Set pins corresponding to Tx and Rx of UART to AFIO

	USARTx->USARTx->CR1 &= ~(USART_CR1_TE | USART_CR1_RE); /*Clear the Mode bits*/
	USARTx->USARTx->CR1 |= (USARTx->TxRx_Mode); //Enable Tx/Rx/BOTH

}
/*
======================================================================================================================
* @Func_name   :   MCAL_USART_DeInit
* @brief       :   Deinitialization of the specified USART instance.
* @param [in]  :   USARTx: specifies the USART configuration structure to be deinitialized. Can be (USART1, USART2, or USART3).
* @return      :   none.
* Note         :   Resets the USART peripheral and disables its interrupt.
======================================================================================================================
*/
void MCAL_USART_DeInit(USART_Config_t * USARTx)
{

	RCC_Config_t ResetUSART;
	if(USARTx->USARTx == USART1)
	{
		ResetUSART.PeripheralNo = RCC_PERIPHERAL_USART1;
		NVIC_IRQ37_USART1_DISABLE;
	}
	else if(USARTx->USARTx == USART2)
	{
		ResetUSART.PeripheralNo = RCC_PERIPHERAL_USART2;
		NVIC_IRQ38_USART2_DISABLE;
	}
	else
	{
		ResetUSART.PeripheralNo = RCC_PERIPHERAL_USART3;
		NVIC_IRQ39_USART3_DISABLE;
	}
	MCAL_RCC_ResetPeripheral(&ResetUSART);
}
/*
======================================================================================================================
* @Func_name   :   MCAL_USART_SendData
* @brief       :   Send data through the specified USART instance.
* @param [in]  :   USARTx: specifies the USART configuration structure
* @param [in]  :   data: data to be sent.
* @return      :   none.
* Note         :   If the mechanism is set to polling, the function will busy-wait until the transmission buffer is empty.
======================================================================================================================
*/
void MCAL_USART_SendData(USART_Config_t * USARTx , uint16_t data)
{

	if(USARTx->Mechanism_type == Polling)
	{
		while((USARTx->USARTx->SR & USART_SR_TXE) == USART_TX_BUFFER_FULL ); //Busy wait until TXE is 1
	}

	if(USARTx->WordLength == USART_WordLength_9b)
	{
		USARTx->USARTx->DR = (data & 0x1FF); //9 bits data if no parity or 8 bits data + 1 parity
	}
	else
	{
		USARTx->USARTx->DR = (data & 0xFF); //8 bits data if no parity or 7 bits data + 1 parity
	}

}
/*
======================================================================================================================
* @Func_name   :   MCAL_USART_ReceiveData
* @brief       :   Receive data from the specified USART instance.
* @param [in]  :   USARTx: specifies the USART configuration structure
* @param [out] :   data: pointer to the buffer where the received data will be stored.
* @return      :   none.
* Note         :   If the mechanism is set to polling, the function will busy-wait until the reception buffer is not empty.
======================================================================================================================
*/
void MCAL_USART_ReceiveData(USART_Config_t * USARTx , uint16_t * data)
{
	if(USARTx->Mechanism_type == Polling)
	{
		while((USARTx->USARTx->SR & USART_SR_RXNE) == USART_RX_BUFFER_EMPTY);
	}
	if(USARTx->WordLength == USART_WordLength_9b)
	{
		if(USARTx->Parity != USART_Parity_NONE)
		{
			*data = (USARTx->USARTx->DR & (uint16_t)0x1FF); //Read all the 9 bits as data
		}
		else
		{
			*data = (USARTx->USARTx->DR & (uint8_t)0xFF); //Read only 8 bits as data as MSB is parity bit
		}
	}
	else
	{
		if(USARTx->Parity != USART_Parity_NONE)
		{
			*data = (USARTx->USARTx->DR & (uint8_t)0xFF); //Read all the 8 bits as data
		}
		else
		{
			*data = (USARTx->USARTx->DR & (uint8_t)0x7F); //Read only 7 bits as data as MSB is parity bit
		}
	}
}

/*
======================================================================================================================
* @Func_name   :   MCAL_USART_WAIT_TransmissionComplete
* @brief       :   Wait until the transmission is complete.
* @param [in]  :   USARTx: specifies the USART instance.
* @return      :   none.
======================================================================================================================
*/
void MCAL_USART_WAIT_TransmissionComplete(USART_Config_t * USARTx)
{
	while((USARTx->USARTx->SR & USART_SR_TC));
}

/*
======================================================================================================================
* @Func_name   :   MCAL_USART_Enable_Interrupt
* @brief       :   Enable the specified interrupt for the USART instance and set the callback function.
* @param [in]  :   USARTx: specifies the USART configuration structure
* @param [in]  :   IRQ: specifies the interrupt to be enabled. Must be a value from @ref USART_IRQ_Define
* @param [in]  :   P_IRQEvent_CallBack: pointer to the callback function.
* @return      :   none.
======================================================================================================================
*/
void MCAL_USART_Enable_Interrupt(USART_Config_t * USARTx , uint8_t IRQ , void ( * P_IRQEvent_CallBack)(void))
{
	if(USARTx->USARTx == USART1)
	{
        MCAL_NVIC_EnableIRQ(NVIC_USART1_IVT_INDEX);
		p_IRQ_callback_USART1[IRQ] = P_IRQEvent_CallBack;
	}
	else if(USARTx->USARTx == USART2)
	{
        MCAL_NVIC_EnableIRQ(NVIC_USART2_IVT_INDEX);
		p_IRQ_callback_USART2[IRQ] = P_IRQEvent_CallBack;
	}
	else if(USARTx->USARTx == USART3)
	{
        MCAL_NVIC_EnableIRQ(NVIC_USART3_IVT_INDEX);
		p_IRQ_callback_USART3[IRQ] = P_IRQEvent_CallBack;
	}


    if(IRQ == USART_IRQ_ERROR || IRQ == USART_IRQ_CTS)
    {
        SET_BIT(USARTx->USARTx->CR3, IRQ);

    }else{

        SET_BIT(USARTx->USARTx->CR1, IRQ);
    }
}

/*
======================================================================================================================
* @Func_name   :   MCAL_UART_Interrupt_Disable
* @brief       :   Disable the specified interrupt for the USART instance.
* @param [in]  :   USARTx: specifies the USART configuration structure
* @param [in]  :   IRQ: specifies the interrupt to be disabled , Must be a value from @ref USART_IRQ_Define
* @return      :   none.
======================================================================================================================
*/
void MCAL_UART_Interrupt_Disable(USART_Config_t * USARTx, uint8 IRQ)
{
    if(IRQ == USART_IRQ_ERROR || IRQ == USART_IRQ_CTS)
    {
        CLEAR_BIT(USARTx->USARTx->CR3, IRQ);

    }else{

        CLEAR_BIT(USARTx->USARTx->CR1, IRQ);
    }
}

/**************************************************************************************************************************
===============================================
*               USART ISR functions
*===============================================
*/
// Overriding ISR of USARTx

void USART1_IRQHandler(void)
{
    USART_IRQHandler(USART1, p_IRQ_callback_USART1);
}

void USART2_IRQHandler(void)
{
    USART_IRQHandler(USART2, p_IRQ_callback_USART2);
}

void USART3_IRQHandler(void)
{
    USART_IRQHandler(USART3, p_IRQ_callback_USART3);
}
