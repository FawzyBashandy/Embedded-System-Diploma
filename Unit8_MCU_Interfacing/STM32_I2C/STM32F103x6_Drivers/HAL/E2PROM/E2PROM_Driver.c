/*
 * E2PROM_Driver.c
 *
 *  Created on: Mar 15, 2024
 *      Author: Fawzy Bashandy
 */

#include <E2PROM/E2PROM_Driver.h>

/**================================================================
* @Fn          - HAL_E2PROM_Init
* @brief       - Initializes the I2C peripheral and configures the EEPROM device.
* @param [in]  - None
* @retval       - N/A
* Note         - Sets up I2C configuration with parameters such as clock speed,
*                clock stretching, and general call address. Configures EEPROM
*                device address and initializes the I2C peripheral for communication.
**================================================================*/
void HAL_E2PROM_Init(void)
{
	//Master Init that will access E2PROM
	I2C_CFG.ClockSpeed 				= I2C_ClockSpeed_SM100KHZ;
	I2C_CFG.ClockStretching 		= I2C_ClockStretching_Enable;
	I2C_CFG.GeneralCallAddress 		= I2C_GeneralCallAddress_Enable;
	I2C_CFG.I2C						= I2C1;
	I2C_CFG.Mechanism				= I2CPolling;
	I2C_CFG.Mode					= I2C_Mode_SM;

	//Address Config
	DeviceAddress.Length		  	= SevenBits;
	DeviceAddress.Mode			  	= DualAddress;
	DeviceAddress.Primary_Address 	= 0x30;
	DeviceAddress.Secondary_Address = 0x33;
	I2C_CFG.SlaveAddress = &DeviceAddress;

	MCAL_I2C_Init(&I2C_CFG);
}

/**================================================================
 * @Fn          - HAL_E2PROM_WriteData
 * @brief       - Writes data to the EEPROM at a specified memory address.
 * @param [in]  - MemoryAddress  : The memory address in the EEPROM where data will be written.
 * @param [in]  - SlaveAddress   : The I2C address of the EEPROM.
 * @param [in]  - data           : Pointer to the buffer containing the data to be written.
 * @param [in]  - dataLen        : Length of the data to be written.
 * @retval       - N/A
 * Note         - Constructs a buffer containing the memory address and data.
 *                Performs an I2C master transmission to write the data to the EEPROM,
 *                including generating a start condition and a stop condition.
 **================================================================*/
void HAL_E2PROM_WriteData(uint16_t MemoryAddress,uint8_t SlaveAddress ,uint8_t *data , uint32_t dataLen)
{
	uint8_t buffer[256] = {MemoryAddress >> 8 , MemoryAddress};
	for(int i = 2; i<(dataLen +2);i++)
	{
		buffer[i]=*data;
		data++;
	}
	MasterCFG.AddressCFG.Length 		 	= SevenBits;
	MasterCFG.AddressCFG.Mode   		  	= SingleAddress;
	MasterCFG.AddressCFG.Primary_Address 	= SlaveAddress;
	MasterCFG.DataBuffer					= buffer;
	MasterCFG.DataBufferLength				= dataLen + 2;
	MasterCFG.Direction						= MasterTransmits;
	MasterCFG.StartCondition				= NormalStart;
	MasterCFG.StopCondition					= StopConditionEnable;
	MCAL_I2C_Master_TX(&I2C_CFG,&MasterCFG);
}

/**================================================================
* @Fn          - HAL_E2PROM_ReadData
* @brief       - Reads data from the EEPROM from a specified memory address.
* @param [in]  - MemoryAddress  : The memory address in the EEPROM from which data will be read.
* @param [in]  - SlaveAddress   : The I2C address of the EEPROM.
* @param [in]  - data           : Pointer to the buffer where read data will be stored.
* @param [in]  - dataLen        : Length of the data to be read.
* @retval       - N/A
* Note         - Performs an I2C master transmission to send the memory address, then
*                performs an I2C master reception to read the data from the EEPROM,
*                including generating a repeated start condition and a stop condition.
**================================================================*/
void HAL_E2PROM_ReadData(uint16_t MemoryAddress,uint8_t SlaveAddress ,uint8_t *data , uint32_t dataLen)
{
	uint8_t buffer[2] = {MemoryAddress >> 8 , MemoryAddress};
	MasterCFG.AddressCFG.Length 		 	= SevenBits;
	MasterCFG.AddressCFG.Mode   		  	= SingleAddress;
	MasterCFG.AddressCFG.Primary_Address 	= SlaveAddress;
	MasterCFG.DataBuffer					= buffer;
	MasterCFG.DataBufferLength				= 2;
	MasterCFG.Direction						= MasterTransmits;
	MasterCFG.StartCondition				= NormalStart;
	MasterCFG.StopCondition					= StopConditionDisable;
	MCAL_I2C_Master_TX(&I2C_CFG,&MasterCFG);

	MasterCFG.DataBuffer 					= data;
	MasterCFG.DataBufferLength 				= dataLen;
	MasterCFG.Direction						= MasterReceives;
	MasterCFG.StartCondition				= RepeatedStart;
	MasterCFG.StopCondition					= StopConditionEnable;
	MCAL_I2C_Master_RX(&I2C_CFG,&MasterCFG);
}


