/*
 * usart.h
 *
 * Created: 17/09/2026 4:34:16 pm
 *  Author: Mayit
 */ 


#ifndef UART_H_
#define UART_H_

void usart_init(uint16_t ubrr);
void usart_transmit(uint8_t data);
void usart_send_string(const char *str);

#endif /* UART_H_ */