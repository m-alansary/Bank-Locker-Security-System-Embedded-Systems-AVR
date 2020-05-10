/*
 * external_eeprom.c
 *
 *  Created on: Oct 23, 2019
 *      Author: Ansary
 */

#include "external_eeprom.h"
#include "i2c.h"

#define PW_ADDRR 350

void EEPROM_init(void){
	TWI_init();
}


uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data){
	TWI_Start();
	if(TWI_Get_Status() != TW_START)
		return ERROR;

	TWI_write((uint8) (0xA0 | ((u16addr & 0x0700) >> 7)));
	if(TWI_Get_Status() != TW_MT_SLA_W_ACK)
			return ERROR;

	TWI_write((uint8) u16addr);
	if(TWI_Get_Status() != TW_MT_DATA_ACK)
			return ERROR;

	TWI_write(u8data);
	if(TWI_Get_Status() != TW_MT_DATA_ACK)
			return ERROR;

	TWI_Stop();

	return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data){
	TWI_Start();
	if(TWI_Get_Status() != TW_START)
		return ERROR;

	TWI_write((uint8) (0xA0 | ((u16addr & 0x0700) >> 7)));
	if(TWI_Get_Status() != TW_MT_SLA_W_ACK)
		return ERROR;

	TWI_write((uint8) u16addr);
	if(TWI_Get_Status() != TW_MT_DATA_ACK)
		return ERROR;

	TWI_Start();
	if(TWI_Get_Status() != TW_REP_START)
		return ERROR;

	TWI_write((uint8) (0xA0 | ((u16addr & 0x0700) >> 7) | 1));
	if(TWI_Get_Status() != TW_MT_SLA_R_ACK)
		return ERROR;

	*u8data = TWI_Read_With_NACK();
	if (TWI_Get_Status() != TW_MR_DATA_NACK)
		return ERROR;

	TWI_Stop();
	return SUCCESS;
}


void EEPROM_writeString(uint16 u16addr, uint8 *str){
	uint8 i = 0;
	while(*str != '\0'){
		EEPROM_writeByte(u16addr + i, *str);
		_delay_ms(10);
		str++;
		i++;
	}
	EEPROM_writeByte(u16addr + i, *str);
	_delay_ms(10);
}


void EEPROM_readString(uint16 u16addr, uint8 *str){
	uint8 i = 0;
	EEPROM_readByte(u16addr + i, &str[i]);
	_delay_ms(10);
	while(str[i] != '\0'){
		i++;
		EEPROM_readByte(u16addr + i, &str[i]);
		_delay_ms(10);
	}
}




