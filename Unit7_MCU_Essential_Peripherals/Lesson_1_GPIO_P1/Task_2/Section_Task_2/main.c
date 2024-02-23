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
	int counter = 0,flag=0;
    while (1) 
   {
		if(readBit(PINC,1) == 0)
		{
			switch(flag)
			{
				case 0: setBit(PORTA,counter);
						counter++;
						flag = (counter<8)?0:1;
						break;
				case 1: clearBit(PORTA,counter);
						counter--;
						flag = (counter>=0)?1:0;
						break;
			}
		}
		_delay_ms(25);
   }
}
void GPIO_Init()
{
	setBits(DDRA,0,0xFF);//Set all port a as output
	clearBit(DDRC,1); //PA1 as input
	setBit(PORTC,1); //PA1 as input with pull-up activated
}
