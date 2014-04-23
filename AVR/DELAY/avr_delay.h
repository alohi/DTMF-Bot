
#ifndef __avr_delay_h__
#define __avr_delay_h__

#define F_CPU 16000000UL
#include <util/delay.h>

extern void delay_us(unsigned int);
extern void delay_ms(unsigned int);

#define _delay_milli(val) delay_ms(val)
#define _delay_micro(val) delay_us(val)

#endif