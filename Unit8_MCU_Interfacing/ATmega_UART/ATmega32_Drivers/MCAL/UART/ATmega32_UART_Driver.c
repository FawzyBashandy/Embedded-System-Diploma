/*
 * ATmega32_USART_Driver.c
 *
 *  Created on: March 5 , 2024
 *      Author: Fawzy Bashandy
 */

/*================================================================
* Includes
*================================================================*/
#include "ATmega32_UART_Driver.h"
#include "Atmega32.h"

/*================================================================
* APIs functions definitions
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
void MCAL_USART_Init(void)
{
    /* Set baud rate */
    uint16_t ubrr_value = 51;  // for 9600 baud rate

    UBRRH = (uint8_t)(ubrr_value >> 8);
    UBRRL = (uint8_t)ubrr_value;

    /* Set frame format: 8 data bits, no parity, 1 stop bit */
    UCSRC = 0b10000110;  

    /* Enable transmitter and receiver */
    UCSRB = (1 << TXEN) | (1 << RXEN);
}

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
void MCAL_USART_Send_Char(uint8_t data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSRA & (1 << UDRE)))
        ;

    /* Put data into buffer, sends the data */
    UDR = data;
}

/*
================================================================
* @Func_name  : MCAL_USART_Get_Char
* @brief      : Receives an 8 bit character from the USART.
* @param [in] : none.
* @param [out]: none.
* @return_val : The data received.
* Note        : none.
================================================================
*/
uint8_t MCAL_USART_Get_Char(void)
{
    /* Wait for data to be received */
    while (!(UCSRA & (1 << RXC)))
        ;

    /* Get and return received data from buffer */
    return UDR;
}

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
void MCAL_USART_Send_String(uint8_t* string)
{
    while (*string)
    {
        MCAL_USART_Send_Char(*string++);
    }
}

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
void MCAL_USART_Get_String(uint8_t* buffer, uint8_t bufferSize)
{
    uint8_t count = 0, input;
    while (count < bufferSize - 1)
    {
        input = MCAL_USART_Get_Char();
        if (input == '\r')
        {
            break;
        }
        buffer[count++] = input;
    }

    buffer[count] = '\0';
}
