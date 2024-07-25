

/*
*===============================================
*                   Includes
*===============================================
*/

#include <RCC/STM32F103x6_RCC_Driver.h>
#include <E2PROM/E2PROM_Driver.h>

/*
===============================================
*  				GLOBAL VARIABLES
*===============================================
*/



/*
===============================================
*  				Functions declarations
*===============================================
*/
void clock_init();
int main(void)
{
	uint8_t buffer[5]={0x1,0x2,0x3,0x4,0x5};
	uint8_t Datain[5];
	//init
	clock_init();
	HAL_E2PROM_Init();
	HAL_E2PROM_WriteData(0xFFF0, E2PROM_SLAVE_ADDRESS, buffer, sizeof(buffer));
	HAL_E2PROM_ReadData(0xFFF0, E2PROM_SLAVE_ADDRESS, Datain, sizeof(Datain));
	while(1);
}

/*
===============================================
*  				Functions definitions
*===============================================
*/

void clock_init()
{
	//IOA Clock Enable

	RCC_Config_t Rcc;
	Rcc.PeripheralNo = RCC_PERIPHERAL_IOPB;
	MCAL_RCC_EnablePeripheralClock(&Rcc);

	//AFIO Clock enable

	Rcc.PeripheralNo = RCC_PERIPHERAL_AFIO;
	MCAL_RCC_EnablePeripheralClock(&Rcc);

	//I2C1 Clock Enable
	Rcc.PeripheralNo = RCC_PERIPHERAL_I2C1;
	MCAL_RCC_EnablePeripheralClock(&Rcc);


}


/*
void delay()
{
	for(vuint32_t i = 1 ; i < 99999 ; i++);
}
*/
