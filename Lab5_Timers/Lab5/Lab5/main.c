/*
 * Lab5.c
 *
 * Created: 17/09/2026 1:09:15 pm
 * Author : Mayit
 */ 

#define F_CPU 2000000UL

#include "timer0.h"
#include "timer1.h"
#include "int0.h"
#include "usart.h"

#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void) {
	DDRB = 0xFF;
	DDRC = 0x00;
	DDRD = 0x00;

	timer0_init();
	timer1_init();
	int0_init();
	usart_init(12);
	sei();

	uint16_t period;
	char line[16];

	while (1) {
		if (int0_get_period(&period)) {
			float freq = int0_ticks_to_freq(period);
			dtostrf(freq, 6, 2, line);
			usart_send_string(line);
			usart_send_string(" Hz\r\n");
		}
	}
}
