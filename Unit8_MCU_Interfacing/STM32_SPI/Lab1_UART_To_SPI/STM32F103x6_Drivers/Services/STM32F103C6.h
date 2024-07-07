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

#include "Platform_Types.h"
#include <stdio.h>
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
//Base addresses Cortex-M3
//-----------------------------

#define CORTEX_M3_INTERNAL_PERIPHERALS_MEMORY_BASE    	0xE0000000UL
#define NVIC_BASE										(CORTEX_M3_INTERNAL_PERIPHERALS_MEMORY_BASE + 0xE100)

/*================================================================*/
//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

#define RCC_BASE								0x40021000UL

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------

#define TIM2_BASE								0x40000000UL

#define USART2_BASE								0x40004400UL
#define USART3_BASE								0x40004800UL

#define SPI2_BASE								0x40003800UL
#define SPI3_BASE								0x40003C00UL
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

#define USART1_BASE								0x40013800UL

#define SPI1_BASE								0x40013000UL

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
	vuint32_t EXTICR[4];
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

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32_t SR;
	vuint32_t DR;
	vuint32_t BRR;
	vuint32_t CR1;
	vuint32_t CR2;
	vuint32_t CR3;
	vuint32_t GTPR;
}USART_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32_t CR1;
	vuint32_t CR2;
	vuint32_t SR;
	vuint32_t DR;
	vuint32_t CRCPR;
	vuint32_t RXCRCR;
	vuint32_t TXCRCR;
}SPI_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: TIM2
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32_t CR1;
	vuint32_t CR2;
	vuint32_t SMCR;
	vuint32_t DIER;
	vuint32_t SR;
	vuint32_t EGR;
	vuint32_t CCMR1;
	vuint32_t CCMR2;
	vuint32_t CCER;
	vuint32_t CNT;
	vuint32_t PSC;
	vuint32_t ARR;
	uint32_t  Reserved0;
	vuint32_t CCR1;
	vuint32_t CCR2;
	vuint32_t CCR3;
	vuint32_t CCR4;
	uint32_t  Reserved1;
	vuint32_t DCR;
	vuint32_t DMAR;
}TIM2_t;

/*----------NVIC registers-----------------*/
#define NVIC_ISER_BASE       ((volatile uint32 *)(NVIC_BASE + 0x000))	/*Interrupt set-enable registers base*/
#define NVIC_ISER0          *((volatile uint32 *)(NVIC_BASE + 0x000))	/*Interrupt[0 : 31] set-enable register*/
#define NVIC_ISER1          *((volatile uint32 *)(NVIC_BASE + 0x004))	/*Interrupt[32 : 63] set-enable register*/
#define NVIC_ISER2          *((volatile uint32 *)(NVIC_BASE + 0x008))	/*Interrupt[64 : 80] set-enable register*/


#define NVIC_ICER_BASE       ((volatile uint32 *)(NVIC_BASE + 0x080))	/*Interrupt clear-enable registers base*/
#define NVIC_ICER0          *((volatile uint32 *)(NVIC_BASE + 0x080))	/*Interrupt[0 : 31]  clear-enable register*/
#define NVIC_ICER1          *((volatile uint32 *)(NVIC_BASE + 0x084))	/*Interrupt[32 : 63] clear-enable register*/
#define NVIC_ICER2          *((volatile uint32 *)(NVIC_BASE + 0x088))	/*Interrupt[64 : 80] clear-enable register*/

#define NVIC_ISPR_BASE		 ((volatile uint32 *)(NVIC_BASE + 0x100))	/*Interrupt set-pending registers base*/
#define NVIC_ISPR0			*((volatile uint32 *)(NVIC_BASE + 0x100))	/*Interrupt[0 : 31]  set-pending register*/
#define NVIC_ISPR1			*((volatile uint32 *)(NVIC_BASE + 0x104))	/*Interrupt[32 : 63] set-pending register*/
#define NVIC_ISPR2			*((volatile uint32 *)(NVIC_BASE + 0x108))	/*Interrupt[64 : 80] set-pending register*/

#define NVIC_ICPR_BASE		 ((volatile uint32 *)(NVIC_BASE + 0x180))	/*Interrupt clear-pending registers base*/
#define NVIC_ICPR0			*((volatile uint32 *)(NVIC_BASE + 0x180))	/*Interrupt[0 : 31]  clear-pending register*/
#define NVIC_ICPR1			*((volatile uint32 *)(NVIC_BASE + 0x184))	/*Interrupt[32 : 63] clear-pending register*/
#define NVIC_ICPR2			*((volatile uint32 *)(NVIC_BASE + 0x188))	/*Interrupt[64 : 80] clear-pending register*/

#define NVIC_IABR_BASE		 ((volatile uint32 *)(NVIC_BASE + 0x200))	/*Interrupt active bit registers base*/
#define NVIC_IABR0			*((volatile uint32 *)(NVIC_BASE + 0x200))	/*Interrupt[0 : 31]  active bit register*/
#define NVIC_IABR1			*((volatile uint32 *)(NVIC_BASE + 0x204))	/*Interrupt[32 : 63] active bit register*/
#define NVIC_IABR2			*((volatile uint32 *)(NVIC_BASE + 0x208))	/*Interrupt[64 : 80] active bit register*/

#define NVIC_IPR_BASE		 ((volatile uint32 *)(NVIC_BASE + 0x300))	/*Interrupt set-priority registers base*/
#define NVIC_IPR0			*((volatile uint32 *)(NVIC_BASE + 0x300))	/*Interrupt[0  : 3 ] set-priority register*/
#define NVIC_IPR1			*((volatile uint32 *)(NVIC_BASE + 0x304))	/*Interrupt[4  : 7 ] set-priority register*/
#define NVIC_IPR2			*((volatile uint32 *)(NVIC_BASE + 0x308))	/*Interrupt[8  : 11] set-priority register*/
#define NVIC_IPR3			*((volatile uint32 *)(NVIC_BASE + 0x30C))	/*Interrupt[12 : 15] set-priority register*/
#define NVIC_IPR4			*((volatile uint32 *)(NVIC_BASE + 0x310))	/*Interrupt[16 : 19] set-priority register*/
#define NVIC_IPR5			*((volatile uint32 *)(NVIC_BASE + 0x314))	/*Interrupt[20 : 23] set-priority register*/
#define NVIC_IPR6			*((volatile uint32 *)(NVIC_BASE + 0x318))	/*Interrupt[24 : 27] set-priority register*/
#define NVIC_IPR7			*((volatile uint32 *)(NVIC_BASE + 0x31C))	/*Interrupt[28 : 31] set-priority register*/
#define NVIC_IPR8			*((volatile uint32 *)(NVIC_BASE + 0x320))	/*Interrupt[32 : 35] set-priority register*/
#define NVIC_IPR9			*((volatile uint32 *)(NVIC_BASE + 0x324))	/*Interrupt[36 : 39] set-priority register*/
#define NVIC_IPR10			*((volatile uint32 *)(NVIC_BASE + 0x328))	/*Interrupt[40 : 43] set-priority register*/
#define NVIC_IPR11			*((volatile uint32 *)(NVIC_BASE + 0x32C))	/*Interrupt[44 : 47] set-priority register*/
#define NVIC_IPR12			*((volatile uint32 *)(NVIC_BASE + 0x330))	/*Interrupt[48 : 51] set-priority register*/
#define NVIC_IPR13			*((volatile uint32 *)(NVIC_BASE + 0x334))	/*Interrupt[52 : 55] set-priority register*/
#define NVIC_IPR14			*((volatile uint32 *)(NVIC_BASE + 0x338))	/*Interrupt[56 : 59] set-priority register*/
#define NVIC_IPR15			*((volatile uint32 *)(NVIC_BASE + 0x33C))	/*Interrupt[60 : 63] set-priority register*/
#define NVIC_IPR16			*((volatile uint32 *)(NVIC_BASE + 0x340))	/*Interrupt[64 : 67] set-priority register*/
#define NVIC_IPR17			*((volatile uint32 *)(NVIC_BASE + 0x344))	/*Interrupt[68 : 71] set-priority register*/
#define NVIC_IPR18			*((volatile uint32 *)(NVIC_BASE + 0x348))	/*Interrupt[72 : 75] set-priority register*/
#define NVIC_IPR19			*((volatile uint32 *)(NVIC_BASE + 0x34C))	/*Interrupt[76 : 79] set-priority register*/
#define NVIC_IPR20			*((volatile uint32 *)(NVIC_BASE + 0x350))	/*Interrupt[80] 	 set-priority register*/

#define NVIC_STIR			*((volatile uint32 *)(0xE000EF00 + 0xE00))	/*Software trigger interrupt register*/
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

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: USART
//-*-*-*-*-*-*-*-*-*-*-*

#define USART1 			((USART_t *)USART1_BASE)
#define USART2 			((USART_t *)USART2_BASE)
#define USART3 			((USART_t *)USART3_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: SPI
//-*-*-*-*-*-*-*-*-*-*-*

#define SPI1 			((SPI_t *)SPI1_BASE)
#define SPI2 			((SPI_t *)SPI2_BASE)
#define SPI3 			((SPI_t *)SPI3_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: TIM2
//-*-*-*-*-*-*-*-*-*-*-*

#define TIM2 			((TIM2_t *)AFIO_BASE)

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*

#define APB2_Peri_CLOCK_ENABLE(periID) ( RCC->APB2ENR |=(1<<periID) )



//===========EXTI=============
//ENABLE
#define NVIC_IRQ6_EXTI0_Enable 			(NVIC_ISER0 |= 1 << 6)
#define NVIC_IRQ7_EXTI1_Enable 			(NVIC_ISER0 |= 1 << 7)
#define NVIC_IRQ8_EXTI2_Enable 			(NVIC_ISER0 |= 1 << 8)
#define NVIC_IRQ9_EXTI3_Enable 			(NVIC_ISER0 |= 1 << 9)
#define NVIC_IRQ10_EXTI4_Enable 		(NVIC_ISER0 |= 1 << 10)

#define NVIC_IRQ23_EXTI9_5_Enable 		(NVIC_ISER0 |= 1 << 23)
#define NVIC_IRQ40_EXTI15_10_Enable 	(NVIC_ISER1 |= 1 << 8)

//DISABLE

#define NVIC_IRQ6_EXTI0_DISABLE 		(NVIC_ICER0 |= 1 << 6)
#define NVIC_IRQ7_EXTI1_DISABLE 		(NVIC_ICER0 |= 1 << 7)
#define NVIC_IRQ8_EXTI2_DISABLE 		(NVIC_ICER0 |= 1 << 8)
#define NVIC_IRQ9_EXTI3_DISABLE 		(NVIC_ICER0 |= 1 << 9)
#define NVIC_IRQ10_EXTI4_DISABLE 		(NVIC_ICER0 |= 1 << 10)

#define NVIC_IRQ23_EXTI9_5_DISABLE 		(NVIC_ICER0 |= 1 << 23)
#define NVIC_IRQ40_EXTI15_10_DISABLE 	(NVIC_ICER1 |= 1 << 8)

//===========USART=============

//Enable
#define NVIC_IRQ37_USART1_ENABLE 		(NVIC_ISER1 |= 1 << 5)
#define NVIC_IRQ38_USART2_ENABLE		(NVIC_ISER1 |= 1 << 6)
#define NVIC_IRQ39_USART3_ENABLE		(NVIC_ISER1 |= 1 << 7)
//Disable
#define NVIC_IRQ37_USART1_DISABLE		(NVIC_ICER1 |= 1 << 7)
#define NVIC_IRQ38_USART2_DISABLE		(NVIC_ICER1 |= 1 << 7)
#define NVIC_IRQ39_USART3_DISABLE		(NVIC_ICER1 |= 1 << 7)
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*


#endif /* STM32F103C6_H_ */
