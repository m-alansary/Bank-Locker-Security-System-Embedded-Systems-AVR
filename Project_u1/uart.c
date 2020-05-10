/*
 * UART.c
 *
 *  Created on: Oct 13, 2019
 *      Author: Ansary
 */

#include "uart.h"

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)


void UART_init(void){
	/*
	 * U2X = 1 for double transmission speed
	 */
	UCSRA = (1 << U2X);
	/*
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART TX Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 */
	UCSRB = (1 << RXEN) | (1 << TXEN);
	/*
	 * URSEL = 1 : Access the UCSRC register not the UBRRH
	 * UMSEL = 0 : Asynchronous Operation
	 * UPM   = 0 : Parity mode is off
	 * USBS  = 0 : one stop bit
	 * UCPOL = x : clock used for Synchronous only
	 * UCSZ  = 3 : 8 bit mode
	 */
	UCSRC = (1 << URSEL) |  (1 << UCSZ1) | (1 << UCSZ0);
	/*
	 * Sets MSB of the UBRR to 0 to write
	 * writs BAUD_PRESCALE in the UBRR for baud rate of 9600
	 */
	UBRRH = 103 >> 8;
	UBRRL = 103;
}

void UART_sendByte(const uint8 data){
	/*
	while(BIT_IS_CLEAR(UCSRA, TXC));
	SET_BIT(UCSRA, TXC);
	UDR = data;
	*/

	while(BIT_IS_CLEAR(UCSRA,UDRE));
	UDR = data;

}

uint8 UART_receiveByte(void){
	while(BIT_IS_CLEAR(UCSRA, RXC));
	return UDR;
}

void UART_sendString(uint8 *str){
	while(*str != '\0'){
		UART_sendByte(*str);
		str++;
	}
}

void UART_recieveString(uint8 *str){
	*str = UART_receiveByte();
	while(*str != '#'){
		str++;
		*str = UART_receiveByte();
	}
	*str = '\0';
}




