/*
 * Unit7_Section1.c
 *
 * Created: 23/02/2024 02:34:35 م
 * Author : Fawzy Bashandy
 */ 
#define F_CPU 8000000ul
#include "Bit_Math.h"
#include "IO.h"
#include <util/delay.h>
void GPIO_Init();

int main(void)
{
	GPIO_Init();
    while (1) 
   {
		for(unsigned char i = 0 ; i<8 ;i++)
		{
			setBit(PORTA,i);
			_delay_ms(50);
		}
		for(unsigned char j =7 ; j>=0 ; j--)
		{
			clearBit(PORTA,j);
			_delay_ms(50);
		}
    }
}
void GPIO_Init()
{
	setBits(DDRA,0,0xFF);//Set all port a as output
}
