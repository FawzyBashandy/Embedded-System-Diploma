///*
// * STM32F103x6_EXTI_Driver.c
// *
// *  Created on: Feb 28, 2024
// *      Author: Fawzy Bashandy
// */

//*===============================================
//*                   Includes
//*===============================================

#include <EXTI/STM32F103x6_EXTI_Driver.h>
#include <GPIO/STM32F103x6_GPIO_Driver.h>

///**************************************************************************************************************************
//===============================================
//*  				Global variables
//*==============================================
void (* GP_IRQ_Callback[15])(void);
//===============================================
//*  				Generic Macros
//*==============================================
#define AFIO_EXTICR_resetValue		0x00000000
#define EXTI_Registers_resetValue	0x00000000
#define EXTI_PR_Reset				0xFFFFFFFF

#define EXTI_Pxx_Map(x)	((x == GPIOA)?0 : \
							 (x == GPIOB)?1 : \
							 (x == GPIOC)?2 : \
							 (x == GPIOD)?3 : 0 )
//===============================================
//*  				Generic Functions
//*===============================================
void Enable_NVIC(uint8_t IRQx)
{
    switch(IRQx)
    {
        case 6:
            NVIC_IRQ6_EXTI0_Enable;
            break;
        case 7:
            NVIC_IRQ7_EXTI1_Enable;
            break;
        case 8:
            NVIC_IRQ8_EXTI2_Enable;
            break;
        case 9:
            NVIC_IRQ9_EXTI3_Enable;
            break;
        case 10:
            NVIC_IRQ10_EXTI4_Enable;
            break;
        case 23:
            NVIC_IRQ23_EXTI9_5_Enable;
            break;
        case 40:
            NVIC_IRQ40_EXTI15_10_Enable;
            break;
    }
}
void Disable_NVIC(uint8_t IRQx)
{
    switch(IRQx)
    {
        case 6:
            NVIC_IRQ6_EXTI0_DISABLE;
            break;
        case 7:
            NVIC_IRQ7_EXTI1_DISABLE;
            break;
        case 8:
            NVIC_IRQ8_EXTI2_DISABLE;
            break;
        case 9:
            NVIC_IRQ9_EXTI3_DISABLE;
            break;
        case 10:
            NVIC_IRQ10_EXTI4_DISABLE;
            break;
        case 23:
            NVIC_IRQ23_EXTI9_5_DISABLE;
            break;
        case 40:
            NVIC_IRQ40_EXTI15_10_DISABLE;
            break;
    }
}
void Update_EXTI(EXTI_PinConfig_t *EXTI_config)
{
	// 1 - Set the EXTI given pin as AF INPUT ( Floating input )
	pinConfig_t pinCfg ;
	pinCfg.pinNumber 	= EXTI_config->EXTIx.pinNumber;
	pinCfg.pinMode  	= GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(EXTI_config->EXTIx.EXTI_Port, &pinCfg);
	// 2 - Route the given pin to the corresponding EXTI line
	uint8_t AFIO_EXTICR_Index , AFIO_EXTICR_pos;
	AFIO_EXTICR_Index 	= EXTI_config->EXTIx.EXTI_lineNumber / 4 ;
	AFIO_EXTICR_pos		= (EXTI_config->EXTIx.EXTI_lineNumber % 4) * 4 ;

	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF << AFIO_EXTICR_pos); //Clear the bits first in case of actual update
	AFIO->EXTICR[AFIO_EXTICR_Index] |= (EXTI_Pxx_Map(EXTI_config->EXTIx.EXTI_Port) << AFIO_EXTICR_pos);

	// 3.1 - configure the EXTI registers from the given config
	if(EXTI_config->EXTI_TriggerCase == EXTI_Trigger_Rising)
	{
		EXTI->RTSR |= (1<<EXTI_config->EXTIx.EXTI_lineNumber);
		EXTI->FTSR &= ~(1<<EXTI_config->EXTIx.EXTI_lineNumber);
	}
	else if (EXTI_config->EXTI_TriggerCase == EXTI_Trigger_Falling)
	{
		EXTI->FTSR |= (1<<EXTI_config->EXTIx.EXTI_lineNumber);
		EXTI->RTSR &= ~(1<<EXTI_config->EXTIx.EXTI_lineNumber);

	}
	else if (EXTI_config->EXTI_TriggerCase == EXTI_Trigger_RisingAndFalling)
	{
		EXTI->RTSR |= (1<<EXTI_config->EXTIx.EXTI_lineNumber);
		EXTI->FTSR |= (1<<EXTI_config->EXTIx.EXTI_lineNumber);
	}

	// 3.2 - enabling or disabling IRQ (both EXTI _ NVIC)
	if(EXTI_config->IRQ_EN == EXTI_IRQ_ENABLE)
	{
		EXTI->IMR |= (1<<EXTI_config->EXTIx.EXTI_lineNumber); //Write 1 to remove mask from the IRQ
		Enable_NVIC(EXTI_config->EXTIx.IRQ_Number);
	}
	else if(EXTI_config->IRQ_EN == EXTI_IRQ_Disable)
	{
		EXTI->IMR &= ~(1<<EXTI_config->EXTIx.EXTI_lineNumber); //Write 0 to mask the IRQ
		Disable_NVIC(EXTI_config->EXTIx.IRQ_Number);
	}

	// 4 - Update the IRQ Handling callback functions
	GP_IRQ_Callback[EXTI_config->EXTIx.EXTI_lineNumber] = EXTI_config->P_IRQ_CallBack;

}
///**************************************************************************************************************************
//*===============================================
//*  			APIs functions definitions
//*===============================================
//*/
void MCAL_EXTI_Init(EXTI_PinConfig_t *EXTI_config)
{
	Update_EXTI(EXTI_config);
}
void MCAL_EXTI_Update(EXTI_PinConfig_t *EXTI_config)
{
	Update_EXTI(EXTI_config);
}
void MCAL_EXTI_Reset()
{
	// 1 - Write the reset values on AFIO_EXTICR to reset the EXTIx_Pxx mappings
	AFIO->EXTICR[0] = AFIO_EXTICR_resetValue;
	AFIO->EXTICR[1] = AFIO_EXTICR_resetValue;
	AFIO->EXTICR[2] = AFIO_EXTICR_resetValue;
	AFIO->EXTICR[3] = AFIO_EXTICR_resetValue;

	// 2 - Write the reset values on EXTI Registers to reset EXTI lines configurations
	EXTI->EMR		= EXTI_Registers_resetValue;
	EXTI->FTSR		= EXTI_Registers_resetValue;
	EXTI->IMR		= EXTI_Registers_resetValue;
	EXTI->RTSR		= EXTI_Registers_resetValue;
	EXTI->SWIER		= EXTI_Registers_resetValue;

	EXTI->PR		= EXTI_PR_Reset; //W_C (write to clear)

	// 3 - Disable the EXTI IRQs from the NVIC Controller
	NVIC_IRQ6_EXTI0_DISABLE;
	NVIC_IRQ7_EXTI1_DISABLE;
	NVIC_IRQ8_EXTI2_DISABLE;
	NVIC_IRQ9_EXTI3_DISABLE;
	NVIC_IRQ10_EXTI4_DISABLE;
	NVIC_IRQ23_EXTI9_5_DISABLE;
	NVIC_IRQ40_EXTI15_10_DISABLE;
}

///**************************************************************************************************************************
//===============================================
//*               EXTI ISR functions
//*===============================================
//*/
void EXTI0_IRQHandler (void)
{
	//Clear this IRQ from the PendingRegister to ACK
	EXTI->PR |= (1<<0);
	//Call the callback function in the application layer
	GP_IRQ_Callback[0]();
}
void EXTI1_IRQHandler (void)
{
	//Clear this IRQ from the PendingRegister to ACK
	EXTI->PR |= (1<<1);
	//Call the callback function in the application layer
	GP_IRQ_Callback[1]();
}
void EXTI2_IRQHandler (void)
{
	//Clear this IRQ from the PendingRegister to ACK
	EXTI->PR |= (1<<2);
	//Call the callback function in the application layer
	GP_IRQ_Callback[2]();
}
void EXTI3_IRQHandler (void)
{
	//Clear this IRQ from the PendingRegister to ACK
	EXTI->PR |= (1<<3);
	//Call the callback function in the application layer
	GP_IRQ_Callback[3]();
}
void EXTI4_IRQHandler (void)
{
	//Clear this IRQ from the PendingRegister to ACK
	EXTI->PR |= (1<<4);
	//Call the callback function in the application layer
	GP_IRQ_Callback[4]();
}
void EXTI9_5_IRQHandler (void)
{
	if(EXTI->PR & (1<<5)) { EXTI->PR |= (1<<5); GP_IRQ_Callback[5]();}
	if(EXTI->PR & (1<<6)) { EXTI->PR |= (1<<6); GP_IRQ_Callback[6]();}
	if(EXTI->PR & (1<<7)) { EXTI->PR |= (1<<7); GP_IRQ_Callback[7]();}
	if(EXTI->PR & (1<<8)) { EXTI->PR |= (1<<8); GP_IRQ_Callback[8]();}
	if(EXTI->PR & (1<<9)) { EXTI->PR |= (1<<9); GP_IRQ_Callback[9]();}
}
void EXTI15_10_IRQHandler (void)
{
	if(EXTI->PR & (1<<10)) { EXTI->PR |= (1<<10); GP_IRQ_Callback[10]();}
	if(EXTI->PR & (1<<11)) { EXTI->PR |= (1<<11); GP_IRQ_Callback[11]();}
	if(EXTI->PR & (1<<12)) { EXTI->PR |= (1<<12); GP_IRQ_Callback[12]();}
	if(EXTI->PR & (1<<13)) { EXTI->PR |= (1<<13); GP_IRQ_Callback[13]();}
	if(EXTI->PR & (1<<14)) { EXTI->PR |= (1<<14); GP_IRQ_Callback[14]();}
	if(EXTI->PR & (1<<15)) { EXTI->PR |= (1<<15); GP_IRQ_Callback[15]();}
}
