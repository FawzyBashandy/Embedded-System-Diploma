

/*
*===============================================
*                   Includes
*===============================================
*/

#include "STM32F103C6.h"
#include "STM32F103x6_GPIO_Driver.h"
#include "STM32F103x6_Keypad_Driver.h"
#include "STM32F103x6_LCD_Driver.h"

/*
===============================================
*  				GLOBAL VARIABLES
*===============================================
*/
uint8_t sevenSegNumCodes[10] = {
		//GFEDCBA
		0b00111111, // 0
		0b00000110, // 1
		0b01011011, // 2
		0b01001111, // 3
		0b01100110, // 4
		0b01101101, // 5
		0b01111101, // 6
		0b00000111, // 7
		0b01111111, // 8
		0b01101111  // 9
};



LCD_Config LCD;

/*
===============================================
*  				Functions declarations
*===============================================
*/
void clock_init();
void delay(uint8 delay_Counter);
void SevenSeg_init();
void display_count();
void LCD_Init();

int main(void)
{
	uint8_t pressedKey;

	clock_init();
	SevenSeg_init();
	HAL_Keypad_INIT();
	LCD_Init();
	display_count();
	while (1)
	{
		 pressedKey = HAL_Keypad_getCh();
		 if(pressedKey != '$')
		 {
		 	if(pressedKey == '!')
		 	{
		 		HAL_LCD_Clear_Screen(&LCD);
		 	}else{
		 		if(pressedKey >= '0' && pressedKey <= '9')
		 		{
		 			GPIOB->ODR = (GPIOB->ODR & ~(0xFF << GPIO_PIN_9)) | ((~sevenSegNumCodes[pressedKey - '0']) << GPIO_PIN_9);
		 		}
		 		HAL_LCD_WRITE_CHAR(&LCD,pressedKey);
		 	}
		 }
	}
}

/*
===============================================
*  				Functions definitions
*===============================================
*/

void clock_init()
{
	/*Enable GPIO_A*/
	APB2_Peri_CLOCK_ENABLE(2);

	/*Enable GPIO_B*/

	APB2_Peri_CLOCK_ENABLE(3);
}

void SevenSeg_init()
{
	pinConfig_t config;

	config.pinNumber = GPIO_PIN_9;
	config.pinMode = GPIO_MODE_OUTPUT_PP;
	config.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB, &config);

	config.pinNumber = GPIO_PIN_10;
	config.pinMode = GPIO_MODE_OUTPUT_PP;
	config.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB, &config);

	config.pinNumber = GPIO_PIN_11;
	config.pinMode = GPIO_MODE_OUTPUT_PP;
	config.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB, &config);

	config.pinNumber = GPIO_PIN_12;
	config.pinMode = GPIO_MODE_OUTPUT_PP;
	config.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB, &config);

	config.pinNumber = GPIO_PIN_13;
	config.pinMode = GPIO_MODE_OUTPUT_PP;
	config.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB, &config);

	config.pinNumber = GPIO_PIN_14;
	config.pinMode = GPIO_MODE_OUTPUT_PP;
	config.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB, &config);

	config.pinNumber = GPIO_PIN_15;
	config.pinMode = GPIO_MODE_OUTPUT_PP;
	config.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB, &config);
}

void display_count()
{
	uint8 i;
	for(i = 0 ; i < 10; i++)
	{
		HAL_LCD_WRITE_CHAR(&LCD,(i +'0'));
		GPIOB->ODR = (GPIOB->ODR & ~(0xFF << GPIO_PIN_9)) | (~sevenSegNumCodes[i] << GPIO_PIN_9);
		delay(100);
	}

	HAL_LCD_Clear_Screen(&LCD);
	HAL_LCD_WRITE_STRING(&LCD,"Keypad Is Ready");
	delay(100);
	HAL_LCD_Clear_Screen(&LCD);
}

void delay(uint8 delay_Counter)
{
	volatile uint8 i, j;
	for(i = 0; i < delay_Counter; i++)
	{
		for ( j = 0; j < 255; j++)
		{
		}
	}
}
void LCD_Init()
{
	LCD.LCD_ctrlPort = GPIOA;
	LCD.LCD_dataPort = GPIOA;
	LCD.ctrlPins = LCD_CPINS_G4;
	LCD.dataPins = LCD_DPINS_LOWER_HALF;
	HAL_LCD_Init(&LCD);
}

