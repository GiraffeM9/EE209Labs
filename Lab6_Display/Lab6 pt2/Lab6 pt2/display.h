/*
 * display.h
 *
 * Created: 29/09/2026 2:45:31 pm
 *  Author: Mayit
 */ 

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void init_display(void);
void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos);
void send_next_character_to_display(void);

#endif