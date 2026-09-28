/*
 * timer.c
 *
 * Created: 29/09/2026 12:18:46 pm
 *  Author: Mayit
 */ 

#include "timer.h"
#include "display.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// 10ms tick: 2MHz / 256 = 7812.5Hz, 78 counts is about 10ms
void timer0_init(void){
	TCCR0A = (1 << WGM01);      // CTC mode
	TCCR0B = (1 << CS02);       // prescaler 256
	OCR0A = 77;
	TIMSK0 = (1 << OCIE0A);     // compare match A interrupt
}

ISR(TIMER0_COMPA_vect){
	display_refresh();
}