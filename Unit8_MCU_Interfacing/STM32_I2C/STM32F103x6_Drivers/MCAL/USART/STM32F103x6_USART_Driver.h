/*
 * STM32_F103C6_USART_Driver.h
 *
 *  Created on: Feb 28, 2024
 *      Author: Fawzy Bashandy
 */

#ifndef STM32_F103C6_USART_DRIVER_H_
#define STM32_F103C6_USART_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include <BitMath.h>
#include <Platform_Types.h>
#include <STM32F103C6.h>
#include <stdint.h>

#include <GPIO/STM32F103x6_GPIO_Driver.h>

//-----------------------------
//General structures
//-----------------------------

typedef enum {Polling,Interrupt}Mechanism;

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	USART_t * USARTx;							/*Specify the instance of USART required
					   	  	  	  	  	  	  	  This parameter must be a value of @ref USARTx_Define*/

	uint16_t	  TxRx_Mode;						/*Specify UART_Mode (Sending / Receiving / BOTH)
					   	  	  	  	  	  	  	  This parameter must be a value of @ref USART_TxRxMode_Define*/

	uint32_t  BaudRate;							/*Specify Tx/Rx standard baudrate required
					   	  	  	  	  	  	  	  This parameter must be a value of @ref USART_BaudRate_Define*/

	uint32_t   WordLength;						/*Specify the word length required
					   	  	  	  	  	  	  	  This parameter must be a value of @ref USART_WordLength_Define*/

	uint32_t   Parity;							/*Specify the parity bit in the USART Frame
					   	  	  	  	  	  	  	  This parameter must be a value of @ref USART_Parity_Define*/

	uint32_t   StopBitsLength;					/*Specify the number of stop bits in USART Frame
					   	  	  	  	  	  	  	  This parameter must be a value of @ref USART_StopBitsLength_Define*/

	Mechanism Mechanism_type;					/*Specify the Tx/Rx mechanism
					   	  	  	  	  	  	  	  This parameter must be a value of @ref USART_MechanismType_Define*/

}USART_Config_t;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref USARTx_Define

#define USARTx_Instance1				USART1
#define USARTx_Instance2				USART2
#define USARTx_Instance3				USART3

//@ref USART_TxRxMode_Define

#define USART_TxRxMode_Transmiting		(1<<3)
#define USART_TxRxMode_Receiving		(1<<2)
#define USART_TxRxMode_BOTH_TXRX		(0b11<<2)

//@ref USART_BaudRate_Define

#define USART_BaudRate_2400				(uint32_t)(2400)
#define USART_BaudRate_9600				(uint32_t)(9600)
#define USART_BaudRate_19200			(uint32_t)(19200)
#define USART_BaudRate_57600			(uint32_t)(57600)
#define USART_BaudRate_115200			(uint32_t)(115200)
#define USART_BaudRate_230400			(uint32_t)(230400)
#define USART_BaudRate_460800			(uint32_t)(460800)
#define USART_BaudRate_921600			(uint32_t)(921600)
#define USART_BaudRate_2250000          (uint32_t)(2250000)
#define USART_BaudRate_4500000			(uint32_t)(4500000)

//@ref USART_WordLength_Define

#define USART_WordLength_8b				0
#define USART_WordLength_9b				(1 << 12)

//@ref USART_Parity_Define

#define USART_Parity_EVEN				(1<<10)
#define USART_Parity_ODD				((1 << 10) | (1 << 9)
#define USART_Parity_NONE				0

//@ref USART_StopBitsLength_Define

#define USART_StopBitsLength_HalfBit			(1 << 12)
#define USART_StopBitsLength_OneBit				0
#define USART_StopBitsLength_OneAndHalfBit		(3 << 12)
#define USART_StopBitsLength_TwoBits			(2 << 12)


//@ref USART_IRQ_Define

#define USART_IRQ_ERROR         0
#define USART_IRQ_IDLE          4
#define USART_IRQ_RXNE          5
#define USART_IRQ_TC            6
#define USART_IRQ_TXE           7
#define USART_IRQ_PE            8
#define USART_IRQ_CTS           10

//@ref USART_MechanismType_Define

#define USART_MechanismType_POLLING				Polling
#define USART_MechanismType_Interrupt			Interrupt

/**************************************************************************************************************************
*===============================================
*         Control/Status Registers Pins Macros
*===============================================
*/

/*
*  USART control register 1 (USART_CR1) bit definitions.
*/
#define USART_CR1_UE        0x00002000      /* USART enable */
#define USART_CR1_M         0x00001000      /* Word length */
#define USART_CR1_PCE       0x00000400      /* Parity control enable */
#define USART_CR1_PS        0x00000200      /* Parity selection */
#define USART_CR1_PEIE      0x00000100      /* PE interrupt enable */
#define USART_CR1_TXEIE     0x00000080      /* TXE interrupt enable */
#define USART_CR1_TCIE      0x00000040      /* Transmission complete interrupt enable */
#define USART_CR1_RXNEIE    0x00000020      /* RXNE interrupt enable */
#define USART_CR1_IDLEIE    0x00000010     /* IDLEIE interrupt enable */
#define USART_CR1_TE        0x00000008      /* Transmitter enable */
#define USART_CR1_RE        0x00000004      /* Receiver enable */

/*
*  USART control register 2 (USART_CR2) bit definitions.
*/
#define USART_CR2_STOP      0x00003000      /* STOP bits */

/*
*  USART control register 3 (USART_CR3) bit definitions.
*/
#define USART_CR3_CTSIE     0x00000400      /* CTS interrupt enable */
#define USART_CR3_CTSE      0x00000200      /* CTS enable */
#define USART_CR3_RTSE      0x00000100      /* RTS enable */
#define USART_CR3_EIE       0x00000001      /* Error interrupt enable */

/*
*  USART Status Register (USART_SR) bit definitions.
*/
#define USART_SR_CTS            0x00000200      /*CTS flag, This bit is set by hardware when the CTS input toggles*/
#define USART_SR_TXE            0x00000080      /*Transmit data register empty flag*/
#define USART_SR_TC             0x00000040      /*Transmission complete flag*/
#define USART_SR_RXNE           0x00000020      /*Read data register not empty flag*/
#define USART_SR_IDLE           0x00000010      /*IDLE line detected flag*/
#define USART_SR_ORE            0x00000008      /*Overrun error flag*/
#define USART_SR_NE             0x00000004      /*Noise error flag*/
#define USART_SR_FE             0x00000002      /*Framing error flag*/
#define USART_SR_PE             0x00000001      /*Parity error flag*/

#define USART_TX_BUFFER_EMPTY       1
#define USART_TX_BUFFER_FULL        0

#define USART_RX_BUFFER_EMPTY       0
#define USART_RX_BUFFER_FULL        1

#define USART_TRANS_NOT_COMPLETE    0
/*
* ===============================================
* APIs Supported by "MCAL USART DRIVER"
* ===============================================
*/
void MCAL_USART_Init(USART_Config_t * USARTx);
void MCAL_USART_DeInit(USART_Config_t * USARTx);
void MCAL_USART_SendData(USART_Config_t * USARTx , uint16_t data);
void MCAL_USART_Enable_Interrupt(USART_Config_t * USARTx , uint8_t IRQ_Event , void ( * P_IRQEvent_CallBack)(void));
void MCAL_UART_Interrupt_Disable(USART_Config_t * USART, uint8_t IRQ_Event);
void MCAL_USART_ReceiveData(USART_Config_t * USARTx , uint16_t * data);

#endif /* STM32_F103C6_USART_DRIVER_H_ */
