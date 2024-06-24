/*
 * STM32F03x6_LCD_Driver.c
 *
 *  Created on: ٢٨‏/٠٢‏/٢٠٢٤
 *      Author: Fawzy Bashandy
 */

#include "STM32F103x6_Keypad_Driver.h"
#include "STM32F103x6_GPIO_Driver.h"
pinConfig_t pinConfig;
void Delay(uint32_t time) {
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}

static uint8_t Keypad_Row_Pins[] = {KEYPAD_ROW0,KEYPAD_ROW1,KEYPAD_ROW2,KEYPAD_ROW3};
static uint8_t Keypad_Col_Pins[] = {KEYPAD_COL0,KEYPAD_COL1,KEYPAD_COL2,KEYPAD_COL3};

/**================================================================
* @Fn            -HAL_Keypad_INIT
* @brief         -Initializes the keypad by configuring the row pins as inputs with pull-up resistors
*                 and the column pins as outputs set to a high state initially. This setup prepares
*                 the keypad for detecting key presses.
* @param         -None
* @retval        -None
* Note           -This function must be called before attempting to read key presses. It configures
*                 the necessary GPIO pins connected to the keypad matrix.
*/
void HAL_Keypad_INIT() {
    // Initialize column pins as output and set them to HIGH

	pinConfig.pinNumber = KEYPAD_COL0;
	pinConfig.pinMode = GPIO_MODE_OUTPUT_PP;
	pinConfig.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinConfig);
	MCAL_GPIO_WritePin(KEYPAD_DATA_PORT, KEYPAD_COL0, GPIO_PIN_STATUS_HIGH);

	pinConfig.pinNumber = KEYPAD_COL1;
	pinConfig.pinMode = GPIO_MODE_OUTPUT_PP;
	pinConfig.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinConfig);
	MCAL_GPIO_WritePin(KEYPAD_DATA_PORT, KEYPAD_COL1, GPIO_PIN_STATUS_HIGH);

	pinConfig.pinNumber = KEYPAD_COL2;
	pinConfig.pinMode = GPIO_MODE_OUTPUT_PP;
	pinConfig.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinConfig);
	MCAL_GPIO_WritePin(KEYPAD_DATA_PORT, KEYPAD_COL2, GPIO_PIN_STATUS_HIGH);

	pinConfig.pinNumber = KEYPAD_COL3;
	pinConfig.pinMode = GPIO_MODE_OUTPUT_PP;
	pinConfig.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinConfig);
	MCAL_GPIO_WritePin(KEYPAD_DATA_PORT, KEYPAD_COL3, GPIO_PIN_STATUS_HIGH);


    // Initialize row pins as input with pull-up
    pinConfig.pinNumber = KEYPAD_ROW0;
    pinConfig.pinMode = GPIO_MODE_INPUT_PU;
    MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinConfig);

    pinConfig.pinNumber = KEYPAD_ROW1;
    pinConfig.pinMode = GPIO_MODE_INPUT_PU;
    MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinConfig);

    pinConfig.pinNumber = KEYPAD_ROW2;
    pinConfig.pinMode = GPIO_MODE_INPUT_PU;
    MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinConfig);

    pinConfig.pinNumber = KEYPAD_ROW3;
    pinConfig.pinMode = GPIO_MODE_INPUT_PU;
    MCAL_GPIO_Init(KEYPAD_DATA_PORT, &pinConfig);
}

/**================================================================
* @Fn            -HAL_Keypad_getCh
* @brief         -Scans the keypad for any pressed keys and returns the character corresponding to the key.
*                 It sets each column to low one by one and checks each row for a low state, indicating a button press.
*                 This function implements a simple debouncing mechanism by waiting for the key to be released.
* @param         -None
* @retval        -The character corresponding to the pressed key. Returns '$' if no key is pressed.
* Note           -This function relies on the keypad initialization done by HAL_Keypad_INIT(). It must be called
*                 in a loop to continuously check for key presses. The function maps each key press to a predefined
*                 character based on the keypad layout.
*/
uint8_t HAL_Keypad_getCh()
{
    for (uint8_t col = 0; col < 4; col++) {
        // Set current column to LOW
        MCAL_GPIO_WritePin(KEYPAD_DATA_PORT, Keypad_Col_Pins[col], GPIO_PIN_STATUS_LOW);
        for (uint8_t row = 0; row < 4; row++) {
            // Check if button is pressed
            if (MCAL_GPIO_ReadPin(KEYPAD_DATA_PORT, Keypad_Row_Pins[row]) == GPIO_PIN_STATUS_LOW) {
                // Wait for button release (debouncing)
                while (MCAL_GPIO_ReadPin(KEYPAD_DATA_PORT, Keypad_Row_Pins[row]) == GPIO_PIN_STATUS_LOW);

                // Return the pressed key
                return Keypad_Character[row][col];
            }
        }

        // Reset the current column to HIGH before moving to the next column
        MCAL_GPIO_WritePin(KEYPAD_DATA_PORT, Keypad_Col_Pins[col], GPIO_PIN_STATUS_HIGH);
    }

    // Indicate no key pressed
    return '$';
}


