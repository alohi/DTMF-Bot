
#ifndef __app_h__
#define __app_h__


// All Enable Pin of motor ( 3 (Arduino) -> EN (L293D)
#define EN_DIR    DDRD
#define EN_PORT   PORTD
#define EN_BIT    1 << 3

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

// 8 (Arduino) -> MA1 of L293D - 2
#define MC1_DIR   DDRB
#define MC1_PORT  PORTB
#define MC1_BIT   1 << 0

// 9 (Arduino) -> MA2 of L293D - 2
#define MC2_DIR   DDRB
#define MC2_PORT  PORTB
#define MC2_BIT   1 << 1

// 10 (Arduino) -> MB1 of L293D - 2
#define MD1_DIR   DDRB
#define MD1_PORT  PORTB
#define MD1_BIT   1 << 2

// 10 (Arduino) -> MB2 of L293D - 2
#define MD2_DIR   DDRB
#define MD2_PORT  PORTB
#define MD2_BIT   1 << 3

// Sensors

// IR Sensor (2 (Arduino) - IR Sensor (DOUT))
#define IR_DIR    DDRD
#define IR_PIN    PIND
#define IR_BIT    1 << 2

// A4 (Arduino) -> DOUT (Smoke Sensor)
#define SMK_DIR   DDRC
#define SMK_PIN   PINC
#define SMK_BIT   1 << 4

// A5 (Arduino) -> DOUT (Fire Sensor)
#define FIR_DIR   DDRC
#define FIR_PIN   PINC
#define FIR_BIT   1 << 5

// Indications (LED1,LED2,LED3,LED4) Connection is below

/*//////////////////////////////////////////////////////////////
Arduino                  LED
-------                  ---
A0            -          LED1
A1            -          LED2
A2            -          LED3
A3            -          LED4
//////////////////////////////////////////////////////////////*/

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

// DTMF Key Definition
#define DTMF_FW    2
#define DTMF_BW    8
#define DTMF_ST    5
#define DTMF_LT    4
#define DTMF_RT    6
#define DTMF_SP    7
#define DTMF_SM    9




#endif



