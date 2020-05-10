/*
 * main1.c
 *
 *  Created on: Oct 23, 2019
 *      Author: Ansary
 */

#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "communication_macros.h"
#include "std_types.h"

#define ENTER_VALUE 13

void readPassword(uint8 *password);
uint8 setPassword(void);
void defaultScreen(void);
uint8 checkPassword(void);
void passwordEnter(void);

uint8 key, counter = 0;

int main(void){
	LCD_init();
	UART_init();

	while(setPassword() != DONE){
		LCD_clearScreen();
		LCD_displayString("PWs don't match");
		_delay_ms(1000);
		LCD_clearScreen();
	}

	LCD_clearScreen();
	LCD_displayString("PW has been set");
	_delay_ms(1000);

	defaultScreen();

	while(1){
		key = Keypad_getPressedKey();
		if(key == '+'){
			_delay_ms(100);
			LCD_clearScreen();
			passwordEnter();
			if(counter != 4){
				LCD_clearScreen();
				LCD_displayString("Welcome!");
				UART_sendByte(OPEN_DOOR);
				_delay_ms(2000);
			}
			counter = 0;
			defaultScreen();
		}
		else if(key == '-'){
			_delay_ms(100);
			LCD_clearScreen();
			passwordEnter();
			_delay_ms(100);
			if(counter != 4){
				LCD_clearScreen();
				while(setPassword() != DONE){
					LCD_clearScreen();
					LCD_displayString("PWs don't match");
					_delay_ms(1000);
					LCD_clearScreen();
				}
				LCD_clearScreen();
				LCD_displayString("PW has been set");
				_delay_ms(1000);
			}
			counter = 0;
			defaultScreen();
		}
	}
}

void readPassword(uint8 *password){
	*password = Keypad_getPressedKey() + 48;
	while(*password != ENTER_VALUE + 48){
		LCD_displayCharacter('*');
		_delay_ms(300);
		password++;
		*password = Keypad_getPressedKey() + 48;
	}
	*password = '#';
	password++;
	*password = '\0';
}

uint8 setPassword(void){
	uint8 password[17];
	uint8 received;

	LCD_displayString("Enter New PW");
	LCD_goToRowColumn(1, 0);
	readPassword(password);
	UART_sendByte(SET_PW);
	UART_sendString(password);

	_delay_ms(100);

	LCD_clearScreen();
	LCD_displayString("Renter your PW");
	LCD_goToRowColumn(1, 0);
	readPassword(password);
	UART_sendByte(SET_PW);
	UART_sendString(password);

	received = UART_receiveByte();
	while(received != DONE && received != NOT_DONE){
		received = UART_receiveByte();
	}
	return received;
}

uint8 checkPassword(void){
	uint8 password[17];
	uint8 received;
	LCD_clearScreen();
	LCD_displayString("Enter Your PW");
	LCD_goToRowColumn(1, 0);
	readPassword(password);
	UART_sendByte(CHECK_PW);
	UART_sendString(password);
	received = UART_receiveByte();
	while(received != DONE && received != NOT_DONE){
		received = UART_receiveByte();
	}
	return received;
}

void defaultScreen(void){
	LCD_clearScreen();
	LCD_displayString("+: Open Door");
	LCD_goToRowColumn(1, 0);
	LCD_displayString("-: Change PW");
}


void passwordEnter(void){
	while(checkPassword() != DONE){
		LCD_clearScreen();
		LCD_displayString("Wrong PW");
		counter++;
		if(counter == 4){
			_delay_ms(100);
			UART_sendByte(THIEF);
			LCD_clearScreen();
			LCD_displayString("ALERT!!!");
			for(int i = 0; i < 20; i++)
				_delay_ms(1000); /* Wait 20 Seconds while Buzzer is Buzzing */
			break;
		}
		_delay_ms(1000);
	}
}











