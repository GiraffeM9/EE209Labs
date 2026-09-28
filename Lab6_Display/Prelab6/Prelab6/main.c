/*
 * Prelab6.c
 *
 * Created: 25/09/2026 7:57:12 pm
 * Author : Mayit
 */ 

#define F_CPU 2000000UL

#include "display.h"

#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
	DDRB |= 1 << DDB0 | 1 << DDB1 | 1 << DDB4;
	DDRC |= 1 << DDC5 | 1 << DDC4 | 1 << DDC3 | 1 << DDC2 | 1 << DDC1 | 1 << DDC0;
	DDRB &= ~(1 << DDB7);
	
	display_init();
	
	uint8_t counter = 0;
	
	while (1)
	{
		displayNumber(counter);

		// Check button
		if (!(PINB & (1 << PINB7)))
		{
			counter = 0;
		}

		_delay_ms(1000);

		counter++;

		if (counter > 9)
		{
			counter = 0;
		}
	}
}

