/*
 * timer0.c
 *
 * Created: 17/09/2026 1:10:06 pm
 *  Author: Mayit
 */ 

#include "timer0.h"
#include "led.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint16_t timer0_ms_count = 0;

ISR(TIMER0_COMPA_vect) {
	led_toggle();
}

void timer0_init(){
	TCCR0A |= (1 << WGM01); // CTC mode
	TCCR0B |= (1 << CS02); // Prescaler = 256
	OCR0A = 77; // (77+1)*256/2MHz = 9.984ms
	TIMSK0 = (1 << OCIE0A); // Timer/Counter0 compare match A interrupt is enabled
}

