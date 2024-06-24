# STM32 USART Driver

This repository contains a USART driver implementation for STM32F103C6 microcontroller series, developed by Fawzy Bashandy.

## Overview

The USART driver facilitates serial communication via UART (Universal Asynchronous Receiver/Transmitter) on STM32 microcontrollers. It supports both polling and interrupt-driven mechanisms for sending and receiving data.

## Features

- **Initialization:** Initialize USART peripheral with configurable baud rate, word length, parity, stop bits, and communication mode.
- **Sending Data:** Send data over USART using polling or interrupt mechanisms.
- **Receiving Data:** Receive data from USART using polling or interrupt mechanisms.
- **Error Handling:** Handle various USART errors like framing errors, parity errors, and overrun errors.
- **Interrupts:** Enable and manage USART interrupts for different events.
- **GPIO Configuration:** Automatically configure GPIO pins for USART transmission and reception.

## Repository Structure

The repository is structured as follows:

- `STM32_F103C6_USART_Driver.h`: Header file containing USART driver definitions, configurations, and function prototypes.
- `STM32_F103C6_USART_Driver.c`: Source file containing USART driver implementation.
- `BitMath.h`, `Platform_Types.h`, `STM32F103x6.h`: Header files for bit manipulation, platform types, and STM32F103C6 specific definitions.
- `STM32F103x6_GPIO_Driver.h`, `STM32F103x6_RCC_Driver.h`, `STM32F103x6_NVIC_Driver.h`: Header files for GPIO, RCC, and NVIC drivers respectively.
- `README.md`: This file, providing an overview, features, and usage instructions.

## Usage

To use the USART driver in your STM32F103C6 project:

1. Include `STM32_F103C6_USART_Driver.h` and other necessary headers in your project.
2. Configure the USART using `MCAL_USART_Init()` function with a properly filled `USART_Config_t` structure.
3. Use `MCAL_USART_SendData()` to send data and `MCAL_USART_ReceiveData()` to receive data.
4. Optionally, enable interrupts using `MCAL_USART_Enable_Interrupt()` and handle interrupt events in corresponding ISR (Interrupt Service Routine) functions.

### Example

```c
#include "STM32_F103C6_USART_Driver.h"

int main(void) {
    USART_Config_t usart_config;

    // Initialize USART configuration
    usart_config.USARTx = USARTx_Instance1;
    usart_config.TxRx_Mode = USART_TxRxMode_BOTH_TXRX;
    usart_config.BaudRate = USART_BaudRate_9600;
    usart_config.WordLength = USART_WordLength_8b;
    usart_config.Parity = USART_Parity_NONE;
    usart_config.StopBitsLength = USART_StopBitsLength_OneBit;
    usart_config.Mechanism_type = USART_MechanismType_Interrupt;

    MCAL_USART_Init(&usart_config);

    // Send and receive data
    uint16_t data;
    MCAL_USART_SendData(&usart_config, 'A');
    MCAL_USART_ReceiveData(&usart_config, &data);

    return 0;
}
```
### Simulation Video
[**Click Here[Drive]**](https://drive.google.com/file/d/1RJlbIZjAomuMTcFnbyDbEafJQ1cCTNDg/view?usp=sharing)
