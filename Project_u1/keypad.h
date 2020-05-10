/*
 * keypad.h
 *
 *  Created on: Oct 4, 2019
 *      Author: Ansary
 */

#ifndef KEYPAD
#define KEYPAD

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/* The number of keypad columns */
#define N_COL 4

/* The number of keypad rows */
#define N_ROW 4

/* Keypad Port Configurations */
#define KEYPAD_PORT PORTA
#define KEYPAD_PIN  PINA
#define KEYPAD_DDR 	DDRA


uint8 Keypad_getPressedKey();

#endif /* KEYPAD */
