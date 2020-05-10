/*
 * external_eeprom.h
 *
 *  Created on: Oct 23, 2019
 *      Author: Ansary
 */

#ifndef EXTERNAL_EEPROM
#define EXTERNAL_EEPROM_H_

#include "std_types.h"

#define ERROR 0
#define SUCCESS 1

void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

void EEPROM_writeString(uint16 u16addr,uint8 *str);
void EEPROM_readString(uint16 u16addr,uint8 *str);

#endif /* EXTERNAL_EEPROM */
