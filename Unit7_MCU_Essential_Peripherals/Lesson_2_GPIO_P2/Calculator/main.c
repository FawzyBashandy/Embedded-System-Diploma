/*
 * LCD_Keypad.c
 *
 * Created: 25/02/2024 03:18:08 ص
 * Author : fawzy
 */ 

#include <avr/io.h>
#include "LCD/LCD.h"
#include "Keypad/Keypad.h"
#include <stdlib.h>

int main(void)
{
	LCD_INIT();
	/*LCD_WRITE_STRING("Fawzy Bashandy");
	LCD_GOTO_XY(1,0);
	LCD_Display_Number(25);
	LCD_WRITE_CHAR(':');
	LCD_Display_Number(02);
	LCD_WRITE_CHAR(':');
	LCD_Display_Number(2024);
	LCD_WRITE_CHAR(' ');
	LCD_Display_Real_Number(1.20);
	LCD_WRITE_STRING("AM");*/
	Keypad_INIT();
    unsigned char pressed_key;
    unsigned char op1[7] = {0}, op2[7] = {0}, operator = 0;
    int i = 0, j = 0, result = 0;
    LCD_clear_screen();
    while (1)
    {
	    pressed_key = Keypad_getCh(); // Assuming this function returns '$' if no key is pressed

	    if(pressed_key == '$') // No key pressed
	    {
		    continue;
	    }
	    else if(pressed_key == '!') // Clear screen and reset calculator
	    {
		    LCD_clear_screen();
		    i = j = 0; // Reset indexes
		    op1[0] = op2[0] = operator = 0; // Reset operands and operator
		    continue;
	    }
	    else if(pressed_key >= '0' && pressed_key <= '9') // Check for numeric input
	    {
		    LCD_WRITE_CHAR(pressed_key); // Display the pressed key

		    if(operator == 0) // Still capturing the first operand
		    {
			    op1[i++] = pressed_key;
		    }
		    else // Capturing the second operand
		    {
			    op2[j++] = pressed_key;
		    }
	    }
	    else if(pressed_key == '=')
	    {
		    LCD_WRITE_CHAR(pressed_key);

		    // Perform the operation
		    switch(operator)
		    {
			    case '+':
			    result = atoi(op1) + atoi(op2);
			    break;
			    case '*':
			    result = atoi(op1) * atoi(op2);
			    break;
			    case '-':
			    result = atoi(op1) - atoi(op2);
			    break;
			    case '/':
			    result = atoi(op1) / atoi(op2);
			    break;
			    default:
			    continue;
			    break;
		    }
			 LCD_Display_Number(result);
			_delay_ms(2000);

			// Clear for next operation
			LCD_clear_screen();
			memset(op1, 0, sizeof(op1)); // Clear op1
			memset(op2, 0, sizeof(op2)); // Clear op2
			i = j = 0;
			operator = 0;
	    }
	    else // Capture operator
	    {
		    operator = pressed_key;
		    LCD_WRITE_CHAR(pressed_key);
	    }
    }
    }
