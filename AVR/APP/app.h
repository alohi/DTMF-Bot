
#ifndef __app_h__
#define __app_h__

#include <avr/io.h>

// Clock Frequency (Internal 8 Mhz)
#define __CLK__FREQUENCY 8000000UL

// Gsm Modem baud rate
#define __BAUD_RATE___ 9600

#define  CALL_PICK_TRIAL_MAX 10
#define __APP_TIMER_TIMEOUT  20

#define SENSOR_ENABLE
#define SMS_ENABLE
//#define AUTO_STOP


#define MOB_NO "9342833087"

// DTMF Key Definition
#define DTMF_FW    2
#define DTMF_BW    8
#define DTMF_ST    5
#define DTMF_LT    4
#define DTMF_RT    6
#define DTMF_SP    7
#define DTMF_SM    9

extern void initSystem(void);
extern void bootTest(void);
extern void app(void);


#endif



