# STM32F103C6 UART and SPI Communication Example

This project demonstrates the implementation of UART and SPI communication protocols on the STM32F103C6 microcontroller, showcasing both master and slave configurations for versatile embedded system applications.

## Project Overview

The repository contains custom drivers for UART and SPI peripherals, providing a hands-on example of how these communication interfaces can be utilized in real-world scenarios. The project includes initialization routines and interrupt-driven data handling for both UART and SPI, highlighting the flexibility and robustness of STM32 MCUs in embedded systems.

### Key Features

- **Custom UART Driver**: Configured to operate at a baud rate of 115200 with support for both transmission and reception modes. The UART driver can operate in interrupt-driven mode for the master configuration, enabling efficient data exchange between the MCU and external devices.
- **Custom SPI Driver**: Implemented in both master and slave configurations. The SPI driver supports full-duplex communication with interrupt-driven reception in the slave mode, demonstrating bidirectional data transfer capabilities.
- **Master/Slave Configuration**: Easily switch between master and slave modes for SPI communication by modifying a single define (`MCU_Act_As_Master` or `MCU_Act_As_Slave`).

### Application Workflow

The application operates as follows:

1. **UART Input**: Data is received from a UART terminal connected to USART1.
2. **SPI Communication (SOC1 to SOC2)**: The data received via UART is transmitted from the master MCU (SOC1) to a slave MCU (SOC2) using SPI communication.
3. **SPI Communication (SOC2 to SOC1)**: Data is then transmitted back from the slave MCU (SOC2) to the master MCU (SOC1) over SPI.
4. **UART Output**: Finally, the received data is sent back to the UART terminal for display.

### Technical Details

- **Peripheral Initialization**: Detailed initialization sequences for GPIO, UART, and SPI peripherals, ensuring proper configuration and reliable operation.
- **Interrupt Handling**: Implementation of interrupt service routines (ISRs) for UART and SPI, optimizing data handling efficiency and real-time responsiveness.
- **Software Abstraction**: High-level functions encapsulate complex hardware interactions, enhancing code readability and facilitating code reuse across different projects.

### Efforts and Learning Outcomes

This project involved:

- In-depth study of the STM32F103C6 MCU datasheet and reference manual to understand UART and SPI peripheral functionalities.
- Design and development of efficient and reusable software drivers, emphasizing best practices in embedded software development.
- Extensive testing and debugging to verify the robustness and reliability of UART and SPI communication under various operating conditions.
- Acquisition of practical skills in managing interrupts, peripheral configurations, and data exchange protocols in embedded systems.

## Conclusion

By implementing UART and SPI communication drivers on the STM32F103C6 microcontroller, this project exemplifies the versatility and power of STM32 MCUs in embedded applications. It serves as a valuable resource for developers looking to integrate communication protocols into their own projects and deepen their understanding of microcontroller programming.

### Simulation Video
[**Watch here (Drive)**](https://drive.google.com/file/d/1NxByMoAbcz5-iPkEoW7pTYXIhhEbFDDV/view?usp=drive_link)
