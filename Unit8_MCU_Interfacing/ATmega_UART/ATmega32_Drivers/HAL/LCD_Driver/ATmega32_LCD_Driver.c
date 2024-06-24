/*
 * ATmega32_LCD_Driver.h
 *
 *  Created on: ٢٨‏/٠٢‏/٢٠٢٤
 *      Author: Fawzy Bashandy
 */
#include <util/delay.h>
#include "ATmega32_LCD_Driver.h"
#include "ATmega32_GPIO_Driver.h"
#include <stdio.h>
#include <stdlib.h>
pinConfig_t pinConfig;
uint8_t RS_Pos=0,RW_Pos=0,EN_Pos = 0;
void My_Wait(uint32_t time) {
	volatile uint8_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++);
}
void getCtrlPinsPositions(uint32_t bitmask , uint8_t * RS_Pos ,uint8_t * RW_Pos,uint8_t * EN_Pos) {
    for (uint8_t i = 0; i < 32; i++) {
        if (bitmask & (1UL << i)) {
            *RS_Pos = i;
            *RW_Pos = i+(uint8_t)1;
            *EN_Pos = i+(uint8_t)2;
            return;
        }
    }
}
void LCD_GPIO_Init(LCD_Config * lcdConfig)
{
	getCtrlPinsPositions(lcdConfig->ctrlPins, &RS_Pos, &RW_Pos, &EN_Pos);

	pinConfig.pinNumber = RS_Pos;
	pinConfig.pinMode = GPIO_MODE_OUTPUT;
	MCAL_GPIO_Init(lcdConfig->LCD_ctrlPort, &pinConfig);

	pinConfig.pinNumber =RW_Pos;
	pinConfig.pinMode = GPIO_MODE_OUTPUT;
	MCAL_GPIO_Init(lcdConfig->LCD_ctrlPort, &pinConfig);

	pinConfig.pinNumber =EN_Pos;
	pinConfig.pinMode = GPIO_MODE_OUTPUT;
	MCAL_GPIO_Init(lcdConfig->LCD_ctrlPort, &pinConfig);
	
	//8bit Mode
	if (lcdConfig->LCD_Mode == LCD_MODE_8BIT) //Set all port as output(DATA)
	{
		for(uint8_t i = 0 ; i < 8 ; i++)
		{
			pinConfig.pinNumber = i;
			pinConfig.pinMode = GPIO_MODE_OUTPUT;
			MCAL_GPIO_Init(lcdConfig->LCD_dataPort, &pinConfig);
		}
	
	}
	else //4 Bit Mode
	{
        uint32_t pinsMask = lcdConfig->dataPins; // This should be one of the 4-bit mode macros
        for (uint8_t pin = 0; pin < 8; ++pin)
        {
             if (pinsMask & (1 << pin))
             {
                 pinConfig.pinNumber = pin;
                 pinConfig.pinMode = GPIO_MODE_OUTPUT;
                 MCAL_GPIO_Init(lcdConfig->LCD_dataPort, &pinConfig);
             }
        }
	}


	MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, EN_Pos, GPIO_PIN_STATUS_LOW);
	MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RS_Pos, GPIO_PIN_STATUS_LOW);
	MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RW_Pos, GPIO_PIN_STATUS_LOW);
}

/**================================================================
* @Fn            -HAL_LCD_Init
* @brief         -Initializes the LCD display based on the configuration provided in lcdConfig.
*                 This includes setting up the GPIO pins for data and control signals, and sending
*                 initialization commands to the LCD.
* @param [in]    -lcdConfig: Pointer to LCD_Config struct which contains configuration information
*                 for initializing the LCD. This includes the GPIO ports for data and control lines,
*                 pin numbers.
* @retval        -None
* Note           -This function must be called before any other LCD operations are performed. It
*                 configures the LCD to a known state and prepares it for receiving commands and data.
*                 The function internally calls My_Wait() to provide necessary delays during initialization.
*/
void HAL_LCD_Init(LCD_Config * lcdConfig)
{

	//	DataDir_LCD_CTRL |= (1<<EN_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	My_Wait(20);
	LCD_GPIO_Init(lcdConfig);
	My_Wait(15);
    if (lcdConfig->LCD_Mode == LCD_MODE_4BIT) {
        // Initial 4-bit specific sequence
        HAL_LCD_WRITE_COMMAND(lcdConfig, 0x02); // Set to 4-bit mode
        HAL_LCD_WRITE_COMMAND(lcdConfig, LCD_FUNCTION_4BIT_2LINES);
    } else {
        // 8-bit mode initialization
        HAL_LCD_WRITE_COMMAND(lcdConfig, LCD_FUNCTION_8BIT_2LINES);
    }
	HAL_LCD_Clear_Screen(lcdConfig);  //.
	HAL_LCD_WRITE_COMMAND(lcdConfig,LCD_ENTRY_MODE);
	HAL_LCD_WRITE_COMMAND(lcdConfig,LCD_BEGIN_AT_FIRST_ROW);
	HAL_LCD_WRITE_COMMAND(lcdConfig,LCD_DISP_ON_CURSOR_BLINK);
}

/**================================================================
* @Fn            -HAL_LCD_Clear_Screen
* @brief         -Clears the entire LCD display and returns the cursor to the home position (0,0).
* @param [in]    -lcdConfig: Pointer to LCD_Config struct which contains configuration information
*                 for the LCD. This includes the GPIO ports for data and control lines.
* @retval        -None
* Note           -This function should be called whenever the display needs to be cleared. It sends
*                 the clear display command to the LCD which also resets the cursor position.
*/
void HAL_LCD_Clear_Screen(LCD_Config * lcdConfig)
{
	HAL_LCD_WRITE_COMMAND(lcdConfig,LCD_CLEAR_SCREEN);
}

/**================================================================
* @Fn            -HAL_LCD_WRITE_COMMAND
* @brief         -Sends a command to the LCD.
* @param [in]    -lcdConfig: Pointer to LCD_Config struct which contains configuration information
*                 for the LCD. This includes the GPIO ports for data and control lines.
* @param [in]    -command: The command byte to send to the LCD.
* @retval        -None
* Note           -This function is used internally to send various commands to the LCD, such as
*                 function set, entry mode set, display control, etc. It sets up the control lines
*                 and data pins appropriately to send the command.
*/
void HAL_LCD_WRITE_COMMAND(LCD_Config * lcdConfig,uint8_t command)
{

	getCtrlPinsPositions(lcdConfig->ctrlPins, &RS_Pos, &RW_Pos, &EN_Pos);
	if(lcdConfig->LCD_Mode == LCD_MODE_8BIT)
	{
		MCAL_GPIO_WritePort(lcdConfig->LCD_dataPort,command); //.
	}
	else //4 bit mode
	{
		uint8_t shiftpos = (lcdConfig->dataPins == LCD_DPINS_HIGHER_4PINS) ? 4 : 0 ;
		MCAL_GPIO_WritePartialPort(lcdConfig->LCD_dataPort, shiftpos , shiftpos+3 , command >> 4); //Send the higher nibble
		MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RS_Pos, GPIO_PIN_STATUS_LOW);
		MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RW_Pos, GPIO_PIN_STATUS_LOW);
		My_Wait(1);
		HAL_LCD_Kick(lcdConfig);
		MCAL_GPIO_WritePartialPort(lcdConfig->LCD_dataPort, shiftpos , shiftpos+3 , command); //Send the lower nibble
	}
	MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RS_Pos, GPIO_PIN_STATUS_LOW);
	MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RW_Pos, GPIO_PIN_STATUS_LOW);
	My_Wait(1);
	HAL_LCD_Kick(lcdConfig);
}

/**================================================================
* @Fn            -HAL_LCD_WRITE_CHAR
* @brief         -Writes a single character to the LCD at the current cursor position.
* @param [in]    -lcdConfig: Pointer to LCD_Config struct which contains configuration information
*                 for the LCD. This includes the GPIO ports for data and control lines.
* @param [in]    -character: The ASCII character to be displayed on the LCD.
* @retval        -None
* Note           -This function writes a character to the LCD and handles the necessary data and
*                 control signal manipulation. It automatically wraps text to the next line or
*                 scrolls the display if the end of the display is reached.
*/
void HAL_LCD_WRITE_CHAR(LCD_Config *lcdConfig,uint8_t character)
{
	static uint8_t tracker=0;
	getCtrlPinsPositions(lcdConfig->ctrlPins, &RS_Pos, &RW_Pos, &EN_Pos);
    if (tracker == 16) {
        // If 16 characters have been written, move to the second line.

    	HAL_LCD_WRITE_COMMAND(lcdConfig,LCD_BEGIN_AT_SECOND_ROW); // Move cursor to the beginning of the second line.
    } else if (tracker == 32) {
        // If 32 characters have been written, clear the screen and reset the tracker.
        HAL_LCD_Clear_Screen(lcdConfig);
        tracker = 0; // Reset tracker after clearing the screen.
        My_Wait(20); // Wait for the LCD to clear the screen.
    }
//	8Bit mode
	if(lcdConfig->LCD_Mode == LCD_MODE_8BIT)
	{
		MCAL_GPIO_WritePort(lcdConfig->LCD_dataPort,character); //.
		MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RS_Pos, GPIO_PIN_STATUS_HIGH);
		MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RW_Pos, GPIO_PIN_STATUS_LOW);
		My_Wait(1);
		HAL_LCD_Kick(lcdConfig);
	}
	else //4 BITMODE
	{
		uint8_t shiftpos = (lcdConfig->dataPins == LCD_DPINS_HIGHER_4PINS) ? 4 : 0 ;
		MCAL_GPIO_WritePartialPort(lcdConfig->LCD_dataPort, shiftpos , shiftpos+3 , character >> 4); //Send the higher nibble
		MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RS_Pos, GPIO_PIN_STATUS_HIGH);
		MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RW_Pos, GPIO_PIN_STATUS_LOW);
		My_Wait(1);
		HAL_LCD_Kick(lcdConfig);
		MCAL_GPIO_WritePartialPort(lcdConfig->LCD_dataPort, shiftpos , shiftpos+3 , character); //Send the lower nibble
		MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RS_Pos, GPIO_PIN_STATUS_HIGH);
		MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RW_Pos, GPIO_PIN_STATUS_LOW);
		My_Wait(1);
		HAL_LCD_Kick(lcdConfig);
	}

    tracker++; // Increment tracker AFTER writing the character.
    My_Wait(2); // Wait for the LCD to process the character.
}

/**================================================================
* @Fn            -HAL_LCD_WRITE_STRING
* @brief         -Writes a string of characters to the LCD.
* @param [in]    -lcdConfig: Pointer to LCD_Config struct which contains configuration information
*                 for the LCD. This includes the GPIO ports for data and control lines.
* @param [in]    -string: Pointer to the null-terminated string to be displayed on the LCD.
* @retval        -None
* Note           -The function iterates through each character of the string and calls
*                 HAL_LCD_WRITE_CHAR to display it. It handles line wrapping and display scrolling
*                 if the string is longer than the display's width.
*/
void HAL_LCD_WRITE_STRING(LCD_Config * lcdConfig,uint8_t* string)
{
	uint32_t count = 0;
	while (*string > 0){
		count++;
		HAL_LCD_WRITE_CHAR(lcdConfig,*string++);
	}
}

/**================================================================
* @Fn            -HAL_LCD_check_isbusy
* @brief         -Checks if the LCD is busy executing a command and waits until it's ready.
* @param [in]    -lcdConfig: Pointer to LCD_Config struct which contains configuration information
*                 for the LCD. This includes the GPIO ports for data and control lines.
* @retval        -None
* Note           -This function reads the busy flag (BF) from the LCD and waits in a loop until
*                 the LCD is ready. It's used internally before sending commands or data to ensure
*                 the LCD can accept them.
*/
void HAL_LCD_check_isbusy(LCD_Config * lcdConfig)
{
	if (lcdConfig->LCD_Mode == LCD_MODE_8BIT) //Set all port as output(DATA)
	{
		for(uint8_t i = 0 ; i < 8 ; i++)
		{
			pinConfig.pinNumber = i;
			pinConfig.pinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(lcdConfig->LCD_dataPort, &pinConfig);
		}

	}
	else //4 Bit Mode
	{
		uint32_t pinsMask = lcdConfig->dataPins; // This should be one of the 4-bit mode macros
		for (uint8_t pin = 0; pin < 8; ++pin)
		{
			if (pinsMask & (1 << pin))
			{
				pinConfig.pinNumber = pin;
				pinConfig.pinMode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(lcdConfig->LCD_dataPort, &pinConfig);
			}
		}
	}
	getCtrlPinsPositions(lcdConfig->ctrlPins, &RS_Pos, &RW_Pos, &EN_Pos);
	MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RS_Pos, GPIO_PIN_STATUS_LOW);
	MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RW_Pos, GPIO_PIN_STATUS_HIGH);
	HAL_LCD_Kick(lcdConfig);
	MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, RW_Pos, GPIO_PIN_STATUS_LOW);
}

/**================================================================
* @Fn            -HAL_LCD_Kick
* @brief         -Generates the enable pulse to latch the data/command into the LCD.
* @param [in]    -lcdConfig: Pointer to LCD_Config struct which contains configuration information
*                 for the LCD. This includes the GPIO port and pin for the enable line.
* @retval        -None
* Note           -This function is used internally after setting up the data/command bits and
*                 control signals. It toggles the enable line to signal the LCD to accept the data/command.
*/
void HAL_LCD_Kick(LCD_Config * lcdConfig) {
    MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, EN_Pos, GPIO_PIN_STATUS_HIGH);
    My_Wait(50); // Increase this delay as needed
    MCAL_GPIO_WritePin(lcdConfig->LCD_ctrlPort, EN_Pos, GPIO_PIN_STATUS_LOW);

}

/**================================================================
* @Fn            -HAL_LCD_GOTO_XY
* @brief         -Moves the LCD cursor to a specified position.
* @param [in]    -lcdConfig: Pointer to LCD_Config struct which contains configuration information
*                 for the LCD. This includes the GPIO ports for data and control lines.
* @param [in]    -line: The line number (0 based) where the cursor should be moved.
* @param [in]    -position: The position (column number, 0 based) on the line where the cursor should be moved.
* @retval        -None
* Note           -This function calculates the address based on the line and position, then sends
*                 the set DDRAM address command to move the cursor.
*/
void HAL_LCD_GOTO_XY(LCD_Config * lcdConfig,uint8_t line, uint8_t position)
{
	if(line == 0 && (position < 16 && position >= 0))
	{
		HAL_LCD_WRITE_COMMAND(lcdConfig,LCD_BEGIN_AT_FIRST_ROW + position);
	}
	else if (line == 1 && (position < 16 && position >= 0))
	{
		HAL_LCD_WRITE_COMMAND(lcdConfig,LCD_BEGIN_AT_SECOND_ROW + position);
	}
}

/**================================================================
* @Fn            -HAL_LCD_Display_Number
* @brief         -Displays a numerical value on the LCD.
* @param [in]    -lcdConfig: Pointer to LCD_Config struct which contains configuration information
*                 for the LCD. This includes the GPIO ports for data and control lines.
* @param [in]    -number: The integer number to display.
* @retval        -None
* Note           -This function converts the integer number to a string and then calls
*                 HAL_LCD_WRITE_STRING to display it on the LCD.
*/
void HAL_LCD_Display_Number(LCD_Config * lcdConfig,int32_t number)
{
	uint8_t str[7]; //assume max number is 7 digits
	itoa(number ,str,10);
	HAL_LCD_WRITE_STRING(lcdConfig,str);
}
/**================================================================
* @Fn            -HAL_LCD_Display_Real_Number
* @brief         -Displays a floating-point number on the LCD with two decimal places.
* @param [in]    -lcdConfig: Pointer to LCD_Config struct which contains configuration information
*                 for the LCD. This includes the GPIO ports for data and control lines.
* @param [in]    -num: The floating-point number to display.
* @retval        -None
* Note           -This function formats the floating-point number to a string with two decimal places
*                 and then calls HAL_LCD_WRITE_STRING to display it on the LCD.
*/
void HAL_LCD_Display_Real_Number(LCD_Config * lcdConfig,float64 num)
{
	int32_t integerPart = (int32_t)num;
	int32_t fractionalPart = (int32_t)((num - integerPart) * 100); // For 2 decimal places
	uint8_t double_Str[15];
	snprintf(double_Str, sizeof(double_Str), "%d.%02d", integerPart, fractionalPart);
	HAL_LCD_WRITE_STRING(lcdConfig,double_Str);
}
