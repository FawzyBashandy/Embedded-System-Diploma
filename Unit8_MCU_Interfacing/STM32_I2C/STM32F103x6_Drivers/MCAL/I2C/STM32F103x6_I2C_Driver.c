/*
 * STM32_F103C6_I2C_Driver.h
 *
 *  Created on: Mar 15, 2024
 *      Author: Fawzy Bashandy
 */

#include <STM32F103C6.h>
#include <GPIO/STM32F103x6_GPIO_Driver.h>
#include <I2C/STM32F103x6_I2C_Driver.h>
#include <RCC/STM32F103x6_RCC_Driver.h>
#include <NVIC/STM32F103x6_NVIC_Driver.h>


void (* p_IRQ_callback_I2C1[7] )(void);
void (* p_IRQ_callback_I2C2[7] )(void);

/*********************************
=========Helper Functions=========
*********************************/


/**================================================================
* @Fn          - I2C_ConfigureMapped_GPIO_PINS
* @brief       - Configures GPIO pins for I2C functionality based on the selected I2C peripheral (I2C1 or I2C2).
* @param [in]  - I2Cx      : Pointer to the I2C_Config_t structure, specifying the I2C peripheral to configure.
* @retval       - N/A
* Note         - Configures SCL and SDA pins for I2C1 and I2C2. For I2C1, uses GPIOB pins 6 and 7; for I2C2, uses GPIOB pins 10 and 11.
*               - Pins are set to Alternate Function Open-Drain mode with 10 MHz speed.
**================================================================*/
static void I2C_ConfigureMapped_GPIO_PINS(I2C_Config_t * I2Cx)
{
    pinConfig_t cfg;

    if (I2Cx->I2C == I2C1)
    {
    	//SCL
    	cfg.pinNumber 		= GPIO_PIN_6;
    	cfg.pinMode	  		= GPIO_MODE_AF_OUTPUT_OD;
    	cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
    	MCAL_GPIO_Init(GPIOB, &cfg);

    	//SDA
    	cfg.pinNumber 		= GPIO_PIN_7;
    	cfg.pinMode	  		= GPIO_MODE_AF_OUTPUT_OD;
    	cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
    	MCAL_GPIO_Init(GPIOB, &cfg);
    }
    else if (I2Cx->I2C == I2C2)
    {
    	//SCL
    	cfg.pinNumber 		= GPIO_PIN_10;
    	cfg.pinMode	  		= GPIO_MODE_AF_OUTPUT_OD;
    	cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
    	MCAL_GPIO_Init(GPIOB, &cfg);

    	//SDA
    	cfg.pinNumber 		= GPIO_PIN_11;
    	cfg.pinMode	  		= GPIO_MODE_AF_OUTPUT_OD;
    	cfg.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
    	MCAL_GPIO_Init(GPIOB, &cfg);
    }
}

/**================================================================
* @Fn          - I2C_IRQHandler
* @brief       - Handles I2C interrupt requests and calls the appropriate callback functions based on interrupt flags.
* @param [in]  - I2Cx      : Pointer to the I2C_t structure, specifying the I2C peripheral.
* @param [in]  - p_IRQ_callback : Array of function pointers to the callback functions for different I2C interrupt events.
* @retval       - N/A
* Note         - Handles various I2C events including data transmission, data reception, address matched, start bit sent, and stop condition.
**================================================================*/
static void I2C_IRQHandler(I2C_t *I2Cx, void (*p_IRQ_callback[])(void))
{
	uint16_t dummy;
	if(I2Cx -> CR2 & I2C_CR2_ITBUFEN)
	{
		if(I2Cx -> SR1 & I2C_SR1_TXE)
		{
			//Cleared by software writing to the DR register or by hardware after a start or a stop condition or when PE=0.
			p_IRQ_callback[TransmitterBufferEmpty]();
		}
		if(I2Cx -> SR1 & I2C_SR1_RXNE)
		{
			//Cleared by software reading or writing the DR register or by hardware when PE=0.
			p_IRQ_callback[ReceiverBufferNotEmpty]();
		}
	}
	else if(I2Cx -> CR2 & I2C_CR2_ITEVTEN)
	{
		if(I2Cx->SR1 & I2C_SR1_STOPF)
		{
			//Cleared by software reading the SR1 register followed by a write in the CR1 register, or by hardware when PE=0
			I2Cx->DR |= 0x0000; //Dummy read
			p_IRQ_callback[StopReceivedInterrupt]();
		}
		if(I2Cx->SR1 & I2C_SR1_BTF)
		{
			//Cleared by software reading SR1 followed by either a read or write in the DR register or by hardware after a start or a stop condition in transmission or when PE=0.
			p_IRQ_callback[DataByteTransferFinishedInterrupt]();
		}
		if(I2Cx->SR1 & I2C_SR1_ADDR)
		{
			//This bit is cleared by software reading SR1 register followed reading SR2, or by hardware when PE=0.
			dummy = I2Cx->SR2;
			p_IRQ_callback[AddressSentorMatchedInterrupt]();
		}
		if(I2Cx->SR1 & I2C_SR1_SB)
		{
			//Cleared by software by reading the SR1 register followed by writing the DR register
			p_IRQ_callback[StartBitSentInterrupt]();
		}
	}
}

/**================================================================
* @Fn          - Calculate_CRC
* @brief       - Calculates the CRC value used for I2C clock speed configuration.
* @param [in]  - F_I2C    : I2C clock frequency in Hz.
* @retval       - CRC     : Calculated CRC value.
* Note         - The CRC value is derived from the peripheral clock frequency (F_PCLK1) and the I2C clock frequency.
**================================================================*/
static uint16_t Calculate_CRC(uint32_t F_I2C)
{
	uint16_t CRC;
	uint32_t F_PCLK1 = MCAL_RCC_GetPCLK1Frequency();

	CRC = (F_PCLK1 / (F_I2C << 1 )); //CRC = Fpclk1/(2*Required SCL Frequency)

	return CRC;

}

/**================================================================
* @Fn          - GetFlagStatus
* @brief       - Checks the status of a specific I2C flag.
* @param [in]  - I2C      : Pointer to the I2C_t structure, specifying the I2C peripheral.
* @param [in]  - Flag     : The I2C flag to check.
* @retval       - EventStatus : Status of the specified flag (SET or RESET).
* Note         - Flags checked include bus busy, start bit, address matched, data received, and byte transfer finished.
**================================================================*/
static eStatus_t GetFlagStatus(I2C_t * I2C , eI2CFlags_t Flag)
{
	eStatus_t EventStatus = RESET;
	uint16_t dummyRead;
	switch(Flag)
	{
	case I2C_Busy_Flag:
	{
        /*
         *   Bit 1 BUSY: Bus busy
         *       0: No communication on the bus
         *       1: Communication ongoing on the bus
         *       – Set by hardware on detection of SDA or SCL low
         *       – cleared by hardware on detection of a Stop condition.
         *       It indicates a communication in progress on the bus. This information is still updated when
         *       the interface is disabled (PE=0).
        */

		if((I2C->SR2) & (I2C_SR2_BUSY))
			EventStatus = SET;
		else
			EventStatus = RESET;
		break;
	}
	case I2C_EV5:
	{
        /*
        *   EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
        *
        *   Bit 0 SB: Start bit (Master mode)
        *   0: No Start condition
        *   1: Start condition generated.
        *   – Set when a Start condition generated.
        *   – Cleared by software by reading the SR1 register followed by writing the DR register, or by
        *   hardware when PE=0
        */
		if((I2C->SR1) & (I2C_SR1_SB))
			EventStatus = SET;
		else
			EventStatus = RESET;
		break;
	}
	case I2C_EV6:
	{
        /*
         *  EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
         *
         * Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
         *      Address matched (Slave)
         *       0: Address mismatched or not received.
         *       1: Received address matched.
         *
         *     Address sent (Master)
         *       0: No end of address transmission
         *       1: End of address transmission
         *
         *      Note: ADDR is not set after a NACK reception
         * */
		if((I2C->SR1) & (I2C_SR1_ADDR))
		{
			EventStatus = SET;
		dummyRead = I2C->SR2;
		}
		else
			EventStatus = RESET;
		break;
	}
    case I2C_EV7:
    {
        /**
         * EV7: RxNe = 1, cleared by reading the DR register
         *
         * Bit 6 RxNE: Data register not empty (receivers)
         *  0: Data register empty
         *  1: Data register not empty
         */
        if((I2C->SR1) & (I2C_SR1_RXNE))
        {
            EventStatus = SET;
        }else{
            EventStatus = RESET;
        }

        break;
	}
	case I2C_EV8_1:
	case I2C_EV8:
	{
        /**
         *  EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
         *  EV8: TxE=1, shift register not empty, .data register empty, cleared by writing DR register
         *
         *  Bit 7 TxE: Data register empty (transmitters)
         *  0: Data register not empty
         *  1: Data register empty
         *
         *  TxE is not set if a NACK is received,
         */
		if((I2C->SR1) & (I2C_SR1_TXE))
			EventStatus = SET;
		else
			EventStatus = RESET;
		break;
	}
	case I2C_EV8_2:
	{
        /**
         * EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
         *
         * Bit 2 BTF: Byte transfer finished
         *  0: Data byte transfer not done
         *  1: Data byte transfer succeeded
         *
         * Bit 7 TxE: Data register empty (transmitters)
         *  0: Data register not empty
         *  1: Data register empty
         */
		if((I2C->SR1) & (I2C_SR1_TXE) && (I2C->SR1) & (I2C_SR1_BTF))
			EventStatus = SET;
		else
			EventStatus = RESET;
		break;
	}
	default:
		break;
	}
	return EventStatus;
}

/**================================================================
* @Fn          - GenerateStart
* @brief       - Generates a start condition or disables it based on the provided state.
* @param [in]  - I2Cx     : Pointer to the I2C_Config_t structure, specifying the I2C peripheral.
* @param [in]  - NewState : The state to set for the start condition (Enable or Disable).
* @param [in]  - Start    : Type of start condition (RepeatedStart or not).
* @retval       - N/A
* Note         - If starting a new transmission, waits for the bus to be idle before generating the start condition.
**================================================================*/
static void GenerateStart(I2C_Config_t * I2Cx , FunctionalState NewState ,eStart_t Start )
{
	if(Start != RepeatedStart)
	{
		while(GetFlagStatus(I2Cx,I2C_Busy_Flag));
	}

    if(NewState == Enable)
    {
        /*Enable the start condition generation*/
    	I2Cx->I2C->CR1 |= I2C_CR1_START;
    }else{
        /*Disable the start condition generation*/
    	I2Cx->I2C->CR1 &= ~(I2C_CR1_START);
    }
}

/**================================================================
* @Fn          - I2C_SendAddress
* @brief       - Sends the slave address to the I2C bus.
* @param [in]  - I2Cx         : Pointer to the I2C_Config_t structure, specifying the I2C peripheral.
* @param [in]  - SlaveAddress : 7-bit slave address to send.
* @param [in]  - DirectionOfTx : Direction of transmission (MasterTransmits or MasterReceives).
* @retval       - N/A
* Note         - Address is sent with the direction bit set.
**================================================================*/
static void I2C_SendAddress(I2C_Config_t * I2Cx , uint8_t SlaveAddress , eDataDir_t DirectionOfTx)
{
	//7 bit address mode supported only.
	SlaveAddress = (SlaveAddress << 1) | DirectionOfTx;

	I2Cx->I2C->DR = SlaveAddress;
}

/**================================================================
* @Fn          - GenerateStop
* @brief       - Generates a stop condition on the I2C bus.
* @param [in]  - I2Cx : Pointer to the I2C_Config_t structure, specifying the I2C peripheral.
* @param [in]  - Stop : Type of stop condition (StopConditionEnable or not).
* @retval       - N/A
* Note         - Generates a stop condition if enabled.
**================================================================*/
static void GenerateStop(I2C_Config_t * I2Cx , eStop_t Stop )
{
	if(Stop == StopConditionEnable)
	{
		I2Cx->I2C->CR1 |= I2C_CR1_STOP;
	}
}

/**================================================================
* @Fn          - ConfigureACK
* @brief       - Configures the acknowledgment feature of I2C.
* @param [in]  - I2C       : Pointer to the I2C_t structure, specifying the I2C peripheral.
* @param [in]  - NewState  : State to set for acknowledgment (Enable or Disable).
* @retval       - N/A
* Note         - Enables or disables acknowledgment based on the state.
**================================================================*/
static void ConfigureACK(I2C_t * I2C , FunctionalState NewState)
{
	if(NewState == Enable)
	{
		I2C->CR1 |= I2C_CR1_ACK;
	}
	else
	{
		I2C->CR1 &= ~I2C_CR1_ACK;
	}
}
/*********************************
=========Supported APIs=========
*********************************/

/**================================================================
* @Fn          - MCAL_I2C_Init
* @brief       - Initializes the I2C peripheral based on the provided configuration.
* @param [in]  - I2Cx : Pointer to the I2C_Config_t structure, specifying the I2C peripheral to initialize.
* @retval       - N/A
* Note         - Configures various I2C settings including clock speed, address mode, acknowledge, and interrupts.
**================================================================*/
void MCAL_I2C_Init(I2C_Config_t * I2Cx)
{
	//1-Set Peripheral Input Clock (FREQ bits)
	I2Cx->I2C->CR2 |= (MCAL_RCC_GetPCLK2Frequency()/1000000) & I2C_CR2_FREQ;

	//2-Set CRR bits
	I2Cx->I2C->CCR |= Calculate_CRC(I2Cx->ClockSpeed);

	//3-Set Rise time
	I2Cx->I2C->TRISE = MCAL_RCC_GetPCLK2Frequency()/1000000 + 1;

	//4-configure General Call address bit
	I2Cx->I2C->CR1 |= I2Cx->GeneralCallAddress;

	//4-Set Address Mode (7bit or 10bit)
	if(I2Cx->SlaveAddress->Length == TenBits)
	{
		I2Cx->I2C->OAR1 |= I2C_OAR2_ADDMODE;
	}

	//5-Enable Acknowledge and configure clock stretching
	I2Cx->I2C->CR1 |= I2C_CR1_ACK;
	I2Cx->I2C->CR1 |= I2Cx->ClockStretching;
	//6- Device Interrupt Configuration
	if(I2Cx->Mechanism == I2CInterrupt)
	{
		if(I2Cx->I2C == I2C1)
		{
			MCAL_NVIC_EnableIRQ(NVIC_I2C1_ER_IVT_INDEX);
			MCAL_NVIC_EnableIRQ(NVIC_I2C1_EV_IVT_INDEX);
		}
		else
		{
			MCAL_NVIC_EnableIRQ(NVIC_I2C2_ER_IVT_INDEX);
			MCAL_NVIC_EnableIRQ(NVIC_I2C2_EV_IVT_INDEX);
		}
	}

	//7-Dual Address Configuration
	if(I2Cx->SlaveAddress->Mode == DualAddress)
	{
		I2Cx->I2C->OAR2 |= I2C_OAR2_ENDUAL;
		I2Cx->I2C->OAR2 |= I2Cx->SlaveAddress->Secondary_Address << I2C_OAR2_ADD2_Pos;
	}
	I2Cx->I2C->OAR1 |= I2Cx->SlaveAddress->Primary_Address << I2C_OAR1_ADD_Pos;

	//8- Configure corresponding GPIO Pins
	I2C_ConfigureMapped_GPIO_PINS(I2Cx);

	//9- Enable the I2C
	I2Cx->I2C->CR1 |= I2C_CR1_PE;
}

/**================================================================
* @Fn          - MCAL_I2C_DeInit
* @brief       - Deinitializes the I2C peripheral, resetting it to default state.
* @param [in]  - I2Cx : Pointer to the I2C_Config_t structure, specifying the I2C peripheral to deinitialize.
* @retval       - N/A
* Note         - Disables I2C interrupts and resets the peripheral clock.
**================================================================*/
void MCAL_I2C_DeInit(I2C_Config_t * I2Cx)
{
	RCC_Config_t ResetI2C;
	if(I2Cx->I2C == I2C1)
	{
		ResetI2C.PeripheralNo = RCC_PERIPHERAL_I2C1;
		MCAL_NVIC_DisableIRQ(NVIC_I2C1_ER_IVT_INDEX);
		MCAL_NVIC_DisableIRQ(NVIC_I2C1_EV_IVT_INDEX);
	}
	else
	{
		ResetI2C.PeripheralNo = RCC_PERIPHERAL_I2C2;
		MCAL_NVIC_DisableIRQ(NVIC_I2C2_ER_IVT_INDEX);
		MCAL_NVIC_DisableIRQ(NVIC_I2C2_EV_IVT_INDEX);
	}
	MCAL_RCC_ResetPeripheral(&ResetI2C);
}

/**================================================================
* @Fn          - MCAL_I2C_Master_TX
* @brief       - Performs a master transmit operation over I2C.
* @param [in]  - I2Cx       : Pointer to the I2C_Config_t structure, specifying the I2C peripheral.
* @param [in]  - MasterCFG  : Pointer to the sMasterTxRx_t structure, containing configuration for the master transmission.
* @retval       - N/A
* Note         - Generates a start condition, sends data, and generates a stop condition based on configuration.
**================================================================*/
void MCAL_I2C_Master_TX(I2C_Config_t * I2Cx , sMasterTxRx_t * MasterCFG )
{
	GenerateStart(I2Cx, Enable, MasterCFG->StartCondition);

	//Wait for EV5(SB=1) Event
	while(!GetFlagStatus(I2Cx->I2C, I2C_EV5));

	//Send Slave Address
	I2C_SendAddress(I2Cx , MasterCFG->AddressCFG.Primary_Address , MasterTransmits);

	//Wait for EV6 (ADDR=1)
	while(!GetFlagStatus(I2Cx->I2C, I2C_EV6));

	//Send data if EV8(TXE = 1) happened only
	for(int i = 0 ; i < MasterCFG->DataBufferLength ; i++)
	{
		while(!GetFlagStatus(I2Cx->I2C, I2C_EV8));

		I2Cx->I2C->DR = (MasterCFG->DataBuffer)[i];
	}

	//Wait For Event EV8_2(TXE=1 and BTF=1) To occur
	while(!GetFlagStatus(I2Cx->I2C, I2C_EV8_2));

	//Generate Stop

	GenerateStop(I2Cx, MasterCFG->StopCondition);
}

/**================================================================
* @Fn          - MCAL_I2C_Master_RX
* @brief       - Performs a master receive operation over I2C.
* @param [in]  - I2Cx       : Pointer to the I2C_Config_t structure, specifying the I2C peripheral.
* @param [in]  - MasterCFG  : Pointer to the sMasterTxRx_t structure, containing configuration for the master reception.
* @retval       - N/A
* Note         - Generates a start condition, receives data, and generates a stop condition based on configuration.
**================================================================*/
void MCAL_I2C_Master_RX(I2C_Config_t * I2Cx , sMasterTxRx_t * MasterCFG )
{
	GenerateStart(I2Cx, Enable, MasterCFG->StartCondition);

	//Wait for EV5(SB=1) Event
	while(!GetFlagStatus(I2Cx->I2C, I2C_EV5));

	//Send Slave Address
	I2C_SendAddress(I2Cx , MasterCFG->AddressCFG.Primary_Address ,MasterReceives);

	//Wait for EV6
	while(!GetFlagStatus(I2Cx->I2C, I2C_EV6));

	//Send data if EV8 happened only
	for(int i = 0 ; i < MasterCFG->DataBufferLength ; i++)
	{
		if(i == (MasterCFG->DataBufferLength - 1))
		{

			ConfigureACK(I2Cx->I2C, Disable);

            if(MasterCFG->StopCondition == StopConditionEnable)
            {
                GenerateStop(I2Cx,  StopConditionEnable);
            }
		}

		while(!GetFlagStatus(I2Cx->I2C, I2C_EV7));

		MasterCFG->DataBuffer[i] = I2Cx->I2C->DR;
	}

	//Re enable Acks for next transactions
	ConfigureACK(I2Cx->I2C, Enable);

}

/**================================================================
* @Fn          - MCAL_I2C_SlaveTx
* @brief       - Transmits a single byte of data as an I2C slave.
* @param [in]  - I2Cx  : Pointer to the I2C_Config_t structure, specifying the I2C peripheral.
* @param [in]  - data  : Byte of data to transmit.
* @retval       - N/A
* Note         - Used for Slave in Interrupt Mode , Not called explicitly.
**================================================================*/
void MCAL_I2C_SlaveTx(I2C_Config_t * I2Cx , uint8_t data)
{
	I2Cx->I2C->DR = data;
}


/**================================================================
* @Fn          - MCAL_I2C_SlaveRx
* @brief       - Receives a single byte of data as an I2C slave.
* @param [in]  - I2Cx : Pointer to the I2C_Config_t structure, specifying the I2C peripheral.
* @retval       - uint8_t : Byte of data received.
* Note         - Used for Slave in Interrupt Mode , Not called explicitly.
**================================================================*/
uint8_t MCAL_I2C_SlaveRx(I2C_Config_t * I2Cx)
{
	return I2Cx->I2C->DR;
}

/**================================================================
* @Fn          - MCAL_I2C_Interrupt_Enable
* @brief       - Enables specific I2C interrupts and sets callback functions.
* @param [in]  - I2Cx       : Pointer to the I2C_Config_t structure, specifying the I2C peripheral.
* @param [in]  - Interrupt  : Type of interrupt to enable.
* @param [in]  - IRQ_CallBack : Function pointer to the callback function for the interrupt.
* @retval       - N/A
* Note         - Configures I2C interrupt settings and registers callback functions for different events.
**================================================================*/
void MCAL_I2C_Interrupt_Enable(I2C_Config_t * I2Cx, Interruptx Interrupt , void ( * P_IRQEvent_CallBack)(void))
{
	if(Interrupt > DataByteTransferFinishedInterrupt)
	{
		I2Cx->I2C->CR2 |= I2C_CR2_ITBUFEN;
	}
	else
	{
		I2Cx->I2C->CR2 |= I2C_CR2_ITEVTEN;
	}

	if(I2Cx->I2C == I2C1)
		p_IRQ_callback_I2C1[Interrupt] = P_IRQEvent_CallBack;
	else
		p_IRQ_callback_I2C2[Interrupt] = P_IRQEvent_CallBack;


}

/**================================================================
* @Fn          - MCAL_I2C_Interrupt_Disable
* @brief       - Disables specific I2C interrupts.
* @param [in]  - I2Cx       : Pointer to the I2C_Config_t structure, specifying the I2C peripheral.
* @param [in]  - Interrupt  : Type of interrupt to disable.
* @retval       - N/A
* Note         - Disables I2C interrupt settings.
**================================================================*/
void MCAL_I2C_Interrupt_Disable(I2C_Config_t * I2Cx, Interruptx Interrupt)
{
	if(I2Cx->I2C == I2C1)
	{
		p_IRQ_callback_I2C1[Interrupt] = NULL;

		if(p_IRQ_callback_I2C1[TransmitterBufferEmpty] || p_IRQ_callback_I2C1[ReceiverBufferNotEmpty])
		{
			I2Cx->I2C->CR2 &= ~I2C_CR2_ITBUFEN;
		}
		else
		{
			for(int i = 0 ; i < ReceiverBufferNotEmpty ; i++)
			{
				if(p_IRQ_callback_I2C1[i] != NULL)
				{
					return;
				}
			}
			I2Cx->I2C->CR2 &= ~I2C_CR2_ITEVTEN;
		}
	}
	else
	{
		p_IRQ_callback_I2C2[Interrupt] = NULL;

		if(p_IRQ_callback_I2C2[TransmitterBufferEmpty] || p_IRQ_callback_I2C2[ReceiverBufferNotEmpty])
		{
			I2Cx->I2C->CR2 &= ~I2C_CR2_ITBUFEN;
		}
		else
		{
			for(int i = 0 ; i < ReceiverBufferNotEmpty ; i++)
			{
				if(p_IRQ_callback_I2C2[i] != NULL)
				{
					return;
				}
			}
			I2Cx->I2C->CR2 &= ~I2C_CR2_ITEVTEN;
		}
	}


}
/**************************************************************************************************************************
===============================================
*               I2C ISR functions
*===============================================
*/
// Overriding ISR of I2Cx

void I2C1_EV_IRQHandler(void)
{
    I2C_IRQHandler(I2C1, p_IRQ_callback_I2C1);

}

void I2C2_EV_IRQHandler(void)
{
    I2C_IRQHandler(I2C2, p_IRQ_callback_I2C2);
}
