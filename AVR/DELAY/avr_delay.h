
#ifndef __avr_delay_h__
#define __avr_delay_h__

#define F_CPU 8000000UL
#include <util/delay.h>

#define _delay_milli(val) _delay_ms(val)
#define _delay_micro(val) _delay_us(val)

#endif