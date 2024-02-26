/*
 * Keypad.h
 *
 * Created: 26/02/2024 02:02:55 ص
 *  Author: fawzy
 */ 

#include <avr/io.h>
#ifndef KEYPAD_H_
#define KEYPAD_H_

#define DataDir_Keypad			DDRD
#define ROWS					0b00001111
#define COLOMNS					0b11110000
#define Keypad_PORT				PORTD
#define Keypad_PIN				PIND
#define R0						0	
#define R1						1	
#define R2						2	
#define R3						3	
#define C0						4	
#define C1						5	
#define C2						6	
#define C3						7	

static unsigned char Keypad_Character[4][4] ={{'7','8','9','/'},
							  {'4','5','6','*'},
							  {'1','2','3','-'},
							  {'!','0','=','+'}};

void Keypad_INIT(void);
unsigned char Keypad_getCh(void);

#endif /* KEYPAD_H_ */