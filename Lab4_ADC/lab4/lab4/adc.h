/*
 * adc.h
 *
 * Created: 27/08/2026 5:31:11 pm
 *  Author: Mayita
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h> // for uint8_t, etc
void adc_init();
uint16_t adc_read(uint8_t channel);


#endif /* ADC_H_ */