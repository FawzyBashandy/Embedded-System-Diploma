#include "Uart.h"
unsigned char String[100]="Learn-In-Depth:Fawzy Mohamed";
void main(void)
{
	Uart_Send_String(String);
}