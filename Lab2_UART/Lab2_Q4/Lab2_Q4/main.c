/*
 * Lab2_Q4.c
 *
 * Created: 6/08/2026 5:20:03 pm
 * Author : Mayita Denenga
 */ 


#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 2000000UL

bool check_prime(uint16_t chk_no);


bool check_prime(uint16_t chk_no){
	for(uint16_t i=2; i < chk_no; i++){
		if ((chk_no % i) == 0){
			return false;
		}
	}
	return true;
}

void usart_init(uint16_t ubrr)
{
	// Set baud rate
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;

	// Enable transmitter
	UCSR0B |= (1 << TXEN0);

	// Set frame format: 8 data bits, 1 stop bit, no parity (8N1)
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void usart_transmit(uint8_t data)
{
	// Wait for empty transmit buffer (UDRE0 flag set = ready)
	while ( !(UCSR0A & (1 << UDRE0)) )
	{
		; // busy-wait / do nothing
	}

	// Put data into buffer, this sends the data
	UDR0 = data;
}

void usart_transmit_number(uint16_t number)
{
	uint8_t digits[5];   // uint16_t max is 65535, so 5 digits is enough
	uint8_t digit_count = 0;
	
	// Handle 0 as a special case (loop below would otherwise skip it)
	if (number == 0)
	{
		usart_transmit(48);
		return;
	}
	
	// Extract digits, least-significant first
	while (number > 0)
	{
		digits[digit_count] = number % 10;
		number = number / 10;
		digit_count++;
	}
	
	// Transmit in reverse (most-significant first)
	for (int8_t i = digit_count - 1; i >= 0; i--)
	{
		usart_transmit(digits[i] + 48);
	}
}


int main(void)
{
	// initialization
	usart_init(12);
	uint16_t number = 345;
	
	uint16_t count = 1;
	uint16_t myPrimes[63] = {1};
	
	for (uint16_t num=2; num<=300; num++){
		if (check_prime(num)){
			myPrimes[count] = num;
			count++;
		}
	}
	
	
    while (1) 
    {
		// sends character "345" every 0.5s
		_delay_ms(500);
		usart_transmit_number(number);
		usart_transmit(32); // space
    }
}

