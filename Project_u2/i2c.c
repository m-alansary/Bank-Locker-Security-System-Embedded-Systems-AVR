/*
 * i2c.c
 *
 *  Created on: Oct 20, 2019
 *      Author: Ansary
 */

#include "i2c.h"

#define SCL 400000


void TWI_init(){
	/*
	 * Prescaler = 1
	 * CLK Frequency must be 8 MHz to get TWBR +ve value
	 * SCL Frequency = 100 kbit/sec
	 */
	TWBR = 0x02; /* ((F_CPU / SCL - 16) / 2) */
	TWSR = 0x00; /* Prescaler = 1 */

	TWAR = 0b00000010;
	/*
	 * TWEN = 1 to enable the I2C
	 */
	TWCR = (1 << TWEN);


}



void TWI_Start(){
	TWCR = (1 << TWEN) | (1 << TWSTA);

	/*while(TWSR >> 3 != TW_START);*/
	 while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_Stop(){
	TWCR = (1 << TWEN) | (1 << TWSTO);

	/* while(BIT_IS_CLEAR(TWCR,TWINT)); */
}


void TWI_write(uint8 data){
	TWDR = data;

	TWCR = (1 << TWEN) | (1 << TWINT);

	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_Read_With_ACK(){
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);

	while(BIT_IS_CLEAR(TWCR,TWINT));

	return TWDR;
}

uint8 TWI_Read_With_NACK(){
	TWCR = (1 << TWEN) | (1 << TWINT);

	while(BIT_IS_CLEAR(TWCR,TWINT));

	return TWDR;
}

uint8 TWI_Get_Status(){
	return TWSR & 0xf8;
}







