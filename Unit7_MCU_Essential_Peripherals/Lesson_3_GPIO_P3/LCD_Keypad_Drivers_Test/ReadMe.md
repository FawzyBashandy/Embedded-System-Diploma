# STM32F103C6 GPIO Driver

This project provides a comprehensive General-Purpose Input/Output (GPIO) driver for the STM32F103C6 microcontroller. The driver is designed to facilitate easy and efficient use of GPIO functionality, allowing users to configure and control GPIO pins for a wide range of applications.

## Features

- **Pin Initialization**: Configure GPIO pins as input, output, analog, or alternate function modes with customizable configurations including pull-up/pull-down resistors and output speed.
- **Pin Read/Write**: Read the status of GPIO pins or an entire port, and write values to pins or an entire port with simple API calls.
- **Pin Toggling**: Easily toggle the state of GPIO pins.
- **Pin Locking**: Lock the configuration of GPIO pins to prevent unintended changes.
- **Clock Management**: Enable or disable GPIO port clocks to manage power consumption.

## Getting Started

### Prerequisites

- STM32F103C6 microcontroller
- Compatible Integrated Development Environment (IDE) such as STM32CubeIDE or Keil µVision
- Basic knowledge of C programming and microcontroller peripherals

### Installation

1. Clone this repository or download the source code.
2. Include the header and source files (`STM32_F103C6_GPIO_Driver.h` and `STM32_F103C6_GPIO_Driver.c`) in your project.
3. Ensure the STM32F103C6 Standard Peripheral Library is included in your project for necessary definitions and base support.

### Usage

1. **Clock Initialization**: Before using GPIO functionalities, enable the clock for the required GPIO port(s) using `Clock_Init()`.

    ```c
    Clock_Init();
    ```

2. **GPIO Initialization**: Configure GPIO pins using `MCAL_GPIO_Init()` by specifying the GPIO port and a configuration structure (`pinConfig_t`).

    ```c
    pinConfig_t pinConfig;
    pinConfig.pinNumber = GPIO_PIN_1;
    pinConfig.pinMode = GPIO_MODE_OUTPUT_PP;
    pinConfig.outputModeSpeed = GPIO_OUTPUT_SPEED_50MHZ;
    MCAL_GPIO_Init(GPIOA, &pinConfig);
    ```

3. **Reading and Writing**: Use `MCAL_GPIO_ReadPin()`, `MCAL_GPIO_WritePin()`, or their port-wide counterparts for pin manipulation.

    ```c
    // Write to a pin
    MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_STATUS_HIGH);
    
    // Read from a pin
    uint8_t pinStatus = MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
    ```

4. **Toggling Pins**: Toggle the state of a GPIO pin with `MCAL_GPIO_TogglePin()`.

    ```c
    MCAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
    ```

5. **Locking Configuration**: Prevent accidental changes to a pin's configuration using `MCAL_GPIO_LockPin()`.

    ```c
    MCAL_GPIO_LockPin(GPIOA, GPIO_PIN_1);
    ```

## Example

An example application toggling an LED based on a button press:

```c
int main(void)
{
    Clock_Init();
    GPIO_Init(); // Assume this configures an LED on PB1 and a Button on PA1
    
    while(1)
    {
        if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_STATUS_LOW)
        {
            MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
            while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_STATUS_LOW);
        }
    }
}
```

## Documentation
For **detailed API usage** and configurations, refer to comments in the header file (`STM32_F103C6_GPIO_Driver.h`) and the source file (`STM32_F103C6_GPIO_Driver.c`).
