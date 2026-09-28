/*
 * Lab6 pt1.c
 *
 * Created: 29/09/2026 12:15:27 pm
 * Author : Mayit
 */ 

#define F_CPU 2000000UL

#include "display.h"
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	DDRB &= ~(1 << DDB7);   // button input

	display_init();
	timer0_init();
	sei();

	while (1)
	{
		// 10 x 100ms = 1s, sampling the button each time
		for (uint8_t i = 0; i < 10; i++)
		{
			_delay_ms(100);
			if (!(PINB & (1 << PINB7)))
			{
				display_reset();
				i = 255;   // wraps to 0 after i++, restarts the 1s wait
			}
		}
		display_increment();
	}
}

