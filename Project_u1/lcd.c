/*
 * lcd.c
 *
 *  Created on: Oct 5, 2019
 *      Author: Ansary
 */
#include "lcd.h"
#include "stdlib.h"

void LCD_init(){
	LCD_CTRL_DDR |= 1 << RW | 1 << EN | 1 << RS;
	#if DATA_BITS_MODE == 8
		LCD_DATA_DDR = 0xff;
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);
	#elif DATA_BITS_MODE == 4
		#ifdef UPPER_PORT_PINS
			LCD_DATA_DDR |= 0xf0;
		#else
			LCD_DATA_DDR |= 0x0f;
		#endif
		LCD_sendCommand(FOUR_BITS_DATA_MODE);
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
	#endif

	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);

}

void LCD_sendCommand(uint8 command){
	CLEAR_BIT(LCD_CTRL_PORT, RS);
	CLEAR_BIT(LCD_CTRL_PORT, RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, EN);
	_delay_ms(1);
	#if DATA_BITS_MODE == 8
		LCD_DATA_PORT = command;
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT, EN);
		_delay_ms(1);
	#elif DATA_BITS_MODE == 4
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | (command & 0xf0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xf0) | ((command & 0xf0) >> 4);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT, EN);
		_delay_ms(1);
		SET_BIT(LCD_CTRL_PORT, EN);
		_delay_ms(1);
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | ((command & 0x0f) << 4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xf0) | (command & 0x0f);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT, EN);
		_delay_ms(1);
	#endif
}

void LCD_displayCharacter(uint8 character){
	SET_BIT(LCD_CTRL_PORT, RS);
	CLEAR_BIT(LCD_CTRL_PORT, RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, EN);
	_delay_ms(1);
	#if DATA_BITS_MODE == 8
		LCD_DATA_PORT = character;
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT, EN);
		_delay_ms(1);
	#elif DATA_BITS_MODE == 4
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | (character & 0xf0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xf0) | ((character & 0xf0) >> 4);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT, EN);
		_delay_ms(1);
		SET_BIT(LCD_CTRL_PORT, EN);
		_delay_ms(1);
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0f) | ((character & 0x0f) << 4);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xf0) | (character & 0x0f);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CTRL_PORT, EN);
		_delay_ms(1);
	#endif
}

void LCD_displayString(uint8 *str){
	while(*str != '\0'){
		LCD_displayCharacter(*str);
		str++;
	}
}

void LCD_goToRowColumn(uint8 row, uint8 col){
	uint8 address;
	switch(row){
		case 0:
			address = col;
			break;
		case 1:
			address = 0x40 + col;
			break;
		case 2:
			address = 0x10 + col;
			break;
		case 3:
			address = 0x50 + col;
			break;
	}

	LCD_sendCommand(SET_CURSOR_LOCATION | address);
}

void LCD_displayStringRowColumn(uint8 *str, uint8 row, uint8 col){
	LCD_goToRowColumn(row, col);
	LCD_displayString(str);
}

void LCD_clearScreen(){
	LCD_sendCommand(CLEAR_COMMAND);
}

void LCD_integerToString(uint32 data){
	char buff[16]; /* String to hold the ACII result */
	itoa(data,buff,10); /* 10 for decimal */
	LCD_displayString(buff);

	/*switch(data){
		case 0:
			LCD_displayCharacter('0');
			break;
		case 1:
			LCD_displayCharacter('1');
			break;
		case 2:
			LCD_displayCharacter('2');
			break;
		case 3:
			LCD_displayCharacter('3');
			break;
		case 4:
			LCD_displayCharacter('4');
			break;
		case 5:
			LCD_displayCharacter('5');
			break;
		case 6:
			LCD_displayCharacter('6');
			break;
		case 7:
			LCD_displayCharacter('7');
			break;
		case 8:
			LCD_displayCharacter('8');
			break;
		case 9:
			LCD_displayCharacter('9');
			break;
	}*/
}







