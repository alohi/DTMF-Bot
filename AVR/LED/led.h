
#ifndef __led_h__
#define __led_h__

#include <avr/io.h>

#include "avr_delay.h"

#define LED1_DIR  DDRC
#define LED1_PORT PORTC
#define LED1_BIT  1 << 0

#define LED2_DIR  DDRC
#define LED2_PORT PORTC
#define LED2_BIT  1 << 1

#define LED3_DIR  DDRC
#define LED3_PORT PORTC
#define LED3_BIT  1 << 2

#define LED4_DIR  DDRC
#define LED4_PORT PORTC
#define LED4_BIT  1 << 3

extern void ledBegin(void);
extern void ledNo(unsigned char);
extern void ledOn(unsigned char,unsigned char);
extern void ledBlink(unsigned char);
extern void ledRun(unsigned char);

#endif