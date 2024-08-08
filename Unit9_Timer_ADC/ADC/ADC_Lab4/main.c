
/*
*===============================================
*                   Includes
*===============================================
*/
#define F_CPU 1000000UL
#include "ATmega32_GPIO_Driver.h"
#include "ATmega32_ADC.h"
#include "ATmega32_LCD_Driver.h"

/*
===============================================
*  				GLOBAL VARIABLES
*===============================================
*/
LCD_Config LCDcfg;
ADC_Config_t ADC_configure;
uint16_t Buffer=0;

/*
===============================================
*  				Functions declarations
*===============================================
*/
void GPIO_init();
void ADC_init();
void LCD_init();
void ConvertToClesius(uint16_t *Buffer);
void EndofConversion_Callback(void)
{
	MCAL_ADC_getConversionResult(&Buffer);
	ConvertToClesius(&Buffer);
	GPIOD->PORT = (Buffer);
	HAL_LCD_Display_Number(&LCDcfg,Buffer);
}
int main(void)
{
	GPIO_init();
	ADC_init();
	LCD_init();
	MCAL_ADC_setEndOfConversion_CALLBACK(EndofConversion_Callback);
	MCAL_ADC_startConversion();
	while(1);
}

/*
===============================================
*  				Functions definitions
*===============================================
*/

void GPIO_init()
{
	pinConfig_t pincfg ;
	pincfg.pinMode = GPIO_MODE_INPUT_FLO;
	pincfg.pinNumber = GPIO_PIN_0;
	MCAL_GPIO_Init(GPIOA,&pincfg);
	GPIOC->DDR |= 0xff;
	GPIOD->DDR |= 0xff;
}
void ADC_init()
{
	ADC_configure.Clock					 = ADC_PreScaler_128;
	ADC_configure.conversionMode		 = AutoTriggerConversion;
	ADC_configure.conversionTriggerEvent = EndofConversionFlag_Trigger;
	ADC_configure.dataAdjustment		 = RightAdjusted;
	ADC_configure.inputChannel			 = ADC_Channel_0;
	ADC_configure.referenceVoltage		 = InternalVoltage;
	
	MCAL_ADC_Init(&ADC_configure);

}
void LCD_init()
{
	LCDcfg.ctrlPins = LCD_CPINS_G2;
	LCDcfg.dataPins = LCD_DPINS_HIGHER_4PINS;
	LCDcfg.LCD_ctrlPort = GPIOB;
	LCDcfg.LCD_dataPort = GPIOB;
	LCDcfg.LCD_Mode = LCD_MODE_4BIT;
	
	HAL_LCD_Init(&LCDcfg);
}
void ConvertToClesius(uint16_t *Buffer)
{
	*Buffer >>= 2; //Divide by 4 to convert from 10mv of LM35 to 2.5mv of ADC
}
