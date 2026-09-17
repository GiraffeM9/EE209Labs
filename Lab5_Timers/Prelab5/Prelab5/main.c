/*
 * Prelab5.c
 *
 * Created: 17/09/2026 12:10:28 pm
 * Author : Mayit
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// initialisation
	DDRB = 0xFF; // all outputs
	DDRC = 0x00; // all inputs
	DDRD = 0x00; // all inputs

    while (1) 
    {
		// turn on for 375ms
		PORTB |= (1 << PORTB5);
		_delay_ms(375);
		
		// turn off for 125ms
		PORTB &= ~(1 << PORTB5);
		_delay_ms(125);
    }
}

