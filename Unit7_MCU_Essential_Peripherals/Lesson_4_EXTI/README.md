# STM32F103x6 EXTI and LCD Driver Implementation

This project is a detailed exploration and implementation of External Interrupts (EXTI) and LCD interfacing on the STM32F103x6 microcontroller, showcasing the versatility and power of STM32 microcontrollers for real-world applications.

## Project Insight

Developed as a hands-on project, this repository contains custom drivers for managing EXTI (External Interrupts) and for controlling an LCD display. The motivation behind this work was to understand the intricacies of microcontroller peripherals and to demonstrate how external signals can interact with microcontroller units (MCUs) to trigger meaningful actions, such as displaying information on an LCD.

### Key Features

- **Custom EXTI Driver**: A robust implementation that allows the STM32F103x6 MCU to respond to external events. This driver supports various trigger conditions, including rising, falling, and both edges, making it adaptable for a wide range of external signals.
- **LCD Driver**: A flexible driver to interface with character LCDs in 4-bit mode. This driver encompasses initialization sequences, command handling, and data display functions, offering a comprehensive toolkit for LCD manipulation.
- **Integration and Event Handling**: Demonstrates the integration of EXTI and LCD drivers to create a responsive system that updates the LCD display in response to external triggers.

### Technical Achievements

- **Low-Level Peripheral Management**: Direct manipulation of MCU registers to control peripheral behavior, offering a deep understanding of MCU operation.
- **Software Abstraction**: Creation of high-level interfaces for complex hardware interactions, making it easier to reuse code across different projects.
- **Real-Time Response**: Implementation of interrupt service routines (ISRs) to achieve real-time responsiveness to external events.

### Efforts and Learning Outcomes

This project involved:

- Detailed study of the STM32F103x6 MCU datasheet and reference manual to understand peripheral functionalities.
- Design and implementation of software drivers from scratch, emphasizing code clarity, efficiency, and reusability.
- Debugging and testing to ensure reliable operation under various conditions.
- Learning best practices in embedded software development, including code organization, peripheral initialization, and interrupt handling.

## Conclusion

Through the development of EXTI and LCD drivers for the STM32F103x6 microcontroller, this project not only highlights the capabilities of STM32 MCUs but also serves as a testament to the power of embedded systems in interfacing with the physical world. It stands as a comprehensive example for enthusiasts and professionals looking to deepen their understanding of microcontroller programming and peripheral management.

### Simulation Video
[**Here**](https://drive.google.com/file/d/1OD27O1oyaNoiTGglQmCZ4f-UI7jogYxh/view?usp=drive_link)