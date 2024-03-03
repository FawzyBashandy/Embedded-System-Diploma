# STM32F103C6 Project: Keypad and 7-Segment Display Interface

This project demonstrates the interfacing of a keypad and a 7-segment display with the STM32F103C6 microcontroller. It showcases the ability to read inputs from a keypad and display corresponding outputs on a 7-segment display. This project is particularly useful for applications requiring numeric input and feedback display, such as simple calculators, numeric keypads for access control, and educational tools for electronics learning.

## Features

- **Keypad Input**: Utilizes a 4x4 matrix keypad to capture user inputs. The keypad driver scans for pressed keys and returns the corresponding character.
- **7-Segment Display Output**: Displays the pressed keypad character on a 7-segment display. This project supports both common anode and common cathode 7-segment displays, showcasing the versatility of the driver in handling different types of displays.
- **Custom Drivers**: Includes custom-written drivers for GPIO, Keypad, and LCD for the STM32F103C6 microcontroller. These drivers provide a foundation for interfacing with the hardware components and can be extended or modified for various applications.

## Project Structure

- `STM32F103x6_GPIO_Driver.h` and `.c`: GPIO driver to configure and control GPIO pins.
- `STM32F103x6_Keypad_Driver.h` and `.c`: Keypad driver to initialize the keypad and detect pressed keys.
- `STM32F103x6_LCD_Driver.h` and `.c`: LCD driver for interfacing with character LCDs, used here to display messages and keypad inputs.
- `main.c`: The main program file demonstrating the usage of keypad and 7-segment display drivers.

## How to Use

### Hardware Setup:

1. Connect the 4x4 matrix keypad to the STM32F103C6 GPIO pins as specified in the `HAL_Keypad_INIT` function.
2. Connect the 7-segment display to the GPIO pins as outlined in the `SevenSeg_init` function. Ensure proper configuration for common anode or common cathode type as per your display.
3. Optionally, connect an LCD to display additional messages or keypad inputs.

### Software Setup:

1. Include the custom drivers (GPIO, Keypad, and LCD) in your project directory.
2. Use the `main.c` file as the entry point for your application.

### Compilation and Flashing:

1. Compile the project using your preferred ARM toolchain.
2. Flash the compiled binary to your STM32F103C6 microcontroller using a programmer (e.g., ST-Link) or bootloader.

### Operation:

1. Upon powering the microcontroller, the LCD (if connected) displays a welcome message.
2. Pressing keys on the keypad will display the corresponding character on the 7-segment display.
3. Special characters or functions (e.g., clear display) can be implemented as per the logic in `main.c`.
### Simulation Video
[**Click Here**](https://drive.google.com/file/d/1t_hVFZ6D7piF17R_wu23BV-8837htS5f/view?usp=drive_link)
