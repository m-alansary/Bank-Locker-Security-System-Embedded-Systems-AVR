/*
 * lcd.h
 *
 *  Created on: Oct 5, 2019
 *      Author: Ansary
 */

#ifndef LCD
#define LCD

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

#define LCD_CTRL_DDR 	DDRD
#define LCD_CTRL_PORT 	PORTD

#define LCD_DATA_DDR	DDRA
#define LCD_DATA_PORT	PORTA

#define RS PD4
#define RW PD5
#define EN PD6

#define DATA_BITS_MODE 4
#define UPPER_PORT_PINS

#define CLEAR_COMMAND 				0x01
#define FOUR_BITS_DATA_MODE 		0x02
#define TWO_LINE_LCD_Four_BIT_MODE 	0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 					0x0C
#define CURSOR_ON 					0x0E
#define SET_CURSOR_LOCATION 		0x80

void LCD_init();
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 character);
void LCD_displayString(uint8 *str);
void LCD_goToRowColumn(uint8 row, uint8 col);
void LCD_displayStringRowColumn(uint8 *str, uint8 row, uint8 col);
void LCD_clearScreen();
void LCD_integerToString(uint32 data);

#endif /* LCD */
