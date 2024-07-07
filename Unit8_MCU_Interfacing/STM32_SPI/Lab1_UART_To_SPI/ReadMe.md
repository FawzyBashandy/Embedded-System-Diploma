# STM32F103C6 UART and SPI Driver Example

This project provides a comprehensive implementation of UART and SPI drivers on the STM32F103C6 microcontroller, highlighting the capabilities of STM32 MCUs for communication protocols in embedded systems.

## Project Insight

Developed to demonstrate the practical application of UART and SPI communication, this repository includes custom drivers for managing UART and SPI peripherals. The motivation behind this project was to understand the detailed workings of these communication protocols and how to effectively implement them in real-world scenarios.

### Key Features

- **Custom UART Driver**: Enables communication between the STM32F103C6 MCU and other devices via UART at a baud rate of 115200. This driver supports interrupt-driven data reception, ensuring efficient data handling.
- **Custom SPI Driver**: Facilitates SPI communication in master mode, allowing the MCU to interface with SPI-compatible devices. The driver supports full-duplex communication and can be configured for different SPI configurations.
- **Master/Slave Configuration**: The project can be easily switched between master and slave modes for SPI communication by modifying a single configuration define.

### Application Workflow

The application operates as follows:

1. **UART Input**: Data is received from a UART terminal connected to USART1 on the STM32F103C6 MCU.
2. **UART to SOC1**: Data received via UART is transmitted to SOC1 (System on Chip 1).
3. **SPI Communication (SOC1 to SPI Debugger)**: SOC1 sends data to a SPI debugger module in Proteus simulation using SPI communication.
4. **SPI Debugger Output**: Data received by the SPI debugger module in Proteus is displayed or further processed in the simulation environment.

### Technical Achievements

- **Low-Level Peripheral Management**: Direct control over MCU registers to manage peripheral behavior, providing an in-depth understanding of hardware operations.
- **Interrupt Handling**: Implementation of interrupt service routines (ISRs) for UART to achieve real-time responsiveness to incoming data.
- **Software Abstraction**: Creation of high-level functions for UART and SPI communication, simplifying the complexity of low-level hardware interactions and making the code reusable across different projects.

### Efforts and Learning Outcomes

This project involved:

- Thorough examination of the STM32F103C6 MCU datasheet and reference manual to grasp the functionalities of UART and SPI peripherals.
- Design and development of custom software drivers, focusing on clarity, efficiency, and reusability of the code.
- Extensive debugging and testing to ensure reliable and robust operation under various conditions.
- Acquiring best practices in embedded software development, including proper peripheral initialization, interrupt management, and code organization.

## Conclusion

The development of UART and SPI drivers for the STM32F103C6 microcontroller demonstrates the practical application and versatility of STM32 MCUs in embedded communication. This project serves as a valuable example for enthusiasts and professionals looking to deepen their understanding of microcontroller programming and peripheral interfacing.

### Simulation Video
[**Watch here (Drive)**](https://drive.google.com/file/d/1dG6XqzclpIfzP2KRoWBwOOaPLKBkABKe/view?usp=drive_link)
