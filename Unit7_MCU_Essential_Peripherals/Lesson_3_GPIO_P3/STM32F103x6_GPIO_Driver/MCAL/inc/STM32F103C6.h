/*
 * STM32F103C6.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */

#ifndef STM32F103C6_H_
#define STM32F103C6_H_

//-----------------------------
//Includes
//-----------------------------

#include <stdio.h>
#include "Platform_Types.h"
#include <stdint.h>

/*================================================================*/
//-----------------------------
//Base addresses for Memories
//-----------------------------


#define SRAM_BASE 								0x20000000UL
#define FLASH_MEMORY_BASE						0x08000000UL
#define SYSTEM_MEMORY_BASE 						0x1FFFF000UL

#define Peripherals_BASE						0x40000000UL

#define Cortex_M3_Internal_Peripherals_BASE 	0xE0000000UL

/*================================================================*/
//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

#define RCC_BASE								0x40021000UL

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------

//Will be added incrementally

//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------

#define GPIOA_BASE								0x40010800UL
#define GPIOB_BASE								0x40010C00UL
#define GPIOC_BASE								0x40011000UL
#define GPIOD_BASE								0x40011400UL
#define GPIOE_BASE								0x40011800UL

#define AFIO_BASE								0x40010000UL

#define EXTI_BASE								0x40010400UL

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32_t CRL;
	vuint32_t CRH;
	vuint32_t IDR;
	vuint32_t ODR;
	vuint32_t BSRR;
	vuint32_t BRR;
	vuint32_t LCKR;
}GPIO_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32_t EVCR;
	vuint32_t MAPR;
	vuint32_t EXTICR1;
	vuint32_t EXTICR2;
	vuint32_t EXTICR3;
	vuint32_t EXTICR4;
	uint32_t  RESERVED;
	vuint32_t MAPR2;
}AFIO_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32_t CR;
	vuint32_t CFGR;
	vuint32_t CIR;
	vuint32_t APB2RSTR;
	vuint32_t APB1RSTR;
	vuint32_t AHBENR;
	vuint32_t APB2ENR;
	vuint32_t APB1ENR;
	vuint32_t BDCR;
	vuint32_t CSR;
	vuint32_t AHBSTR;
	vuint32_t CFGR2;
}RCC_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32_t IMR;
	vuint32_t EMR;
	vuint32_t RTSR;
	vuint32_t FTSR;
	vuint32_t SWIER;
	vuint32_t PR;
}EXTI_t;

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: GPIO
//-*-*-*-*-*-*-*-*-*-*-*
/*Note: LQFP48 package has PORT(A, B)
,part of PORT(C,D) and PORTE isn't
used
*/

#define GPIOA 			((GPIO_t *)GPIOA_BASE)
#define GPIOB 			((GPIO_t *)GPIOB_BASE)
#define GPIOC 			((GPIO_t *)GPIOC_BASE)
#define GPIOD 			((GPIO_t *)GPIOD_BASE)
#define GPIOE 			((GPIO_t *)GPIOE_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: RCC
//-*-*-*-*-*-*-*-*-*-*-*

#define RCC 			((RCC_t *)RCC_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: EXTI
//-*-*-*-*-*-*-*-*-*-*-*

#define EXTI 			((EXTI_t *)EXTI_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: AFIO
//-*-*-*-*-*-*-*-*-*-*-*

#define AFIO 			((AFIO_t *)AFIO_BASE)

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define APB2_Peri_CLOCK_ENABLE(periID) ( RCC->APB2ENR |=(1<<periID) )


//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*


#endif /* STM32F103C6_H_ */
