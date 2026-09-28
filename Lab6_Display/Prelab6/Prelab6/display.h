/*
 * Display.h
 *
 * Created: 25/09/2026 7:59:00 pm
 *  Author: Mayit
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <stdint.h>

void display_init();
void displayNumber(uint8_t number);
void writeToDisplay(uint8_t displayInput);


#endif /* DISPLAY_H_ */