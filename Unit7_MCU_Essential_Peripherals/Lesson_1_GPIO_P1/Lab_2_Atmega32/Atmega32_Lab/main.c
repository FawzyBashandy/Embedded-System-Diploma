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
		for(unsigned char i = 5 ; i<8 ;i++)
		{
			setBit(PORTD,i);
			_delay_ms(100);
			clearBit(PORTD,i);
		}
		setBit(PORTD,4);
		_delay_ms(100);
		clearBit(PORTD,4);
   }
}
void GPIO_Init()
{
	setBits(DDRD,4,0b1111);//Set all port a as output
}
