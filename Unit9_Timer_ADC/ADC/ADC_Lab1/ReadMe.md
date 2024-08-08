# Lab 1: ADC Conversion with 7-Segment Display

This lab demonstrates the use of the ATmega32's ADC to read an analog input from a potentiometer and display the result on a BCD 7-segment display.

### Overview

- **Microcontroller**: ATmega32
- **Clock Frequency**: 8 MHz
- **ADC Configuration**:
  - Clock Prescaler: 128
  - Conversion Mode: Single Conversion
  - Data Adjustment: Right Adjusted
  - Input Channel: 0
  - Reference Voltage: Internal

### Hardware Setup

- **Potentiometer**: Connect to `ADC Channel 0` to provide input voltage (0-5V).
- **BCD 7-Segment Display**: Connect to `PORTC` and `PORTD` to show the ADC value.

### Main Steps

1. Initialize GPIO for input and output.
2. Configure the ADC settings.
3. Start ADC conversion.
4. Output the ADC result to the display.

### Usage

Compile and upload the code to your ATmega32. Adjust the potentiometer to change the input voltage, and view the ADC result on the 7-segment display.

### Requirements

- ATmega32 Microcontroller
- AVR GCC Compiler
- Potentiometer and BCD 7-segment display

### Simulation Results
![Lab1](https://github.com/user-attachments/assets/8e5c715e-7d1f-42fb-9dd3-d9d89045bb3c)
