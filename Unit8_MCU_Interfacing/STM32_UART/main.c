

/*
*===============================================
*                   Includes
*===============================================
*/

#include "STM32F103x6_USART_Driver.h"
#include "STM32F103x6_RCC_Driver.h"
/*
===============================================
*  				GLOBAL VARIABLES
*===============================================
*/
USART_Config_t USART1Cfg;

/*
===============================================
*  				Functions declarations
*===============================================
*/
void clock_init();
void USART_init();
void IRQ_Callback();

int main(void)
{
	clock_init();
	USART_init();

	MCAL_USART_Enable_Interrupt(&USART1Cfg, USART_IRQ_RXNE, IRQ_Callback);
	while (1)
	{
	}
}

/* ==========================Polling Mechanism=====================
int main(void)
{
	clock_init();
	USART_init();
	uint16_t buffer;
	while (1)
	{
		MCAL_USART_ReceiveData(&USART1Cfg, &buffer);
		MCAL_USART_SendData(&USART1Cfg, buffer);
	}
}
*/

/*
===============================================
*  				Functions definitions
*===============================================
*/

void clock_init()
{
	RCC_Config_t Rcc;
	Rcc.PeripheralNo = RCC_PERIPHERAL_IOPA;
	MCAL_RCC_EnablePeripheralClock(&Rcc);

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
	NVIC_IRQ37_USART1_ENABLE;
}

void IRQ_Callback()
{
	uint16_t buffer;
	MCAL_USART_ReceiveData(&USART1Cfg, &buffer);
	MCAL_USART_SendData(&USART1Cfg, buffer);
}
