/*
 * int0.h
 *
 * Created: 17/09/2026 4:22:25 pm
 *  Author: Mayit
 */ 


#ifndef INT0_H_
#define INT0_H_

#include <stdint.h>
#include <stdbool.h>

void int0_init();
bool int0_get_period(uint16_t *period);
float int0_ticks_to_freq(uint16_t period_ticks);

#endif