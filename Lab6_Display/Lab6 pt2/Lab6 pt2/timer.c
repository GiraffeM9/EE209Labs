/*
 * timer.c
 *
 * Created: 29/09/2026 2:45:22 pm
 *  Author: Mayit
 */ 

#include "timer.h"
#include "display.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// 10ms tick, 2MHz / 256 = 7812.5Hz and 78 counts is about 10ms
void timer0_init(void){
	TCCR0A = (1 << WGM01);      // CTC mode
	TCCR0B = (1 << CS02);       // Prescaler 256
	OCR0A = 38;                 // 50 Hz on each display: OCR0A = f_cpu/(256 * 200Hz) - 1 
	TIMSK0 = (1 << OCIE0A);     // Compare match A interrupt
}

ISR(TIMER0_COMPA_vect){
	send_next_character_to_display();
}