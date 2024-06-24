/*
 * ATmega32.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */

#ifndef ATmega32_H_
#define ATmega32_H_

//-----------------------------
//Includes
//-----------------------------

#include <stdio.h>
#include <stdint.h>
#include "Platform_Types.h"

/*================================================================*/
//-----------------------------
//Base addresses for Memories
//-----------------------------


#define DATA_ADDRESS_SPACE          0x00
#define PERIPHERAL_MEMORY_BASE      0x20
#define SRAM_MEMORY_BASE            0x60

/*================================================================*/
//-----------------------------
//Base addresses for Data bus registers
//-----------------------------

#define GPIOA_BASE								(uint8_t)(PERIPHERAL_MEMORY_BASE + 0x19)
#define GPIOB_BASE								(uint8_t)(PERIPHERAL_MEMORY_BASE + 0x16)
#define GPIOC_BASE								(uint8_t)(PERIPHERAL_MEMORY_BASE + 0x13)
#define GPIOD_BASE								(uint8_t)(PERIPHERAL_MEMORY_BASE + 0x10)

#define USART_BASE								(uint8_t)(PERIPHERAL_MEMORY_BASE + 0x0C)

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	uint8_t PIN;
	uint8_t DDR;
	uint8_t PORT;
}GPIO_t;

#define SFIOR   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x30))  /*Special Function IO Register*/

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct{
	vuint8_t UDR;                 /*USART I/O data Register*/
	vuint8_t UCSRA;               /*USART control/status Register A*/
	vuint8_t UCSRB;               /*USART control/status Register B*/
	vuint8_t UBRRL;               /*USART Baud Rate Register Low byte*/
}USART_t;

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

#define GPIOA 			((GPIO_t *)GPIOA_BASE)
#define GPIOB 			((GPIO_t *)GPIOB_BASE)
#define GPIOC 			((GPIO_t *)GPIOC_BASE)
#define GPIOD 			((GPIO_t *)GPIOD_BASE)
#define GPIOE 			((GPIO_t *)GPIOE_BASE)

/*-----------------USART------------------------*/

#define UDR     *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x0C))
#define UCSRA   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x0B))
#define UCSRB   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x0A))
#define UBRRL   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x09))
#define UBRRH   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x20))  /*USART Baud Rate Register High*/
#define UCSRC   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x20))  /*USART control/status Register C*/

#endif /* ATmega32_H_ */
