# Lab 2: ADC Conversion with Callback Function

This lab demonstrates the use of the ATmega32's ADC with a callback function to handle the end of conversion, reading an analog input from a potentiometer and displaying the result on a BCD 7-segment display.

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
3. Set a callback function for the end of conversion.
4. Start ADC conversion and handle results in the callback.

### Usage

Compile and upload the code to your ATmega32. Adjust the potentiometer to change the input voltage, and view the ADC result on the 7-segment display. The conversion result is processed using an end-of-conversion callback function.

### Requirements

- ATmega32 Microcontroller
- AVR GCC Compiler
- Potentiometer and BCD 7-segment display
