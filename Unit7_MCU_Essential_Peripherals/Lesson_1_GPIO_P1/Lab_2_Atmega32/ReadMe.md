# ATMega32 Sequential LED Blinker with Buzzer Alert

This repository features a simple embedded application developed for the ATMega32 microcontroller. It demonstrates a sequential LED blinking pattern using GPIO pins on PORTD, with an additional buzzer alert on pin 4.

## Prerequisites

- AVR-GCC compiler
- An ATMega32 microcontroller

## Description

The main program (`Unit7_Section1.c`) initializes specific pins of PORTD as outputs for LEDs and configures pin 4 for a buzzer. It enters a loop where LEDs connected to pins 5 to 7 on PORTD are lit up sequentially, followed by activating the buzzer connected to pin 4, with a delay between each action.

### GPIO Pins Configuration

- `PORTD` pins 4 to 7 are configured as output pins. Pins 5 to 7 control LEDs, and pin 4 controls a buzzer.
- Each LED pin is set to high (LED on), followed by a delay, and then set to low (LED off) before moving to the next pin.
- After cycling through the LEDs, pin 4 is activated (buzzer on), followed by a delay, and then deactivated (buzzer off).

### Functionality

The application operates in the following sequence:

1. Sequentially sets each of the pins 5, 6, and 7 on `PORTD` to high, waits for a delay, and then clears the pin to low, moving to the next pin in sequence.
2. After clearing pin 7, it activates pin 4 (turning the buzzer on), waits for a delay, and then deactivates pin 4 (turning the buzzer off).
3. This creates a sequential LED blinking pattern from pin 5 to pin 7, with a buzzer alert at the end of each cycle.
4. The cycle repeats indefinitely, creating a continuous blinking pattern with periodic buzzer alerts.

### Simulation Video
[**Here**](https://drive.google.com/file/d/14-O6ZLAQzWc34-bSYq68Wd9yZdGwI_bj/view?usp=drive_link)
