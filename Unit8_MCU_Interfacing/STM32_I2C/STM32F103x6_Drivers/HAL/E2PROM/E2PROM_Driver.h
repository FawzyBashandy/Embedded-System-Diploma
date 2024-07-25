/*
 * STM32F103x6_E2PROM_Driver.h
 *
 *  Created on: Mar 15, 2024
 *      Author: Fawzy Bashandy
 */

#ifndef E2PROM_DRIVER_H_
#define E2PROM_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include <I2C/STM32F103x6_I2C_Driver.h>
#include <STM32F103C6.h>

//I2C_ConfigurationStructure
I2C_Config_t I2C_CFG;
sMasterTxRx_t MasterCFG;
sI2CAddress_t DeviceAddress;
/*===============================================
*                   E2PROM Ports
*===============================================
*/
#define E2PROM_SLAVE_ADDRESS        0x2A

/*
* ===============================================
* APIs Supported by "HAL E2PROM DRIVER"
* ===============================================
*/
void HAL_E2PROM_Init(void);
void HAL_E2PROM_WriteData(uint16_t MemoryAddress,uint8_t SlaveAddress ,uint8_t *data , uint32_t dataLen);
void HAL_E2PROM_ReadData(uint16_t MemoryAddress,uint8_t SlaveAddress ,uint8_t *data , uint32_t dataLen);
#endif /* E2PROM_DRIVER_H_ */
