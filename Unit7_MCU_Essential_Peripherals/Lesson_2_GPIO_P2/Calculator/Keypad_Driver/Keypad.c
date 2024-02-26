/*
 * Keypad.c
 *
 * Created: 26/02/2024 02:02:41 ص
 *  Author: fawzy
 */ 
#include "Keypad.h"
void Keypad_INIT(void)
{
	DataDir_Keypad |=COLOMNS; //Set COLOMNS as output
	DataDir_Keypad &=~(ROWS); //Set ROWS as input
	Keypad_PORT = 0xFF; //Set COLOMNS as output high , set rows as input pull-up resistance
}

unsigned char Keypad_getCh(void)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			Keypad_PORT &= ~(1<<(j+4));
			if((Keypad_PIN & (1 << i)) == 0)
			{
				while((Keypad_PIN & (1 << i)) == 0){}; //Single Pressing MODE
				return Keypad_Character[i][j];
			}
			Keypad_PORT |= (1<<(j+4));
		}
	}
	return '$'; //to indicate no key pressed
}