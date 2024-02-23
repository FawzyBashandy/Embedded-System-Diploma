# ATMega32 Button Controlled LEDs

This repository contains an ATMega32 microcontroller-based application demonstrating a simple interaction between a button input and LED outputs using GPIO pins.

## Prerequisites

- AVR-GCC compiler
- An ATMega32 microcontroller

## Description

The main program initializes one of PORTC's pins as an input for the button and all pins of PORTA as outputs for LEDs. It implements a loop where LEDs connected to PORTA are toggled in sequence based on the button press on PORTC.

### GPIO Pins Configuration

- `PORTA` pins are configured as output pins to control LEDs.
- `PINC1` is configured as an input pin with a pull-up resistor for the button.

### Functionality

Upon pressing the button connected to `PINC1`, the application behaves as follows:

1. If `flag` is 0 (initial state), it sequentially sets each bit on `PORTA` from bit 0 to bit 7, increasing `counter` after each bit is set.
2. Once all bits on `PORTA` have been set (`counter` reaches 8), `flag` is set to 1.
3. If `flag` is 1, it sequentially clears each bit on `PORTA` from the last set bit back to bit 0, decreasing `counter` after each bit is cleared.
4. Once all bits on `PORTA` have been cleared (`counter` reaches -1), `flag` is set back to 0.

This cycle creates an interactive "running lights" effect controlled by the button press.

### Simulation Video
[**Here**](https://drive.google.com/file/d/1n7qXFrhWFHQgQ0s5j25GRZJe5OsgQM1_/view?usp=drive_link)
