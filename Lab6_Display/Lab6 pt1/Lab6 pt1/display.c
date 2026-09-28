/*
 * display.c
 *
 * Created: 29/09/2026 12:18:05 pm
 *  Author: Mayit
 */ 

#include "display.h"
#include <avr/io.h>

static const uint8_t seg_pattern[10] = {
	0x3F, 
	0x06, 
	0x5B, 
	0x4F, 
	0x66, 
	0x6D, 
	0x7D, 
	0x07, 
	0x7F, 
	0x6F
};

static volatile uint8_t counter = 0;
static volatile uint8_t next_digit = 0;   // 0 = Ds1 (tens), 1 = Ds2 (units)

static void write_segments(uint8_t pattern){
	PORTB &= ~(1 << PORTB4);                 // clear g
	PORTC &= 0b11000000;                     // clear a-f
	
	PORTB |= ((pattern >> 6) & 1) << PORTB4; // g
	PORTC |= (pattern & 0x3F);               // a-f
}

void display_init(void){
	DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB4);
	DDRC |= 0x3F;
	PORTB |= (1 << PORTB0) | (1 << PORTB1);  // both digits off
}

void display_increment(void){
	counter++;
	if (counter > 99) counter = 0;
}

void display_reset(void){
	counter = 0;
}

void display_refresh(void){
	uint8_t pattern;

	if (next_digit == 0){
		pattern = seg_pattern[counter / 10]; // tens
	}
	else{
		pattern = seg_pattern[counter % 10]; // ones
	}
	PORTB |= (1 << PORTB0) | (1 << PORTB1);  // 3. disable both
	write_segments(pattern);                 // 4. set segments


	if (next_digit == 0){					// 5. enable chosen digit
		PORTB &= ~(1 << PORTB0);            
	}
	else{
		PORTB &= ~(1 << PORTB1);
	}


	next_digit ^= 1;
}