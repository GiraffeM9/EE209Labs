/*
 * display.c
 *
 * Created: 25/09/2026 7:59:25 pm
 *  Author: Mayit
 */ 
#define F_CPU 2000000UL

#include "display.h"
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

void display_init(){
	PORTB |= (1 << PORTB0);
	PORTB &= ~(1 << PORTB1);
}

const uint8_t seg_pattern[10] = {
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

void displayNumber(uint8_t number){
	writeToDisplay(seg_pattern[number]);
}

void writeToDisplay(uint8_t displayInput){
	/* Input should be laid out as follow:
	*	Dn, Sg, Sf, Se, Sd, Sc, Sb, Sa
	*	where Dn is the display number (0 = Display 1, 1 = Display 2)
	*   & Sa-g is the respective segment
	*/
	
	// Clear g segment only
	PORTB &= ~(1 << PORTB4);

	// Clear a-f
	PORTC &= 0b11000000;

	 // g
	 PORTB |= ((displayInput >> 6) & 1) << PORTB4;

	 // a-f
	 PORTC |= (displayInput & 0x3F);
}