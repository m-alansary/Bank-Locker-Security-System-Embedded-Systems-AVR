/*
 * micro_config.h
 *
 *  Created on: Oct 4, 2019
 *      Author: Ansary
 */

#ifndef MICRO_CONFIG
#define MICRO_CONFIG

#ifndef F_CPU
#define F_CPU 1000000UL //1MHz Clock frequency
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif /* MICRO_CONFIG */
