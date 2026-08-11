/*
 * Lab2_Q4.c
 *
 * Created: 6/08/2026 5:20:03 pm
 * Author : Mayita Denenga
 */ 


#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

#define F_CPU 2000000UL

bool check_prime(uint16_t chk_no);
bool check_prime(uint16_t chk_no){
	if (chk_no < 2){
		return false;
	}
	for(uint16_t i=2; i < chk_no; i++){
		if ((chk_no % i) == 0){
			return false;
		}
	}
	return true;
}

int main(void)
{
	usart_init(12);

	uint16_t count = 0;
	uint16_t myPrimes[62];

	for (uint16_t num=2; num<=300; num++){
		if (check_prime(num)){
			myPrimes[count] = num;
			count++;
		}
	}

	while (1)
	{
		for (uint16_t i = 0; i < count; i++)
		{
			usart_transmit_number(myPrimes[i]);
			usart_transmit(',');
			usart_transmit(' ');
			_delay_ms(500);
		}
		
	}
}