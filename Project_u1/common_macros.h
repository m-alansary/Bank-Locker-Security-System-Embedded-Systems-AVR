/*
 * common_macros.h
 *
 *  Created on: Oct 4, 2019
 *      Author: Ansary
 */

#ifndef COMMON_MACROS
#define COMMON_MACROS

/* Sets BIT in certain REGISTER */
#define SET_BIT(REG, BIT) (REG |= (1 << BIT))

/* Clears BIT in certain REGISTER */
#define CLEAR_BIT(REG, BIT) (REG &= ~(1 << BIT))

/* Toggles BIT in certain REGISTER */
#define TOGGLE_BIT(REG, BIT) (REG ^= (1 << BIT))

/* Rotate REGISTER Bits with the value num right */
#define ROR(REG, num) (REG = (REG | (1 >> num)) | (REG | (1 << (8 - num))))

/* Rotate REGISTER Bits with the value num left */
#define ROL(REG, num) (REG = (REG | (1 << num)) | (REG | (1 >> (8 - num))))

/* Checks if a certain bit is set */
#define BIT_IS_SET(REG, BIT) (REG & (1 << BIT))

/* Checks if a certain bit is cleared */
#define BIT_IS_CLEAR(REG, BIT) (!(REG & (1 << BIT)))

#endif /* COMMON_MACROS */



