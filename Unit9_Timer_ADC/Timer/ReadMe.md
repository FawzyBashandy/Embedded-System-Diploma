# ATmega32 Timer0 Driver

## Overview

This project provides a driver for the Timer0 module of the ATmega32 microcontroller. It includes an example demonstrating how to initialize the timer, configure it for compare match mode, and handle interrupts.

## Features

- Support for different timer operation modes: Normal, Phase Correct PWM, Clear on Compare Match, and Fast PWM.
- Configurable clock source with options for prescaling and external clock.
- Support for Compare Match and Overflow interrupts.
- Callback mechanism for handling timer interrupts.

## Prerequisites

- **Hardware**: ATmega32 microcontroller, development board with GPIO access.
- **Software**: AVR-GCC, AVR-Libc, AVRDUDE (for programming), Atmel Studio (optional).

## File Structure

- **ATmega32_Timer0.c**: Implementation of the Timer0 driver.
- **ATmega32_Timer0.h**: Header file defining the API and configuration structures.
- **main.c**: Example project demonstrating the use of the Timer0 driver.

## Usage

### Initialization

1. **Include the necessary headers** in your application:

    ```c
    #include "ATmega32_GPIO_Driver.h"
    #include "ATmega32_Timer0.h"
    ```

2. **Define the CPU frequency** at the top of your source file:

    ```c
    #define F_CPU 1000000UL
    ```

3. **Set up the Timer0 configuration**:

    ```c
    Timer0_Config_t timerCFG;
    timerCFG.ClockSource = Timer_PreScaler_64;
    timerCFG.OperationMode = ClearOnCompareMatchMode;
    timerCFG.CompareMode = Timer_COM_Disconnected;
    timerCFG.OverFlowInterrupt = Timer_TOI_Disable;
    timerCFG.CompareMatchInterrupt = Timer_TOCI_Enable;
    ```

4. **Initialize the timer** and set the compare value:

    ```c
    MCAL_TIMER0_SetCompare(253);
    MCAL_TIMER0_Init(&timerCFG);
    ```

5. **Configure the GPIO**:

    ```c
    GPIOA->DDR = 0xFF;
    GPIOB->DDR = 0x8; // Set PB3 as output
    ```

6. **Set up the interrupt callback**:

    ```c
    MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(CompareOnMatchCallback);
    ```

### Running the Example

1. **Build the project** using your preferred IDE or the command line with AVR-GCC.
2. **Upload the compiled binary** to the ATmega32 using AVRDUDE or your preferred programming tool.
3. **Observe the behavior**: The `CompareOnMatchCallback` will toggle the GPIO pin PB3 and increment the PORTA value every 62 compare matches.

## API Documentation

### Initialization

- **`eStatus_t MCAL_TIMER0_Init(Timer0_Config_t* timerCFG);`**  
  Initializes the Timer0 module with the specified configuration.

- **`eStatus_t MCAL_TIMER0_Stop();`**  
  Stops the Timer0 by disabling the clock source.

### Counter and Compare Value

- **`eStatus_t MCAL_TIMER0_GetCompare(uint8_t* compareVal);`**  
  Gets the current compare value.

- **`eStatus_t MCAL_TIMER0_SetCompare(uint8_t compareVal);`**  
  Sets the compare value.

- **`eStatus_t MCAL_TIMER0_GetCounter(uint8_t* counterVal);`**  
  Gets the current counter value.

- **`eStatus_t MCAL_TIMER0_SetCounter(uint8_t counterVal);`**  
  Sets the counter value.

### Overflow

- **`eStatus_t MCAL_TIMER0_GetOverflow(uint32_t* overflowVal);`**  
  Gets the overflow counter value.

- **`eStatus_t MCAL_TIMER0_SetOverflow(uint32_t overflowVal);`**  
  Sets the overflow counter value.

### Interrupts

- **`void MCAL_TIMER0_CALLBACK_Overflow_INTERRUPT(void (*callback)(void));`**  
  Registers a callback for the overflow interrupt.

- **`void MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(void (*callback)(void));`**  
  Registers a callback for the compare match interrupt.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.

