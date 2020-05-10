/*
 * main2.c
 *
 *  Created on: Oct 23, 2019
 *      Author: Ansary
 */


#include "uart.h"
#include "communication_macros.h"
#include "external_eeprom.h"
#include "lcd.h"
#include <string.h>

#define PW_ADDRR 0x0250

void buzzer(void);
void openDoor(void);
void setPW(void);
void checkPW(void);

int main(void){
	uint8 byte;
	UART_init();
	/*LCD_init();
	LCD_displayString("123456");*/
	EEPROM_init();

	DDRA |= (1 << PA0) | (1 << PA1);
	DDRB |= (1 << PB5) | (1 << PB6);

	while(1){
		byte = UART_receiveByte();
		switch(byte){
			case THIEF:
				buzzer();
				break;
			case OPEN_DOOR:
				openDoor();
				break;
			case SET_PW:
				setPW();
				break;
			case CHECK_PW:
				checkPW();
				break;
		}
	}
}


void buzzer(void){
	uint32 counter = 0;
	while(counter != 20){
		SET_BIT(PORTB, PB5);
		_delay_ms(500);
		CLEAR_BIT(PORTB, PB5);
		_delay_ms(500);
		counter++;
	}
}

void openDoor(void){
	SET_BIT(PORTA, PA0);
	SET_BIT(PORTB, PB6);
	CLEAR_BIT(PORTA, PA1);
	_delay_ms(1000);
	CLEAR_BIT(PORTA, PA0);
	SET_BIT(PORTA, PA1);
	_delay_ms(1000);
	CLEAR_BIT(PORTA, PA0);
	CLEAR_BIT(PORTA, PA1);
	CLEAR_BIT(PORTB, PB6);
}

void setPW(void){
	uint8 password1[17], password2[17];
	UART_receiveString(password1);
	while(UART_receiveByte() != SET_PW);
	UART_receiveString(password2);
	if(strcmp(password1, password2) == 0){
		UART_sendByte(DONE);
		EEPROM_writeString(PW_ADDRR, password1);
	}
	else{
		UART_sendByte(NOT_DONE);
	}
}

void checkPW(void){
	uint8 password1[17], password2[17];
	UART_receiveString(password1);
	/*LCD_clearScreen();
	LCD_displayString("Here!!");*/
	EEPROM_readString(PW_ADDRR, password2);
	/*LCD_clearScreen();
	LCD_displayString(password1);
	LCD_goToRowColumn(1, 0);
	LCD_displayString(password2);*/
	if(strcmp(password1, password2) == 0){
		UART_sendByte(DONE);
	}
	else{
		UART_sendByte(NOT_DONE);
	}
}








