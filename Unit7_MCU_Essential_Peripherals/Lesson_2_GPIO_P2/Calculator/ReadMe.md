# AVR-Based Calculator with LCD and Keypad

This project is a simple, interactive calculator designed for AVR microcontrollers. It leverages an LCD for displaying inputs and calculation results, and a keypad for user inputs, enabling basic arithmetic operations such as addition, subtraction, multiplication, and division.

## Features

- **LCD Display**: Dynamically shows both the operations being performed and the results of calculations, enhancing user interaction.
- **Keypad Input**: Facilitates easy data entry for numbers and arithmetic operators, making the calculator intuitive to use.
- **Arithmetic Operations**: Capable of performing addition (`+`), subtraction (`-`), multiplication (`*`), and division (`/`), covering the fundamental operations needed for basic calculations.
- **Interactive Controls**: Includes functionality to clear the current operation and prepare the device for a new calculation, ensuring seamless continuity in usage.

## Code Overview

- **Initialization**: Sets up the LCD and keypad, preparing the devices for operation.
- **User Input Handling**: Actively listens for inputs from the keypad, distinguishing between numeric entries, operation commands, and control commands.
- **Operation Execution**: Processes the entered operands and operator upon command, computing the result and displaying it on the LCD.
- **Reset and Clear**: Allows the user to clear the current operation and reset the display, readying the device for a new calculation.

## Usage

- **Entering Numbers**: Numbers can be directly input using the keypad.
- **Performing Operations**: The calculator recognizes `+`, `-`, `*`, and `/` keys as operations to be performed on the entered numbers.
- **Calculating Results**: Pressing `=` commands the calculator to compute and display the result of the operation.
- **Starting Over**: The `!` key serves to clear the display and any entered data, allowing for a new calculation to be started without needing to manually erase previous entries.


### Simulation Video
[**Click Here**](https://drive.google.com/file/d/1ruCqIUQDqUTKVbpBIOCoJhSCE9KuYu8e/view?usp=drive_link)
