/*
 * Lab5.c
 *
 * Created: 17/09/2026 1:09:15 pm
 * Author : Mayit
 */ 

#define F_CPU 2000000UL
#include "timer0.h"
#include "led.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
	DDRB = (1 << 5); //set PB5 to output

	timer0_init();
	while(1){
		if(timer0_check_clear_compare()) {
			led_toggle();
		}
	}
}
