#define UART0DR *(volatile unsigned int *)((unsigned char *)0x101f1000)
void Uart_Send_String(unsigned char *P_String)
{
	while(*P_String !='\0')
	{
		UART0DR=(unsigned int)*P_String;
		P_String++;
	}
}