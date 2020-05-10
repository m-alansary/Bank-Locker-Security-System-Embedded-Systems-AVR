/*
 * keypad.c
 *
 *  Created on: Oct 4, 2019
 *      Author: Ansary
 */
#include "keypad.h"


#if N_COL == 3

	static uint8 Keypad_4x3_adjustSwitchNumber(uint8 buttonNumber);

#elif N_COL == 4

	static uint8 Keypad_4x4_adjustSwitchNumber(uint8 buttonNumber);

#endif

uint8 Keypad_getPressedKey(){
	uint8 col, row;
	while(1){
		for(col = 0; col < N_COL; col++){
			KEYPAD_DDR = (0b00010000 << col);

			KEYPAD_PORT = ~(0b00010000 << col);

			for(row = 0; row < N_ROW; row++){
				if(BIT_IS_CLEAR(KEYPAD_PIN, row)){
					#if N_COL == 3
						return Keypad_4x3_adjustSwitchNumber((col + 1) + N_COL * (row));
					#elif N_COL == 4
						return Keypad_4x4_adjustSwitchNumber((col + 1) + N_COL * (row));
					#endif
				}
			}

		}
	}
}

#if N_COL == 3

	static uint8 Keypad_4x3_adjustSwitchNumber(uint8 buttonNumber){
		switch(buttonNumber){
			case 10:
				return '*';
			case 11:
				return 0;
			case 12:
				return '#';
			default:
				return buttonNumber;
		}
	}

#elif N_COL == 4
	static uint8 Keypad_4x4_adjustSwitchNumber(uint8 buttonNumber){
		switch(buttonNumber){
			case 1:
				return 7;
			case 2:
				return 8;
			case 3:
				return 9;
			case 4:
				return '%';
			case 5:
				return 4;
			case 6:
				return 5;
			case 7:
				return 6;
			case 8:
				return '*';
			case 9:
				return 1;
			case 10:
				return 2;
			case 11:
				return 3;
			case 12:
				return '-';
			case 13:
				return 13; /* ASCII code of Enter */
			case 14:
				return 0;
			case 15:
				return '=';
			case 16:
				return '+';
			default:
				return buttonNumber;
		}
	}
#endif
