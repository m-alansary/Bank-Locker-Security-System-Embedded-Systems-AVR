/*
 * i2c.h
 *
 *  Created on: Oct 20, 2019
 *      Author: Ansary
 */

#ifndef I2C
#define I2

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

#define TW_START         0x08
#define TW_REP_START     0x10
#define TW_MT_SLA_W_ACK  0x18
#define TW_MT_SLA_R_ACK  0x40
#define TW_MT_DATA_ACK   0x28
#define TW_MR_DATA_ACK   0x50
#define TW_MR_DATA_NACK  0x58

void TWI_init();

void TWI_Start();

void TWI_Stop();

void TWI_write(uint8 data);

uint8 TWI_Read_With_ACK();

uint8 TWI_Read_With_NACK();

uint8 TWI_Get_Status();



#endif /* I2C */




