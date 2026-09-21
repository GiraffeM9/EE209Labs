/*
 * timer1.h
 *
 * Created: 17/09/2026 5:07:57 pm
 *  Author: Mayit
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

#include <stdint.h>

void timer1_init();

void timer1_reset();

uint16_t timer1_read();

#endif