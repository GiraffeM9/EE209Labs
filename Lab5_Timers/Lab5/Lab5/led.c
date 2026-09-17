/*
 * led.c
 *
 * Created: 17/09/2026 1:10:26 pm
 *  Author: Mayit
 */ 

#include "led.h"
#include <avr/io.h>

void led_toggle(){
	PORTB ^= (1 << 5); //PB5
}