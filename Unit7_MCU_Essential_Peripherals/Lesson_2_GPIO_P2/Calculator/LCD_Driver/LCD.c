/*
 * LCD.c
 *
 * Created: 25/02/2024 03:19:12 ص
 *  Author: Fawzy
 */ 
#include "LCD.h"
#include <stdio.h>
#include <stdlib.h>
void LCD_INIT()
{
	_delay_ms(20);
	DataDir_LCD_CTRL |= (1<<EN_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	LCD_CTRL &= ~ (1<<EN_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	DataDir_LCD_PORT = 0xFF << DATA_shift; //To work in both FOUR & EIGH BIT MODE
	_delay_ms(15);
	LCD_clear_screen();
	#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	#ifdef FOUR_BIT_MODE
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}
void LCD_clear_screen()
{
		LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}
void LCD_WRITE_COMMAND(unsigned char command)
{
	LCD_check_isbusy();
	#ifdef EIGHT_BIT_MODE
	LCD_PORT = command;
	LCD_CTRL &= ~(1<<RW_SWITCH | 1<<RS_SWITCH);
	LCD_Kick();
	#endif
	#ifdef FOUR_BIT_MODE
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0); //Send the higher 4 bits first;
	LCD_CTRL &= ~(1<<RW_SWITCH | 1<<RS_SWITCH);
	LCD_Kick();
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);	//Then Send the lower 4 bits by shifting them (making them the higher 4 bits then)
	LCD_CTRL &= ~(1<<RW_SWITCH | 1<<RS_SWITCH);
	LCD_Kick();
	#endif
}
void LCD_WRITE_CHAR(unsigned char character)
{
	static unsigned char tracker=0;
	#ifdef EIGHT_BIT_MODE
	LCD_check_isbusy();
	LCD_PORT = character;
	LCD_CTRL |= (1<<RS_SWITCH);
	LCD_CTRL &=~(1<<RW_SWITCH);
	#endif
	#ifdef FOUR_BIT_MODE
	//LCD_check_isbusy(); //Will cause issues here
	//WE did the same thing we did in LCD_WRITE_COMMAND
	LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
	LCD_CTRL |= (1<<RS_SWITCH);
	LCD_CTRL &=~(1<<RW_SWITCH);
	LCD_Kick();
	LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
	LCD_CTRL |= (1<<RS_SWITCH);
	LCD_CTRL &=~(1<<RW_SWITCH);
	//Note : the next LCD_KICK() will be excecuted in both modes (you can also do it like in LCD_WRITE_COMMAND)
	#endif
	if(tracker==16)
	{
		LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW);
	}
	else if(tracker == 32)
	{
		LCD_clear_screen();
		_delay_ms(10);
	}
	LCD_Kick();
	tracker++;
}
void LCD_WRITE_STRING(char* string){
	int count = 0;
	while (*string > 0){
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(1,0);
		}
		else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(0,0);
			count = 0;
		}
	}
}
void LCD_check_isbusy(void)
{
	DataDir_LCD_PORT &=~(0xFF<<DATA_shift);
	LCD_CTRL |=(1<<RW_SWITCH);
	LCD_CTRL &=~(1<<RS_SWITCH);
	LCD_Kick();
	DataDir_LCD_PORT |= (0xFF <<DATA_shift);
	LCD_CTRL &=~(1<<RW_SWITCH);
}
void LCD_Kick(void)
{
	LCD_CTRL &= ~(1<<EN_SWITCH);
	_delay_ms(50);
	LCD_CTRL |= (1<<EN_SWITCH);
}
void LCD_GOTO_XY(unsigned char line, unsigned char position)
{
	if(line == 0 && (position < 16 && position >= 0))
	{
		LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW + position);
	}
	else if (line == 1 && (position < 16 && position >= 0))
	{
		LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + position);
	}
}
void LCD_Display_Number(int number)
{
	char str[7]; //assume max number is 7 digits 
	itoa(number ,str,10);
	LCD_WRITE_STRING(str);
}
void LCD_Display_Real_Number(double num) {
	int integerPart = (int)num;
	int fractionalPart = (int)((num - integerPart) * 100); // For 2 decimal places
	char double_Str[15];
	snprintf(double_Str, sizeof(double_Str), "%d.%02d", integerPart, fractionalPart);
	LCD_WRITE_STRING(double_Str);
}