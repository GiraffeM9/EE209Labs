/*
 * adc.c
 *
 * Created: 27/08/2026 5:30:46 pm
 *  Author: Mayita
 */ 

#include "common.h"
#include "adc.h"

void adc_init(){
	ADMUX = 0b01000010;
	ADCSRA = 0b00101100;
	ADCSRB = 0b01000001;
}

uint16_t adc_read(uint8_t channel){
	
}