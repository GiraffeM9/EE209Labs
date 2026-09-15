/*
 * lab4.c
 *
 * Created: 27/08/2026 5:29:55 pm
 * Author : Mayita
 */ 

#include "adc.h"
#include "uart.h"
#include "common.h"
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
	// Initialisation
	adc_init(); 
	usart_init(12);
	
	uint16_t adc0_readings[40];
	uint16_t adc1_readings[40];
	char line[16];
	
	for (int i = 0; i < 40; i++) {
		adc0_readings[i] = adc_read(0); // ADC0
		adc1_readings[i] = adc_read(1); // ADC1
	}
	
	
	for (int i = 0; i < 40; i++) {
		sprintf(line, "%d , %d\r\n", adc_convert_mv(adc0_readings[i]), adc_convert_mv(adc1_readings[i])); // Creates string: "{adc0 value} , {adc1 value}"
		usart_send_string(line);
	}
	
    while (1) 
    {
    }
}

