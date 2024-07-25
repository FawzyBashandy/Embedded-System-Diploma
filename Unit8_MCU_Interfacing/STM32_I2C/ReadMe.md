# STM32F103C6 I2C and E2PROM Driver

## Overview

This project provides a driver for interfacing with an E2PROM using the I2C protocol on the STM32F103C6 microcontroller. The driver includes both E2PROM-specific functions and a generic I2C driver. This README provides an overview of the provided code, how to use it, and its structure.

## File Structure

- `E2PROM_Driver.c` and `E2PROM_Driver.h`: These files contain the implementation and header definitions for the E2PROM driver.
- `STM32_F103C6_I2C_Driver.h` and `STM32_F103C6_I2C_Driver.c`: These files contain the implementation and header definitions for the I2C driver.
- `application.c`: Contains example usage of the E2PROM driver.
## I2C Driver

### Functions

1. **`void MCAL_I2C_Init(I2C_Config_t *I2Cx);`**
   - Initializes the specified I2C instance with configuration settings.

2. **`void MCAL_I2C_DeInit(I2C_Config_t *I2Cx);`**
   - Deinitializes the specified I2C instance.

3. **`void MCAL_I2C_Master_TX(I2C_Config_t *I2Cx, sMasterTxRx_t *MasterCFG);`**
   - Transmits data as an I2C master.

4. **`void MCAL_I2C_Master_RX(I2C_Config_t *I2Cx, sMasterTxRx_t *MasterCFG);`**
   - Receives data as an I2C master.

5. **`void MCAL_I2C_SlaveTx(I2C_Config_t *I2Cx, uint8_t data);`**
   - Sends data as an I2C slave.

6. **`uint8_t MCAL_I2C_SlaveRx(I2C_Config_t *I2Cx);`**
   - Receives data as an I2C slave.

7. **`void MCAL_I2C_Interrupt_Enable(I2C_Config_t *I2Cx, Interruptx Interrupt, void (*P_IRQEvent_CallBack)(void));`**
   - Enables specified I2C interrupts.

8. **`void MCAL_I2C_Interrupt_Disable(I2C_Config_t *I2Cx, Interruptx Interrupt);`**
   - Disables specified I2C interrupts.

## E2PROM Driver

### Functions

1. **`void HAL_E2PROM_Init(void);`**
   - Initializes the E2PROM by configuring I2C settings and addresses.

2. **`void HAL_E2PROM_WriteData(uint16_t MemoryAddress, uint8_t SlaveAddress, uint8_t *data, uint32_t dataLen);`**
   - Writes data to the E2PROM. Parameters include memory address, slave address, data pointer, and data length.

3. **`void HAL_E2PROM_ReadData(uint16_t MemoryAddress, uint8_t SlaveAddress, uint8_t *data, uint32_t dataLen);`**
   - Reads data from the E2PROM. Parameters include memory address, slave address, data pointer, and data length.

## Example Usage

The `application.c` file demonstrates how to initialize the E2PROM, write to it, and read from it.

### Example Code

```c
#include <RCC/STM32F103x6_RCC_Driver.h>
#include <E2PROM/E2PROM_Driver.h>

void clock_init();
int main(void)
{
    uint8_t buffer[5] = {0x1, 0x2, 0x3, 0x4, 0x5};
    uint8_t dataIn[5];

    // Initialize system clock
    clock_init();
    
    // Initialize E2PROM
    HAL_E2PROM_Init();

    // Write data to E2PROM
    HAL_E2PROM_WriteData(0x0000, 0xA0, buffer, sizeof(buffer));

    // Read data from E2PROM
    HAL_E2PROM_ReadData(0x0000, 0xA0, dataIn, sizeof(dataIn));

    // Application code
}
