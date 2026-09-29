/*
 * Lab6 pt2.c
 *
 * Created: 29/09/2026 2:44:29 pm
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
	uint16_t counter = 0;

	init_display();
	timer0_init();
	sei();

	while (1)
	{
		seperate_and_load_characters(counter, 4);   // 4 means no decimal point
		_delay_ms(400);

		counter++;
		if (counter > 9999)
		counter = 0;
	}
}

