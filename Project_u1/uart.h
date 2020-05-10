/*
 * uart.h
 *
 *  Created on: Oct 13, 2019
 *      Author: Ansary
 */

#ifndef UART
#define UART

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

#define USART_BAUDRATE 9600

void UART_init(void);

void UART_sendByte(const uint8 data);

uint8 UART_receiveByte(void);

void UART_sendString(uint8 *str);

void UART_recieveString(uint8 *str);

#endif /* UART */






