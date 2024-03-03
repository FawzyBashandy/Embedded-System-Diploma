/*
 * Unit7_Section1.c
 *
 * Created: 23/02/2024 02:34:35 م
 * Author : Fawzy Bashandy
 */ 
#define F_CPU 8000000ul
#include "ATmega32_GPIO_Driver.h"
#include "ATmega32_LCD_Driver.h"
void Delay(uint32_t time) {
	vuint8_t i, j;
	for (i = 0; i < time; i++)
	for (j = 0; j < 255; j++);
}

void LCD_Init();
void main(void)
{
	LCD_Init();
    while (1) 
   {
	   HAL_LCD_WRITE_STRING(&LCD," Learn In Depth ");
	   Delay(2000);
	   HAL_LCD_Clear_Screen(&LCD);
   }
}
void LCD_Init()
{
	LCD.LCD_dataPort = GPIOA;
	LCD.LCD_ctrlPort = GPIOB;
	LCD.LCD_Mode = LCD_MODE_4BIT;
	LCD.dataPins = LCD_DPINS_HIGHER_4PINS;
	LCD.ctrlPins = LCD_CPINS_G2;
	HAL_LCD_Init(&LCD);
}
