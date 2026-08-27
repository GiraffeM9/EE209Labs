/*
 * Prelab4.c
 *
 * Created: 27/08/2026 2:19:00 pm
 * Author : Mayita
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB = 0x7F;   // PB7 = input (0), all others = output (1)
	DDRC = 0x00; // all inputs
	DDRD = 0x00; // all inputs
	
	
    while (1) 
    {
		if ((PINB & (1 << PB7)) == 0){
			PORTB |= (1 << PB5);   // LED on
		}
		else{
			PORTB &= ~(1 << PB5);  // LED off
		}

    }
}

