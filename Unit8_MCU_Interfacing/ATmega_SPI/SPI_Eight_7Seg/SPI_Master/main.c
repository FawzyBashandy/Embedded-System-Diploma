
#define F_CPU 1000000UL
#include "ATmega32_GPIO_Driver.h"
#include "ATmega32_SPI_Driver.h"
#include <avr/io.h> //For using "PORTA" Directly ONLY
#include <avr/delay.h>


/*
*===============================================
*                   Includes
*===============================================
*/

#include "ATmega32_SPI_Driver.h"

/*
===============================================
*  				GLOBAL VARIABLES
*===============================================
*/
SPI_Config_t   SPICfg;


/*
===============================================
*  				Functions declarations
*===============================================
*/
void SPI_init();
void Execute(uint8_t cmd , uint8_t data);
int main(void)
{
	uint8_t counter = 0;
	uint8_t displayindex = 1;
	SPI_init();

	Execute(0x09, 0xFF);
	Execute(0x0A, 0xFF);
	Execute(0x0B, 0xF7);
	Execute(0x0C, 0x01);
	for( ; displayindex < 9 ; displayindex++ , counter++)
	{
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_STATUS_LOW);
		MCAL_SPI_SendData(&SPICfg, &displayindex);
		MCAL_SPI_SendData(&SPICfg, &counter);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_STATUS_HIGH);
		_delay_ms(500);
	}
}

/*
===============================================
*  				Functions definitions
*===============================================
*/


void Execute(uint8_t cmd , uint8_t data)
{
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_STATUS_LOW);
	MCAL_SPI_SendData(&SPICfg, &cmd);
	MCAL_SPI_SendData(&SPICfg, &data);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_STATUS_HIGH);

}
void SPI_init()
{
	SPICfg.MasterClk	= SPI_MasterClk_FoscDIV16;
	SPICfg.xBitFirst	= SPI_xBitFirst_MSBFirst;
	SPICfg.SPI			= SPI1;
	SPICfg.ClockConfig	= SPI_ClockConfig_C_Rising_T_Falling;
	SPICfg.DeviceMode	= SPI_DeviceMode_MASTER;
	SPICfg.Mechanism	= SPI_Mechanism_Polling;
	MCAL_SPI_Init(&SPICfg); //Init SPI and the corresponding pins in GPIO
}

