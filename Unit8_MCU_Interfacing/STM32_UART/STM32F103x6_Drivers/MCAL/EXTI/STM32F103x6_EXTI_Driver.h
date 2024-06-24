/*
 * STM32F103x5_EXTI_Driver.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */

#ifndef STM32F103x5_EXTI_Driver_H_
#define STM32F103x5_EXTI_Driver_H_

//-----------------------------
//Includes
//-----------------------------

#include "STM32F103C6.h"
#include "STM32F103x6_GPIO_Driver.h"


//-----------------------------
//User type definitions (structures)
//-----------------------------


typedef struct
{
	GPIO_t * 	EXTI_Port;
	uint8_t 	pinNumber;
	uint8_t		EXTI_lineNumber;
	uint8_t		IRQ_Number;
}EXTI_GPIO_Mapping_t;
typedef struct
{
	EXTI_GPIO_Mapping_t 	EXTIx;						    /*Specify the External interrupt GPIO mapping.
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 *This paramerter must be a value of @ref EXTI_Define*/

	uint8_t 				EXTI_TriggerCase;				/*Specify the trigger mode (Rising , Falling or Both).
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 *This paramerter must be a value of @ref EXTI_Trigger_Define*/

	uint8_t 				IRQ_EN;							/*Enable or Disable the EXTI IRQ (That will enable/disable the IRQ Mask in both EXTI and NVIC Interrupt controller.
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 *This paramerter must be a value of @ref EXTI_IRQ_Define*/

	void (* P_IRQ_CallBack ) (void);						/* Carries the address of the C funtion that will be called on interrupt (in case of IRQ enabled).*/
}EXTI_PinConfig_t;

//-----------------------------
//Generic Macros
//-----------------------------
//EXTI Lines
#define EXTI0			0
#define EXTI1			1
#define EXTI2			2
#define EXTI3			3
#define EXTI4			4
#define EXTI5			5
#define EXTI6			6
#define EXTI7			7
#define EXTI8			8
#define EXTI9			9
#define EXTI10			10
#define EXTI11			11
#define EXTI12			12
#define EXTI13			13
#define EXTI14			14
#define EXTI15			15

//EXTI_IRQ Map
#define EXTI0_IRQ			6
#define EXTI1_IRQ			7
#define EXTI2_IRQ			8
#define EXTI3_IRQ			9
#define EXTI4_IRQ			10
#define EXTI5_IRQ			23
#define EXTI6_IRQ			23
#define EXTI7_IRQ			23
#define EXTI8_IRQ			23
#define EXTI9_IRQ			23
#define EXTI10_IRQ			40
#define EXTI11_IRQ			40
#define EXTI12_IRQ			40
#define EXTI13_IRQ			40
#define EXTI14_IRQ			40
#define EXTI15_IRQ			40
//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref EXTI_Define
//EXTI0
#define EXTI0_PA0				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_0 , EXTI0 , EXTI0_IRQ}
#define EXTI0_PB0				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_0 , EXTI0 , EXTI0_IRQ}
#define EXTI0_PC0				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_0 , EXTI0 , EXTI0_IRQ}
#define EXTI0_PD0				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_0 , EXTI0 , EXTI0_IRQ}
//EXTI1
#define EXTI1_PA1				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_1 , EXTI1 , EXTI1_IRQ}
#define EXTI1_PB1				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_1 , EXTI1 , EXTI1_IRQ}
#define EXTI1_PC1				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_1 , EXTI1 , EXTI1_IRQ}
#define EXTI1_PD1				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_1 , EXTI1 , EXTI1_IRQ}
//EXTI2
#define EXTI2_PA2				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_2 , EXTI2 , EXTI2_IRQ}
#define EXTI2_PB2				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_2 , EXTI2 , EXTI2_IRQ}
#define EXTI2_PC2				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_2 , EXTI2 , EXTI2_IRQ}
#define EXTI2_PD2				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_2 , EXTI2 , EXTI2_IRQ}
//EXTI3
#define EXTI3_PA3				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_3 , EXTI3 , EXTI3_IRQ}
#define EXTI3_PB3				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_3 , EXTI3 , EXTI3_IRQ}
#define EXTI3_PC3				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_3 , EXTI3 , EXTI3_IRQ}
#define EXTI3_PD3				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_3 , EXTI3 , EXTI3_IRQ}
//EXTI4
#define EXTI4_PA4				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_4 , EXTI4 , EXTI4_IRQ}
#define EXTI4_PB4				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_4 , EXTI4 , EXTI4_IRQ}
#define EXTI4_PC4				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_4 , EXTI4 , EXTI4_IRQ}
#define EXTI4_PD4				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_4 , EXTI4 , EXTI4_IRQ}
//EXTI5
#define EXTI5_PA5				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_5 , EXTI5 , EXTI5_IRQ}
#define EXTI5_PB5				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_5 , EXTI5 , EXTI5_IRQ}
#define EXTI5_PC5				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_5 , EXTI5 , EXTI5_IRQ}
#define EXTI5_PD5				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_5 , EXTI5 , EXTI5_IRQ}
//EXTI6
#define EXTI6_PA6				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_6 , EXTI6 , EXTI6_IRQ}
#define EXTI6_PB6				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_6 , EXTI6 , EXTI6_IRQ}
#define EXTI6_PC6				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_6 , EXTI6 , EXTI6_IRQ}
#define EXTI6_PD6				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_6 , EXTI6 , EXTI6_IRQ}
//EXTI7
#define EXTI7_PA7				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_7 , EXTI7 , EXTI7_IRQ}
#define EXTI7_PB7				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_7 , EXTI7 , EXTI7_IRQ}
#define EXTI7_PC7				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_7 , EXTI7 , EXTI7_IRQ}
#define EXTI7_PD7				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_7 , EXTI7 , EXTI7_IRQ}
//EXTI8
#define EXTI8_PA8				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_8 , EXTI8 , EXTI8_IRQ}
#define EXTI8_PB8				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_8 , EXTI8 , EXTI8_IRQ}
#define EXTI8_PC8				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_8 , EXTI8 , EXTI8_IRQ}
#define EXTI8_PD8				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_8 , EXTI8 , EXTI8_IRQ}
//EXTI9
#define EXTI9_PA9				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_9 , EXTI9 , EXTI9_IRQ}
#define EXTI9_PB9				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_9 , EXTI9 , EXTI9_IRQ}
#define EXTI9_PC9				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_9 , EXTI9 , EXTI9_IRQ}
#define EXTI9_PD9				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_9 , EXTI9 , EXTI9_IRQ}
//EXTI10
#define EXTI10_PA10				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_10 , EXTI10 , EXTI10_IRQ}
#define EXTI10_PB10				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_10 , EXTI10 , EXTI10_IRQ}
#define EXTI10_PC10				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_10 , EXTI10 , EXTI10_IRQ}
#define EXTI10_PD10				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_10 , EXTI10 , EXTI10_IRQ}
//EXTI11
#define EXTI11_PA11				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_11 , EXTI11 , EXTI11_IRQ}
#define EXTI11_PB11				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_11 , EXTI11 , EXTI11_IRQ}
#define EXTI11_PC11				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_11 , EXTI11 , EXTI11_IRQ}
#define EXTI11_PD11				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_11 , EXTI11 , EXTI11_IRQ}
//EXTI12
#define EXTI12_PA12				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_12 , EXTI12 , EXTI12_IRQ}
#define EXTI12_PB12				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_12 , EXTI12 , EXTI12_IRQ}
#define EXTI12_PC12				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_12 , EXTI12 , EXTI12_IRQ}
#define EXTI12_PD12				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_12 , EXTI12 , EXTI12_IRQ}
//EXTI13
#define EXTI13_PA13				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_13 , EXTI13 , EXTI13_IRQ}
#define EXTI13_PB13				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_13 , EXTI13 , EXTI13_IRQ}
#define EXTI13_PC13				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_13 , EXTI13 , EXTI13_IRQ}
#define EXTI13_PD13				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_13 , EXTI13 , EXTI13_IRQ}
//EXTI14
#define EXTI14_PA14				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_14 , EXTI14 , EXTI14_IRQ}
#define EXTI14_PB14				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_14 , EXTI14 , EXTI14_IRQ}
#define EXTI14_PC14				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_14 , EXTI14 , EXTI14_IRQ}
#define EXTI14_PD14				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_14 , EXTI14 , EXTI14_IRQ}
//EXTI15
#define EXTI15_PA15				(EXTI_GPIO_Mapping_t){GPIOA , GPIO_PIN_15 , EXTI15 , EXTI15_IRQ}
#define EXTI15_PB15				(EXTI_GPIO_Mapping_t){GPIOB , GPIO_PIN_15 , EXTI15 , EXTI15_IRQ}
#define EXTI15_PC15				(EXTI_GPIO_Mapping_t){GPIOC , GPIO_PIN_15 , EXTI15 , EXTI15_IRQ}
#define EXTI15_PD15				(EXTI_GPIO_Mapping_t){GPIOD , GPIO_PIN_15 , EXTI15 , EXTI15_IRQ}

//@ref EXTI_Trigger_Define

#define EXTI_Trigger_Rising						0
#define EXTI_Trigger_Falling					1
#define EXTI_Trigger_RisingAndFalling			2

//@ref EXTI_IRQ_Define

#define EXTI_IRQ_ENABLE		  1
#define EXTI_IRQ_Disable      0

/*
* ===============================================
* APIs Supported by "MCAL EXTI DRIVER"
* ===============================================
*/

void MCAL_EXTI_Init(EXTI_PinConfig_t *EXTI_config);
void MCAL_EXTI_Update(EXTI_PinConfig_t *EXTI_config);
void MCAL_EXTI_Reset();

#endif /* STM32F103x5_EXTI_Driver_H_ */
