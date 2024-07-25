/*
 * STM32_F103C6_SPI_Driver.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */
#include <STM32F103C6.h>
#include <RCC/STM32F103x6_RCC_Driver.h>
#include <NVIC/STM32F103x6_NVIC_Driver.h>
#include <SPI/STM32F103x6_SPI_Driver.h>
#include <GPIO/STM32F103x6_GPIO_Driver.h>


void (* p_IRQ_callback_SPI1[7] )(void);
void (* p_IRQ_callback_SPI2[7] )(void);
void (* p_IRQ_callback_SPI3[7] )(void);

/*********************************
=========Helper Functions=========
*********************************/



void SPI_ConfigureMapped_GPIO_PINS(SPI_Config_t * SPIx)
{
    pinConfig_t cfg;

    if (SPIx->SPI == SPI1)
    {
    	if(SPIx->DeviceMode == SPI_DeviceMode_SLAVE)
    	{
    		//NSS
    		cfg.pinNumber = GPIO_PIN_4;
    		cfg.pinMode = GPIO_MODE_INPUT_FLO;
    		MCAL_GPIO_Init(GPIOA, &cfg);


    		//SCK
			cfg.pinNumber = GPIO_PIN_5;
			cfg.pinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &cfg);

			//MISO
			cfg.pinNumber = GPIO_PIN_6;
			cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
			cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &cfg);

			//MOSI

			cfg.pinNumber = GPIO_PIN_7;
			cfg.pinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &cfg);

    	}
    	else //Master
    	{
    		//NSS
    		switch(SPIx->SS_Managment)
    		{
    		case SPI_SS_Managment_Master_HW_OutputDisabled:
    		{
                cfg.pinNumber = GPIO_PIN_4;
                cfg.pinMode = GPIO_MODE_INPUT_FLO;
                MCAL_GPIO_Init(GPIOA, &cfg);
                break;
    		}
    		case SPI_SS_Managment_Master_HW_OutputEnabled:
    		{
                cfg.pinNumber = GPIO_PIN_4;
                cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
                cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
                MCAL_GPIO_Init(GPIOA, &cfg);
                break;
    		}
    		default:
    		{
    			break; //Do nothing if SW selected
    		}
    		}

    		//SCK
            cfg.pinNumber = GPIO_PIN_5;
            cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
            cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
            MCAL_GPIO_Init(GPIOA, &cfg);

            //MISO
            cfg.pinNumber = GPIO_PIN_6;
            cfg.pinMode = GPIO_MODE_INPUT_FLO;
            MCAL_GPIO_Init(GPIOA, &cfg);


            //MOSI
            cfg.pinNumber = GPIO_PIN_7;
            cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
            cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
            MCAL_GPIO_Init(GPIOA, &cfg);
    	}
    }
    else if (SPIx->SPI == SPI2)
    {
    	if(SPIx->DeviceMode == SPI_DeviceMode_SLAVE)
    	{
    		//NSS
    		cfg.pinNumber = GPIO_PIN_12;
    		cfg.pinMode = GPIO_MODE_INPUT_FLO;
    		MCAL_GPIO_Init(GPIOB, &cfg);


    		//SCK
			cfg.pinNumber = GPIO_PIN_13;
			cfg.pinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &cfg);

			//MISO
			cfg.pinNumber = GPIO_PIN_14;
			cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
			cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOB, &cfg);

			//MOSI

			cfg.pinNumber = GPIO_PIN_15;
			cfg.pinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &cfg);

    	}
    	else //Master
    	{
    		//NSS
    		switch(SPIx->SS_Managment)
    		{
    		case SPI_SS_Managment_Master_HW_OutputDisabled:
    		{
                cfg.pinNumber = GPIO_PIN_12;
                cfg.pinMode = GPIO_MODE_INPUT_FLO;
                MCAL_GPIO_Init(GPIOB, &cfg);
                break;
    		}
    		case SPI_SS_Managment_Master_HW_OutputEnabled:
    		{
                cfg.pinNumber = GPIO_PIN_12;
                cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
                cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
                MCAL_GPIO_Init(GPIOB, &cfg);
                break;
    		}
    		default:
    		{
    			break; //Do nothing if SW selected
    		}
    		}

    		//SCK
            cfg.pinNumber = GPIO_PIN_13;
            cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
            cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
            MCAL_GPIO_Init(GPIOB, &cfg);

            //MISO
            cfg.pinNumber = GPIO_PIN_14;
            cfg.pinMode = GPIO_MODE_INPUT_FLO;
            MCAL_GPIO_Init(GPIOB, &cfg);


            //MOSI
            cfg.pinNumber = GPIO_PIN_15;
            cfg.pinMode = GPIO_MODE_AF_OUTPUT_PP;
            cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
            MCAL_GPIO_Init(GPIOB, &cfg);
    	}
    }
}

void SPI_IRQHandler(SPI_t *SPIx, void (*p_IRQ_callback[])(void))
{

    if ((SPIx->SR & SPI_SR_RXNE) && (SPIx->CR1 & SPI_CR2_RXNEIE))
    {
        if (p_IRQ_callback[SPI_IRQ_RXNE])
        {
            p_IRQ_callback[SPI_IRQ_RXNE]();
        }
    }

    if ((SPIx->SR & SPI_SR_TXE) && (SPIx->CR1 & SPI_CR2_TXEIE))
    {
        if (p_IRQ_callback[SPI_IRQ_TXE])
        {
            p_IRQ_callback[SPI_IRQ_TXE]();
        }
    }

    if ((SPIx->SR & SPI_SR_MODF) && (SPIx->CR1 & SPI_CR2_ERRIE))
    {

        if (p_IRQ_callback[SPI_IRQ_MODF])
        {
            p_IRQ_callback[SPI_IRQ_MODF]();
        }
    }

    if ((SPIx->SR & SPI_SR_OVR) && (SPIx->CR1 & SPI_CR2_ERRIE))
    {

        if (p_IRQ_callback[SPI_IRQ_OVR])
        {
            p_IRQ_callback[SPI_IRQ_OVR]();
        }
    }

    if ((SPIx->SR & SPI_SR_CRCERR) && (SPIx->CR1 & SPI_CR2_ERRIE))
    {

        if (p_IRQ_callback[SPI_IRQ_CRCERR])
        {
            p_IRQ_callback[SPI_IRQ_CRCERR]();
        }
    }
}
/*********************************
=========Supported APIs=========
*********************************/
/*
======================================================================================================================
* @Func_name   :   MCAL_SPI_Init
* @brief       :   Initializes the specified SPI instance.
* @param [in]  :   SPIx: specifies the SPI instance to be initialized.
* @return      :   none.
======================================================================================================================
*/
void MCAL_SPI_Init(SPI_Config_t * SPIx)
{
	uint16_t temp = 0;

	temp |= SPIx->DeviceMode; //Master or Slave
	temp |= SPIx->CommunicationMode;
	temp |= SPIx->DataSize;

	temp |= SPIx->FrameFormat;
	temp |= SPIx->TimingConfig;

	temp |= SPIx->MasterClk;

	if(SPIx->SS_Managment == SPI_SS_Managment_Master_HW_OutputEnabled || SPIx->SS_Managment == SPI_SS_Managment_Master_HW_OutputDisabled )
	{
		SPIx->SPI->CR2 |= SPIx->SS_Managment;
	}
	else
	{
		temp |= SPIx->SS_Managment;
	}

	temp |= SPI_CR1_SPE; //SPI Enable

	SPIx->SPI->CR1 |= temp;

	SPI_ConfigureMapped_GPIO_PINS(SPIx);

}

/*
======================================================================================================================
* @Func_name   :   MCAL_SPI_DeInit
* @brief       :   Deinitializes the specified SPI instance.
* @param [in]  :   SPIx: specifies the SPI instance to be deinitialized.
* @return      :   none.
======================================================================================================================
*/
void MCAL_SPI_DeInit(SPI_Config_t * SPIx)
{
	RCC_Config_t ResetSPI;
	if(SPIx->SPI == SPI1)
	{
		ResetSPI.PeripheralNo = RCC_PERIPHERAL_SPI1;
		MCAL_NVIC_DisableIRQ(NVIC_SPI1_IVT_INDEX);
	}
	else
	{
		ResetSPI.PeripheralNo = RCC_PERIPHERAL_SPI2;
		MCAL_NVIC_DisableIRQ(NVIC_SPI2_IVT_INDEX);
	}
	MCAL_RCC_ResetPeripheral(&ResetSPI);
}

/*
======================================================================================================================
* @Func_name   :   MCAL_SPI_SendData
* @brief       :   Sends data through the specified SPI instance.
* @param [in]  :   SPIx: specifies the SPI instance.
* @param [in]  :   data: pointer to the data to be sent.
* @return      :   none.
======================================================================================================================
*/
void MCAL_SPI_SendData(SPI_Config_t * SPIx , uint16_t * data)
{
	if(SPIx->Mechanism_type == SPIPolling)
	{
		while(!(SPIx->SPI->SR & SPI_SR_TXE));
	}
	SPIx->SPI->DR = *data;


}

/*
======================================================================================================================
* @Func_name   :   MCAL_SPI_ReceiveData
* @brief       :   Receives data through the specified SPI instance.
* @param [in]  :   SPIx: specifies the SPI instance.
* @param [in]  :   data: pointer to the buffer where received data will be stored.
* @return      :   none.
======================================================================================================================
*/
void MCAL_SPI_ReceiveData(SPI_Config_t * SPIx , uint16_t * data)
{
	if(SPIx->Mechanism_type == SPIPolling)
	{
		while(!(SPIx->SPI->SR & SPI_SR_RXNE));
	}
	*data = SPIx->SPI->DR;
}
/*
======================================================================================================================
* @Func_name   :   MCAL_SPI_ExchangeData
* @brief       :   Exchanges data through the specified SPI instance.
* @param [in]  :   SPIx: specifies the SPI instance.
* @param [in]  :   data: pointer to the data to be sent and where received data will be stored.
* @return      :   none.
======================================================================================================================
*/
void MCAL_SPI_ExchangeData(SPI_Config_t * SPIx , uint16_t * data)
{
	if(SPIx->Mechanism_type == SPIPolling)
	{
		//Transmit
		while(!(SPIx->SPI->SR & SPI_SR_TXE));

		SPIx->SPI->DR = *data;

		//Read Captured data (Received)

		while(!(SPIx->SPI->SR & SPI_SR_RXNE));

		*data = SPIx->SPI->DR;
	}

	//transmit directly but wait until the received data reach the RX buffer for safety
	SPIx->SPI->DR = *data;
	while(!(SPIx->SPI->SR & SPI_SR_RXNE));
	*data = SPIx->SPI->DR;
}

/*
======================================================================================================================
* @Func_name   :   MCAL_SPI_Enable_Interrupt
* @brief       :   Enables the specified SPI interrupt.
* @param [in]  :   SPIx: specifies the SPI instance.
* @param [in]  :   IRQ: specifies the interrupt to be enabled, Must be a value from @ref SPI_IRQ_Define.
* @param [in]  :   P_IRQEvent_CallBack: pointer to the callback function for the specified interrupt.
* @return      :   none.
======================================================================================================================
*/
void MCAL_SPI_Enable_Interrupt(SPI_Config_t * SPIx , uint8_t IRQ , void ( * P_IRQEvent_CallBack)(void))
{
	if(SPIx->SPI == SPI1)
	{
        MCAL_NVIC_EnableIRQ(NVIC_SPI1_IVT_INDEX);
		p_IRQ_callback_SPI1[IRQ] = P_IRQEvent_CallBack;
	}
	else if(SPIx->SPI == SPI2)
	{
        MCAL_NVIC_EnableIRQ(NVIC_SPI2_IVT_INDEX);
		p_IRQ_callback_SPI2[IRQ] = P_IRQEvent_CallBack;
	}



    if(IRQ == SPI_IRQ_TXE || IRQ == SPI_IRQ_RXNE)
    {
        SET_BIT(SPIx->SPI->CR2, IRQ);
        SPIx->Mechanism_type = SPIInterrupt;

    }else{

        SET_BIT(SPIx->SPI->CR2, 5);
    }
}

/*
======================================================================================================================
* @Func_name   :   MCAL_SPI_Interrupt_Disable
* @brief       :   Disables the specified SPI interrupt.
* @param [in]  :   SPIx: specifies the SPI instance.
* @param [in]  :   IRQ: specifies the interrupt to be disabled, Must be a value from @ref SPI_IRQ_Define.
* @return      :   none.
======================================================================================================================
*/
void MCAL_SPI_Interrupt_Disable(SPI_Config_t * SPIx, uint8 IRQ)
{
    if(IRQ == SPI_IRQ_TXE || IRQ == SPI_IRQ_RXNE)
    {
        SPIx->Mechanism_type = SPIPolling;
    	CLEAR_BIT(SPIx->SPI->CR2, IRQ);
        return;
    }

    if(SPIx->SPI == SPI1)
    {
        if(IRQ == SPI_IRQ_TXE || IRQ == SPI_IRQ_RXNE)
        {

            CLEAR_BIT(SPIx->SPI->CR2, IRQ);
            p_IRQ_callback_SPI1[IRQ] = NULL;
            return;
        }
        else
        {
        	p_IRQ_callback_SPI1[IRQ] = NULL;
        	if(p_IRQ_callback_SPI1[5] || p_IRQ_callback_SPI1[4] || p_IRQ_callback_SPI1[3])
        	{
        		return;
        	}
        	CLEAR_BIT(SPIx->SPI->CR2, 5);
        }
    }
    else if (SPIx->SPI == SPI2)
    {
        if(IRQ == SPI_IRQ_TXE || IRQ == SPI_IRQ_RXNE)
        {

            CLEAR_BIT(SPIx->SPI->CR2, IRQ);
            p_IRQ_callback_SPI2[IRQ] = NULL;
            return;
        }
        else
        {
        	p_IRQ_callback_SPI2[IRQ] = NULL;
        	if(p_IRQ_callback_SPI2[SPI_IRQ_MODF] || p_IRQ_callback_SPI2[SPI_IRQ_OVR] || p_IRQ_callback_SPI2[SPI_IRQ_CRCERR])
        	{
        		return;
        	}
        	CLEAR_BIT(SPIx->SPI->CR2, 5);
        }
    }

}
uint8_t is_SPI_BSY(SPI_Config_t * SPIcfg)
{
	if(SPIcfg->SPI->SR & SPI_SR_BSY)
		return 1;
	else
		return 0;
}

/**************************************************************************************************************************
===============================================
*               SPI ISR functions
*===============================================
*/
// Overriding ISR of SPIx

void SPI1_IRQHandler(void)
{
    SPI_IRQHandler(SPI1, p_IRQ_callback_SPI1);
}

void SPI2_IRQHandler(void)
{
    SPI_IRQHandler(SPI2, p_IRQ_callback_SPI2);
}

void SPI3_IRQHandler(void)
{
    SPI_IRQHandler(SPI3, p_IRQ_callback_SPI3);
}
