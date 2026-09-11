/*
 * uart.h
 *
 * Created: 1/09/2026 10:15:35 pm
 *  Author: Mayit
 */ 


#ifndef UART_H_
#define UART_H_

void usart_init(uint16_t ubrr);
void usart_transmit(uint8_t data);
void usart_send_string(const char *str);

#endif /* UART_H_ */