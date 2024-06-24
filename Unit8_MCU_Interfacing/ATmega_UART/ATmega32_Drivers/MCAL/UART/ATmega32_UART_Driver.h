/*
 * ATmega32_USART_Driver.h
 *
 *  Created on: March 5 , 2024
 *      Author: Fawzy Bashandy
 */

#ifndef ATMEGA32_UART_H_
#define ATMEGA32_UART_H_

/*================================================================
* Includes
*================================================================*/
#include "Atmega32.h"

/*================================================================
* Macros Configuration References
*================================================================*/
#define URSEL   7   /* This bit selects between accessing the UCSRC or the UBRRH Register */
#define UCSZ0   1
#define TXEN    3
#define RXEN    4
#define UDRE    5   /* USART Data Register Empty */
#define RXC     7   /* USART Receive Complete */

/*================================================================
* APIs Supported by "MCAL USART DRIVER"
*================================================================*/

/*
================================================================
* @Func_name  : MCAL_USART_Init
* @brief      : Initializes the USART module with a char size of 8 bits, no parity, one stop bit and 9600 baud-rate.
* @param [in] : none.
* @param [out]: none.
* @return_val : none.
* Note        : none.
================================================================
*/
void MCAL_USART_Init(void);

/*
================================================================
* @Func_name  : MCAL_USART_Send_Char
* @brief      : Send an 8 bit character through the USART.
* @param [in] : data: the 8 bit data to be sent.
* @param [out]: none.
* @return_val : none.
* Note        : none.
================================================================
*/
void MCAL_USART_Send_Char(uint8_t data);

/*
================================================================
* @Func_name  : MCAL_USART_Get_Char
* @brief      : Receives an 8 bit character from the USART.
* @param [in] : none.
* @param [out]: none.
* @return_val : The data to be received.
* Note        : none.
================================================================
*/
uint8_t MCAL_USART_Get_Char(void);

/*
================================================================
* @Func_name  : MCAL_USART_Send_String
* @brief      : Sends a string through the USART.
* @param [in] : string: pointer to the string to send.
* @param [out]: none.
* @return_val : none.
* Note        : none.
================================================================
*/
void MCAL_USART_Send_String(uint8_t* string);

/*
================================================================
* @Func_name  : MCAL_USART_Get_String
* @brief      : Receives a string through the USART.
* @param [in] : buffer: pointer to the buffer to store the received string.
* @param [in] : bufferSize: maximum length of the string to be received.
* @return_val : none.
* Note        : This function will receive characters until the end of the string or until the return carriage
*               character is pressed.
================================================================
*/
void MCAL_USART_Get_String(uint8_t* buffer, uint8_t bufferSize);

#endif /* ATMEGA32_UART_H_ */
