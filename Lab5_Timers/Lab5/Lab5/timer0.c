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

void timer0_init(){
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS02);
	OCR0A = 0b01001101; // 77 for 10ms
}

uint8_t timer0_check_clear_compare(){
	if( TIFR0 & (1 << OCF0A) ){ 
		TIFR0 |= (1 << OCF0A);
		//Note: in datasheet this is done by writing 1 to the compare flag
		return 1;
	}
	return 0;
}