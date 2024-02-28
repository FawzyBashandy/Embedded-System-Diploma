#include "STM32F103C6.h"
#include "Platform_Types.h"
#include "STM32_F103C6_GPIO_Driver.h"
#include <stdint.h>

void Clock_Init()
{
	APB2_Peri_CLOCK_ENABLE(2);
	APB2_Peri_CLOCK_ENABLE(3);
}
void wait (uint32_t time)
{
	uint32_t i,j;
	for(i=0;i<time;i++)
	{
		for(j=0;j<255;j++);
	}
}
void GPIO_Init()
{
	//Setting INPUTS
	pinConfig_t pin_Config;
	pin_Config.pinNumber = GPIO_PIN_1;
	pin_Config.pinMode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &pin_Config); //Setting PA1 AS floating input

	pin_Config.pinMode = GPIO_MODE_OUTPUT_PP;
	pin_Config.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB, &pin_Config);//Setting PB1 as Push-Pull output

	pin_Config.pinNumber = GPIO_PIN_13;
	pin_Config.pinMode =GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &pin_Config); //Setting PA13 as floating input

	pin_Config.pinMode = GPIO_MODE_OUTPUT_OD;
	pin_Config.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOB, &pin_Config); //Setting PB13 as open-drain output;

	//Disable leds initially
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_STATUS_HIGH);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_STATUS_HIGH);

}
void My_Wait(uint32_t time)
{
	for(uint32_t i=0 ; i<time;i++)
	{
		for(uint32_t j=0; j<255;j++);
	}
}
int main()
{
	Clock_Init();
	GPIO_Init();
	while(1)
	{
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_STATUS_LOW)
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
			while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)== GPIO_PIN_STATUS_LOW);
		}
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == GPIO_PIN_STATUS_HIGH)
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
		}
		My_Wait(1);
	}
}

