/*
 * uart.h
 *
 * Created: 11/08/2026 2:44:30 pm
 *  Author: Mayit
 */ 

#ifndef UART_H
#define UART_H

#include <stdint.h>

void usart_init(uint16_t ubrr);
void usart_transmit(uint8_t data);
void usart_transmit_number(uint16_t number);

#endif