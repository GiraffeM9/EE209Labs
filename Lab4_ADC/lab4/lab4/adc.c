/*
 * adc.c
 *
 * Created: 27/08/2026 5:30:46 pm
 *  Author: Mayita
 */ 

#include "common.h"
#include "adc.h"

void adc_init(){
	ADMUX |= (1 << REFS0);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2);
}

uint16_t adc_read(uint8_t channel){
	ADMUX &= 0xF0; // Clear channel selection (mux bits)
	ADMUX |= channel; // Set the channel to convert
	ADCSRA |= (1 << ADIF);   // clear any stale flag
	ADCSRA |= (1 << ADSC); // Starting an ADC conversion
	
	while ((ADCSRA & (1 << ADIF)) == 0) { // ADIF bit is checked to see if it is 0
		; // If ADIF bit is not 1, wait until it becomes 1 (polls)
	}
	
	uint8_t low = ADCL;   // Important: Must read this first, "freezes" the ADCL/ADCH pair
	uint8_t high = ADCH;  // Reading this "releases" the register pair, allowing for the next conversion
	
	return (high << 8) | low; // Returns ADC value
}

uint16_t adc_convert_mv(uint16_t adc_value){
	uint32_t mv = ((uint32_t)adc_value * 5000)/1024; // Converts ADC value to original voltage value in millivolts
	return mv;
}