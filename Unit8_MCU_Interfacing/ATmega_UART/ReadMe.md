# ATmega32 UART Driver

## Overview

This project demonstrates the implementation of a UART driver for the ATmega32 microcontroller. It includes functions to initialize the UART, send and receive characters, and send and receive strings. Additionally, a sample application is provided that initializes an LCD and uses the UART driver to echo received characters and display them on the LCD.

## File Structure

- `main.c`: Contains the main program that initializes the LCD and UART, and echoes received characters to both the UART and LCD.
- `ATmega32_UART_Driver.h`: Header file for the UART driver, containing macros, function prototypes, and documentation.
- `ATmega32_UART_Driver.c`: Source file for the UART driver, implementing the functions declared in the header file.

## UART Driver

### Initialization

The UART is initialized with the following settings:
- Baud rate: 9600
- Character size: 8 bits
- Parity: None
- Stop bit: 1

### Functions

- `void MCAL_USART_Init(void)`: Initializes the UART module.
- `void MCAL_USART_Send_Char(uint8_t data)`: Sends an 8-bit character through the UART.
- `uint8_t MCAL_USART_Get_Char(void)`: Receives an 8-bit character from the UART.
- `void MCAL_USART_Send_String(uint8_t* string)`: Sends a string through the UART.
- `void MCAL_USART_Get_String(uint8_t* buffer, uint8_t bufferSize)`: Receives a string through the UART.

## Main Program

### Description

The main program initializes the LCD and UART, then continuously receives characters from the UART, echoes them back through the UART, and displays them on the LCD.

### Functions

- `void LCD_Init()`: Initializes the LCD with specific settings.
- `void main(void)`: The main function that runs the program.

### Code

```c
#define F_CPU 8000000ul
#include "ATmega32_GPIO_Driver.h"
#include "ATmega32_UART_Driver.h"
#include "ATmega32_LCD_Driver.h"

void Delay(uint32_t time) {
    vuint8_t i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 255; j++);
}

void LCD_Init();
void main(void) {
    char inputBuffer[256], input;
    LCD_Init();
    MCAL_USART_Init();
    MCAL_USART_Get_String(inputBuffer, 256);
    MCAL_USART_Send_String((uint8_t*)inputBuffer);
    while (1) {
        input = MCAL_USART_Get_Char();
        MCAL_USART_Send_Char(input);
        HAL_LCD_WRITE_CHAR(&LCD, input);
    }
}

void LCD_Init() {
    LCD.LCD_dataPort = GPIOA;
    LCD.LCD_ctrlPort = GPIOB;
    LCD.LCD_Mode = LCD_MODE_4BIT;
    LCD.dataPins = LCD_DPINS_HIGHER_4PINS;
    LCD.ctrlPins = LCD_CPINS_G2;
    HAL_LCD_Init(&LCD);
}
```
### Usage
1- Connect the ATmega32 microcontroller to a UART terminal program on your PC.

2- Compile and upload the code to the ATmega32.

3- Open the UART terminal and set the baud rate to 9600.

4- Type characters into the terminal; they will be echoed back and displayed on the LCD.

### Simulation Video
[**Click Here[Drive]**](https://drive.google.com/file/d/1MAQxoXDZ7s-Q-1rW7ZsIOBtrUpXPrsdX/view?usp=sharing)
