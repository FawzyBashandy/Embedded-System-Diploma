
#define F_CPU 8000000ul
#include "ATmega32_GPIO_Driver.h"
#include "ATmega32_UART_Driver.h"
#include "ATmega32_LCD_Driver.h"
void Delay(uint32_t time) {
	vuint8_t i, j;
	for (i = 0; i < time; i++)
	for (j = 0; j < 255; j++);
}

void LCD_Init();
void main(void)
{
	char inputBuffer[256],input;
	LCD_Init();
	MCAL_USART_Init();
	MCAL_USART_Get_String(inputBuffer,256);
    MCAL_USART_Send_String(inputBuffer);
    while (1) 
   {
        input = MCAL_USART_Get_Char();
        MCAL_USART_Send_Char(input);
        HAL_LCD_WRITE_CHAR(&LCD,input);
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
