

/*
*===============================================
*                   Includes
*===============================================
*/

#include "STM32F103x6_EXTI_Driver.h"
#include "STM32F103x6_GPIO_Driver.h"
#include "STM32F103x6_LCD_Driver.h"
/*
===============================================
*  				GLOBAL VARIABLES
*===============================================
*/
LCD_Config LCD;

/*
===============================================
*  				Functions declarations
*===============================================
*/
void clock_init();
void delay(uint8 delay_Counter);
void LCD_Init();
void IRQ_Callback();

int main(void)
{
	clock_init();
	LCD_Init();
	EXTI_PinConfig_t EXTIx;
	EXTIx.EXTI_TriggerCase = EXTI_Trigger_RisingAndFalling;
	EXTIx.EXTIx = EXTI9_PB9;
	EXTIx.IRQ_EN = EXTI_IRQ_ENABLE;
	EXTIx.P_IRQ_CallBack = &IRQ_Callback;
	MCAL_EXTI_Init(&EXTIx);
	while (1)
	{

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
	/*Enable AFIO*/

	APB2_Peri_CLOCK_ENABLE(0);
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
	LCD.dataPins = LCD_DPINS_FIRST_NIBBLE;
	LCD.LCD_Mode = LCD_MODE_4BIT;
	HAL_LCD_Init(&LCD);
}
void IRQ_Callback()
{
	HAL_LCD_WRITE_STRING(&LCD, "Interrupt triggered on PB9 !");
	My_Wait(100);
	HAL_LCD_Clear_Screen(&LCD);
}
