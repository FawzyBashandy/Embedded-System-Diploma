
/*
*===============================================
*                   Includes
*===============================================
*/
#define F_CPU 1000000UL
#include "ATmega32_GPIO_Driver.h"
#include "ATmega32_Timer0.h"


/*
===============================================
*  				GLOBAL VARIABLES
*===============================================
*/

Timer0_Config_t timerCFG;

/*
===============================================
*  				Functions declarations
*===============================================
*/
void GPIO_init();
void Timer_init();
void CompareOnMatchCallback()
{
	static uint32_t Counter = 0;
	if(Counter == 62)
	{
		GPIOA->PORT += 1;
		MCAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
		Counter = 0;
	}
	Counter++;
}
int main(void)
{
	GPIO_init();
	MCAL_TIMER0_SetCompare(253);
	Timer_init();
	MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(CompareOnMatchCallback);

	while(1);
}

/*
===============================================
*  				Functions definitions
*===============================================
*/

void GPIO_init()
{
	GPIOA->DDR = 0xFF;
	GPIOB->DDR = 0x8; // Set PB3 as output
}
void Timer_init()
{
	timerCFG.ClockSource = Timer_PreScaler_64;
	timerCFG.OperationMode = ClearOnCompareMatchMode;
	timerCFG.CompareMode	= Timer_COM_Disconnected;
	timerCFG.OverFlowInterrupt = Timer_TOI_Disable;
	timerCFG.CompareMatchInterrupt = Timer_TOCI_Enable;
	
	MCAL_TIMER0_Init(&timerCFG);

}
