# GPIO Lab1

This folder contains an embedded application developed using STM32CubeIDE for an STM32 microcontroller. The application demonstrates basic input and output functionality using GPIO pins.

## Prerequisites

- STM32CubeIDE
- STM32 microcontroller

## Description

The main program (`main.c`) initializes the GPIO pins and implements a simple logic for toggling LEDs based on button presses. The program continuously checks the status of two input pins (`PA1` and `PA13`) connected to buttons and toggles two output pins (`PB1` and `PB13`) connected to LEDs accordingly.

### GPIO Pins Configuration

- `PA1` is configured as a floating input pin.
- `PA13` is configured as a floating input pin.
- `PB1` is configured as a push-pull output pin.
- `PB13` is configured as an open-drain output pin.

### Functionality

The application follows the following logic:

1. If button (single pressing) connected to `PA1` is pressed, it toggles the LED connected to `PB1`.
2. If button (multi pressing) connected to `PA13` is pressed, it toggles the LED connected to `PB13`.
3. The LEDs are initially turned off.
4. There is a delay of 1 unit of time between each iteration of the main loop.

### Simulation Video
[**Here**](https://drive.google.com/file/d/12QxWVVZ6qiqf0cJcx6yAeYenKvpFMKsC/view?usp=drive_link)
