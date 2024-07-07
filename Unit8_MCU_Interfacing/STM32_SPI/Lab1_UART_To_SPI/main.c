

/*
*===============================================
*                   Includes
*===============================================
*/

#include "STM32F103x6_USART_Driver.h"
#include "STM32F103x6_RCC_Driver.h"
#include "STM32F103x6_SPI_Driver.h"

#define MCU_Act_As_Master
//#define MCU_Act_As_Slave
/*
===============================================
*  				GLOBAL VARIABLES
*===============================================
*/
USART_Config_t USART1Cfg;
SPI_Config_t   SPICfg;

/*
===============================================
*  				Functions declarations
*===============================================
*/
void clock_init();
void USART_init();
void SPI_init();
void USART__IRQ_Callback();
void SPI__IRQ_Callback();

int main(void)
{
	clock_init();
	USART_init();
	SPI_init();
	MCAL_USART_Enable_Interrupt(&USART1Cfg, USART_IRQ_RXNE, USART__IRQ_Callback);

	while (1);
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
	Rcc.PeripheralNo = RCC_PERIPHERAL_IOPA;
	MCAL_RCC_EnablePeripheralClock(&Rcc);

	//SPI1 Clock Enable
	Rcc.PeripheralNo = RCC_PERIPHERAL_SPI1;
	MCAL_RCC_EnablePeripheralClock(&Rcc);

	//USART1 Clock Enable
	Rcc.PeripheralNo = RCC_PERIPHERAL_USART1;
	MCAL_RCC_EnablePeripheralClock(&Rcc);

}

void USART_init()
{
	USART1Cfg.BaudRate = USART_BaudRate_115200;
	USART1Cfg.Parity = USART_Parity_NONE;
	USART1Cfg.Mechanism_type = Interrupt;

	USART1Cfg.StopBitsLength = USART_StopBitsLength_OneBit;
	USART1Cfg.TxRx_Mode = USART_TxRxMode_BOTH_TXRX;
	USART1Cfg.USARTx = USART1;

	USART1Cfg.WordLength = USART_WordLength_8b;
	MCAL_USART_Init(&USART1Cfg);
}

void SPI_init()
{
	SPICfg.DeviceMode 		 = SPI_DeviceMode_MASTER;
	SPICfg.CommunicationMode = SPI_CommunicationMode_FULLDUPLEX;
	SPICfg.DataSize			 = SPI_DataSize_8b;

	SPICfg.FrameFormat		 = SPI_FrameFormat_LSBFirst;
	SPICfg.TimingConfig		 = SPI_TimingConfig_T_Falling_C_Rising;
	SPICfg.SPI				 = SPI1;

	SPICfg.Mechanism_type 	 = Polling;
	#ifdef MCU_Act_As_Master
	SPICfg.MasterClk 		 = SPI_MasterCLK_Define_PCLKDiv8;
	SPICfg.SS_Managment 	 = SPI_SS_Mangament_SW_NSS_SET; //SW managemnt and SSI bit is enabled (NSS seen as high)
	#endif

	MCAL_SPI_Init(&SPICfg); //Init SPI and the corresponding pins in GPIO

	//Since The master NSS is managed by SW (and configured as high) , we will configure some pin that master will use it to select a slave from Slaves
	pinConfig_t PA4;
	PA4.pinNumber 		= GPIO_PIN_4;
	PA4.pinMode	  		= GPIO_MODE_OUTPUT_PP;
	PA4.outputModeSpeed = GPIO_OUTPUT_SPEED_10MHZ;
	MCAL_GPIO_Init(GPIOA, &PA4);
}

void USART__IRQ_Callback()
{
	uint16_t buffer;
	MCAL_USART_ReceiveData(&USART1Cfg, &buffer);
	MCAL_USART_SendData(&USART1Cfg, buffer);
	MCAL_GPIO_WritePin(GPIOA,GPIO_PIN_4, GPIO_PIN_STATUS_LOW); //PIN 4 is chosen to be the SS that will be entered to slave while The SS in master is always high to know that he's the only master taking the bus
	MCAL_SPI_SendData(&SPICfg, &buffer);
	MCAL_GPIO_WritePin(GPIOA,GPIO_PIN_4, GPIO_PIN_STATUS_HIGH);
}
