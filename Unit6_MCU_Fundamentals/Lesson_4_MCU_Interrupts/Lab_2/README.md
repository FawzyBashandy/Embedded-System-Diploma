## Lab 2: External Interrupt Driver for Atmega32

This lab focuses on implementing an external interrupt driver for the Atmega32 microcontroller. The following external interrupts are utilized:

- External Interrupt 0 (INT0) - PD2 (IRQ occurs when any logical change is detected).
- External Interrupt 1 (INT1) - PD3 (IRQ occurs on the rising edge).
- External Interrupt 2 (INT2) - PB2 (IRQ occurs on the falling edge).

Additionally, there are three LEDs connected to PD5, PD6, and PD7 (referred to as led0, led1, and led2, respectively).

Each interrupt will turn on led0 for 1 second, while the main function ensures that all LEDs are turned off.

## Simulation Video

Watch the simulation video [here](https://github.com/FawzyBashandy/Embedded-System-Diploma/assets/131293631/9010be72-3feb-4657-b178-4814a6d0443e).
