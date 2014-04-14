
#ifndef __motor_h__
#define __motor_h__

#include "avr_delay.h"
#include <avr/io.h>

// Turning Delay
#define MOTOR_TURN_DELAY 1000

// All Enable Pin of motor ( 3 (Arduino) -> EN (L293D)
/*#define EN_DIR    DDRD
#define EN_PORT   PORTD
#define EN_BIT    1 << 3*/

// 4 (Arduino) -> MA1 of L293D - 1
#define MA1_DIR   DDRD
#define MA1_PORT  PORTD
#define MA1_BIT   1 << 4

// 5 (Arduino) -> MA2 of L293D - 1
#define MA2_DIR   DDRD
#define MA2_PORT  PORTD
#define MA2_BIT   1 << 5

// 6 (Arduino) -> MB1 of L293D - 1
#define MB1_DIR   DDRD
#define MB1_PORT  PORTD
#define MB1_BIT   1 << 6

// 7 (Arduino) -> MB2 of L293D - 1
#define MB2_DIR   DDRD
#define MB2_PORT  PORTD
#define MB2_BIT   1 << 7

// 8 (Arduino) -> MC1 of L293D - 2
#define MC1_DIR   DDRB
#define MC1_PORT  PORTB
#define MC1_BIT   1 << 0

// 9 (Arduino) -> MC2 of L293D - 2
#define MC2_DIR   DDRB
#define MC2_PORT  PORTB
#define MC2_BIT   1 << 1

// 10 (Arduino) -> MD1 of L293D - 2
#define MD1_DIR   DDRB
#define MD1_PORT  PORTB
#define MD1_BIT   1 << 2

// 10 (Arduino) -> MD2 of L293D - 2
#define MD2_DIR   DDRB
#define MD2_PORT  PORTB
#define MD2_BIT   1 << 3

extern void motorBegin(void);
extern void motorStop(void);
extern void motorForward(void);
extern void motorBackward(void);
extern void motorLeft(void);
extern void motorRight(void);

#endif