
#ifndef __app_h__
#define __app_h__

#include <avr/io.h>

// Clock Frequency (Internal 8 Mhz)
#define __CLK__FREQUENCY 8000000

// Gsm Modem baud rate
#define __BAUD_RATE___ 9600

#define _test_delay 5000
#define _TEST_INTERVAL 7000
#define SEN_DEB_DELAY 3000

#define IR_THRESHOLD   300 // 200 is for more distance
#define FIRE_THRESHOLD 300

// Gsm Modem timeout delay in microseconds
#define __GSM_MODEM_TIMEOUT_US    1000

#define __GSM_MODEM_TIMEOUT_COUNT 100 // ( So totale timeout : (__GSM_MODEM_TIMEOUT_US * __GSM_MODEM_TIMEOUT_COUNT)us, or __GSM_MODEM_TIMEOUT_COUNT ms (If __GSM_MODEM_TIMEOUT_US is 1000)



// Sensors

#define IR_CH  4
#define FIR_CH 5

// IR Sensor (2 (Arduino) - IR Sensor (DOUT))
/*
#define IR_DIR    DDRC
#define IR_PIN    PINC
#define IR_PORT   PORTC
#define IR_BIT    1 << 4

// A5 (Arduino) -> DOUT (Fire Sensor)
#define FIR_DIR   DDRC
#define FIR_PIN   PINC
#define FIR_PORT  PORTC
#define FIR_BIT   1 << 5
*/

// A4 (Arduino) -> DOUT (Smoke Sensor)
#define SMK_DIR   DDRD
#define SMK_PIN   PIND
#define SMK_PORT  PORTD
#define SMK_BIT   1 << 2

#define MODEM_PWR_KEY_DIR  DDRB
#define MODEM_PWR_KEY_PORT DDRB
#define MODEM_PWR_KEY_BIT  1 << 4

#define MODEM_RST_KEY_DIR  DDRB
#define MODEM_RST_KEY_PORT DDRB
#define MODEM_RST_KEY_BIT  1 << 5



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


extern void motorLeft(void);
extern void motorRight(void);
extern void motorBackward(void);
extern void motorForward(void);
extern void motorStop(void);
extern void led_indicate_numbers(unsigned char);
extern void led_indicate(int,int);
extern void initSystem(void);
extern void setPortDir(void);
extern void setPullup(void);
extern unsigned int readIR(void);
extern unsigned int readFire(void);
extern void blinkLED1(void);
extern void blinkLED2(void);
extern void modemReset(void);
extern void modemPowerUp(void);

#endif



