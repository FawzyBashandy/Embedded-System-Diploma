/*
 * main.c
 *
 * Created: 9/23/2023 8:17:16 AM
 *  Author: Fawzy
 */ 
#define F_CPU 8000000ul
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
void GPIO_Init();
void Interrupt_Init();

int main(void)
{
	GPIO_Init();
	Interrupt_Init();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}



void GPIO_Init()
{
	DDRD &= ~(0b11 << 2 );
	DDRD |= (0b111<<5); //Make PD5,6,7 As outputs
	PORTD &= ~(0b111<5); //Initialize all leds as off
	
}
void Interrupt_Init()
{
	MCUCR |= (1 << 0) ; //Make INT0 any logical change triggered
	MCUCR |= (0b11 << 2); //Make INT1 Rising Edge triggered
	MCUCSR &= ~(1<<6); //optional -> Make sure that INT2 is Falling edge triggered
	GICR |= (0b111 << 5); //Un-mask(enable) Interrupts from INT0,1,2
	SREG |= (1 << 7); //Enable Global interrupt
	
}
ISR(INT0_vect)
{
	PORTD |= (1<<5);//Enable led at PD5
	_delay_ms(1000); //Wait 1 second
	PORTD &= ~(1<<5); //Disable LED
	//This step is Optional
	GIFR |= (1<<6); //Clear Flag of INT0 (ACK)
}
ISR(INT1_vect)
{
		PORTD |= (1<<6);//Enable led at PD5
		_delay_ms(1000); //Wait 1 second
		PORTD &= ~(1<<6); //Disable LED
		//This step is Optional
		GIFR |= (1<<7); //Clear Flag of INT0 (ACK)
}
ISR(INT2_vect)
{
		PORTD |= (1<<7);//Enable led at PD5
		_delay_ms(1000); //Wait 1 second
		PORTD &= ~(1<<7); //Disable LED
		//This step is Optional
		GIFR |= (1<<5); //Clear Flag of INT0 (ACK)
}