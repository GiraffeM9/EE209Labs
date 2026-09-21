/*
 * timer1.c
 *
 * Created: 17/09/2026 5:07:48 pm
 *  Author: Mayit
 */ 
#include "timer1.h"
#include <avr/io.h>

void timer1_init() {
	TCCR1A = 0;              // normal mode
	TCCR1B = (1 << CS12);    // prescaler 256
	TCNT1 = 0;
}

void timer1_reset() {
	TCNT1 = 0;
}

uint16_t timer1_read() {
	return TCNT1;
}