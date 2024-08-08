# Lab 3: ADC Temperature Measurement with LM35 Sensor

This lab demonstrates the use of the ATmega32's ADC to measure temperature using an LM35 sensor. The ADC reads the analog voltage from the LM35, converts it to Celsius, and displays the result on a BCD 7-segment display.

### Overview

- **Microcontroller**: ATmega32
- **Clock Frequency**: 1 MHz
- **ADC Configuration**:
  - Clock Prescaler: 128
  - Conversion Mode: Auto Trigger Conversion
  - Trigger Event: End of Conversion Flag
  - Data Adjustment: Right Adjusted
  - Input Channel: 0
  - Reference Voltage: Internal

### Hardware Setup

- **LM35 Temperature Sensor**: Connect to `ADC Channel 0` to provide an analog voltage proportional to temperature.
- **BCD 7-Segment Display**: Connect to `PORTD` to show the converted temperature in Celsius.

### Main Steps

1. Initialize GPIO for input and output.
2. Configure the ADC settings with auto-trigger conversion.
3. Use a callback function to handle the end of conversion, converting the ADC result to Celsius.
4. Output the temperature value to the display.

### Usage

Compile and upload the code to your ATmega32. The LM35 sensor provides a voltage that the ADC reads and converts to a temperature value in Celsius, displayed on the 7-segment display. The conversion accounts for the voltage characteristics of the LM35 sensor.

### Requirements

- ATmega32 Microcontroller
- AVR GCC Compiler
- LM35 Temperature Sensor
- BCD 7-segment display

### Notes

- The LM35 outputs 10 mV per degree Celsius. The conversion function divides the ADC result by 4 to match this scaling.
