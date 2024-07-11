
#define F_CPU 1000000UL
#include "ATmega32_GPIO_Driver.h"
#include "ATmega32_SPI_Driver.h"
#include <avr/io.h> //For using "PORTA" Directly ONLY
#include <avr/delay.h>
//#define MCU_Act_As_MASTER
#define MCU_Act_As_SLAVE

SPI_Config_t SPIcfg;
void SPI_Init();
void main(void)
{
	SPI_Init();
	DDRA = 0xFF;
	uint8_t data;
	uint8_t datareceived;
    while (1)
    {
	    #ifdef MCU_Act_As_MASTER
	    for(data = 0 ; data<=255 ; data++)
	    {
			_delay_ms(1000);
			MCAL_GPIO_WritePin(GPIOB , GPIO_PIN_4 , GPIO_PIN_STATUS_LOW);
			datareceived=data;
		    MCAL_SPI_ExchangeData(&SPIcfg,&datareceived);
			MCAL_GPIO_WritePin(GPIOB , GPIO_PIN_4 , GPIO_PIN_STATUS_HIGH);
			PORTA = datareceived;
	    }
		#endif
		#ifdef MCU_Act_As_SLAVE
	    for(data = 255 ; data >=0 ; data--)
	    {
			_delay_ms(1000);
			datareceived=data;
		    MCAL_SPI_ExchangeData(&SPIcfg,&datareceived);
		    PORTA = datareceived;
	    }
		#endif
    }
}
void SPI_Init()
{
	#ifdef MCU_Act_As_MASTER
	SPIcfg.DeviceMode = SPI_DeviceMode_MASTER;
	#endif
	#ifdef MCU_Act_As_SLAVE
	SPIcfg.DeviceMode = SPI_DeviceMode_SLAVE;
	#endif
	SPIcfg.ClockConfig = SPI_ClockConfig_T_Rising_C_Falling;
	SPIcfg.MasterClk = SPI_MasterClk_FoscDIV16;
	SPIcfg.Mechanism = SPI_Mechanism_Polling;
	SPIcfg.SPI = SPI1;
	SPIcfg.xBitFirst = SPI_xBitFirst_MSBFirst;
	MCAL_SPI_Init(&SPIcfg);
}
