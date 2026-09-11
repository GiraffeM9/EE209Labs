/*
 * uart.c
 *
 * Created: 1/09/2026 10:13:28 pm
 *  Author: Mayit
 */ 
#include <avr/io.h>
#include "uart.h"

void usart_init(uint16_t ubrr)
{
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	UCSR0B |= (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void usart_transmit(uint8_t data)
{
	while ( !(UCSR0A & (1 << UDRE0)) )
	{
		;
	}
	UDR0 = data;
}

void usart_send_string(const char *str){
	// loops through string (via pointer) to the end of the string 
	while (*str) {
		usart_transmit((uint8_t)*str++);
	}
}
