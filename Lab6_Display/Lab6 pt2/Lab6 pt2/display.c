/*
 * display.c
 *
 * Created: 29/09/2026 2:45:13 pm
 *  Author: Mayit
 */ 
#include "display.h"
#include <avr/io.h>

// Segment patterns for 0 to 9, dp is the MSB and a is the LSB
const uint8_t seg_pattern[10] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

// Index 0 is the leftmost digit (Ds1) and index 3 is the rightmost (Ds4)
static volatile uint8_t disp_characters[4] = {0, 0, 0, 0};

static volatile uint8_t disp_position = 0;

void init_display(void){
	DDRD |= 1 << DDD4 | 1 << DDD5 | 1 << DDD6 | 1 << DDD7;   // Ds1 to Ds4
	DDRC |= 1 << DDC3 | 1 << DDC4 | 1 << DDC5;               // CP, DS, ST
}

// decimal_pos 0 to 3 puts the point on that digit, anything higher means none
void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos){
	disp_characters[3] = seg_pattern[number % 10];
	disp_characters[2] = seg_pattern[(number / 10) % 10];
	disp_characters[1] = seg_pattern[(number / 100) % 10];
	disp_characters[0] = seg_pattern[(number / 1000) % 10];

	if (decimal_pos <= 3){
		disp_characters[decimal_pos] |= 0x80;
	}
}

void send_next_character_to_display(void){
	PORTD |= 0xF0;                                   // Disable Ds1 to Ds4
	PORTC &= ~(1 << PORTC3 | 1 << PORTC5);           // SH_CP and SH_ST low

	for (int8_t i = 7; i >= 0; i--){
		PORTC &= ~(1 << PORTC4);                     // Clear DS
		PORTC |= ((disp_characters[disp_position] >> i) & 1) << PORTC4;
		PORTC |= (1 << PORTC3);                      // Clock high
		PORTC &= ~(1 << PORTC3);                     // Clock low
	}

	PORTC |= (1 << PORTC5);                          // Latch
	PORTD &= ~(1 << (disp_position + 4));            // Enable the current digit

	if (disp_position == 3){
		disp_position = 0;
	}
	else{
		disp_position++;
	}
}