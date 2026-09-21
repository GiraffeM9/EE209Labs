/*
 * int0.c
 *
 * Created: 17/09/2026 4:22:14 pm
 *  Author: Mayit
 */ 
#include "int0.h"
#include "timer0.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 2000000UL
#define PRESCALER 256

static volatile uint16_t last_count = 0;
static volatile uint8_t  new_period_ready = 0;

void int0_init() {
	EICRA |= (1 << ISC00);
	EICRA &= ~(1 << ISC01);  // any logical change on INT0
	EIMSK |= (1 << INT0);
}

ISR(INT0_vect) {
	if (PIND & (1 << PD2)) {
		// rising edge
		last_count = timer1_read();
		timer1_reset();
		new_period_ready = 1;
	}
}

bool int0_get_period(uint16_t *period) {
	bool ready;
	cli();
	ready = new_period_ready;
	if (ready) {
		new_period_ready = 0;
		*period = last_count;
	}
	sei();
	return ready;
}

float int0_ticks_to_freq(uint16_t period_ticks) {
	float period_s = (float)period_ticks * PRESCALER / F_CPU;
	return 1.0f / period_s;
}