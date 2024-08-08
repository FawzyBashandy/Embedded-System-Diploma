# Lab 5: ADC Voltage Percentage Measurement with LCD Display

This lab demonstrates how to use the ATmega32's ADC to measure the input voltage from a potentiometer and calculate its percentage relative to the reference voltage. The result is displayed on an LCD.

### Overview

- **Microcontroller**: ATmega32
- **Clock Frequency**: 1 MHz
- **ADC Configuration**:
  - Clock Prescaler: 128
  - Conversion Mode: Auto Trigger Conversion
  - Trigger Event: End of Conversion Flag
  - Data Adjustment: Right Adjusted
  - Input Channel: 0
  - Reference Voltage: AVCC

### Hardware Setup

- **Potentiometer**: Connect to `ADC Channel 0` to provide an input voltage.
- **LCD Display**: Connect to `PORTB` to display the percentage of the input voltage relative to the reference voltage.

### Main Steps

1. Initialize GPIO for input and output.
2. Configure the ADC settings with auto-trigger conversion.
3. Initialize the LCD.
4. Use a callback function to handle the end of conversion, calculate the percentage of the input voltage relative to the reference voltage, and display the result on the LCD.

### Usage

Compile and upload the code to your ATmega32. Adjust the potentiometer to change the input voltage. The ADC reads this voltage, calculates the percentage relative to the reference voltage (AVCC), and displays the result on the LCD in percentage format.

### Requirements

- ATmega32 Microcontroller
- AVR GCC Compiler
- Potentiometer
- LCD Display
  
### Simulation Results
![Lab5](https://github.com/user-attachments/assets/a645e534-4391-4b20-bd9f-9dc363c446fd)

### Notes

- The reference voltage is set to AVCC (5V). The percentage calculation is based on the input voltage compared to this reference voltage.
- Ensure that the LCD is correctly connected and initialized for proper display of percentage values.
