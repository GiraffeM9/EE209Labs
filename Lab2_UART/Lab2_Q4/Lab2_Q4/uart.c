/*
 * uart.c
 *
 * Created: 11/08/2026 2:52:08 pm
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

void usart_transmit_number(uint16_t number)
{
	uint8_t digits[5];
	uint8_t digit_count = 0;

	if (number == 0)
	{
		usart_transmit(48);
		return;
	}

	while (number > 0)
	{
		digits[digit_count] = number % 10;
		number = number / 10;
		digit_count++;
	}

	for (int8_t i = digit_count - 1; i >= 0; i--)
	{
		usart_transmit(digits[i] + 48);
	}
}