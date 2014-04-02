
#ifndef __gsm_h__
#define __gsm_h__

#include "uart.h"
#include "timer.h"

#define GSM_REGISTER_STATUS_TRIAL_MAX 10

// Gsm Initiation
#define gsmBegin(unsigned long osc,unsigned long baud) Serialbegin(osc,baud)

extern void          gsmTimerStart(void);
extern void          gsmTimerStop(void);
extern unsigned char gsmGetTimeout(void);

extern unsigned char gsmDetectModem(void);
extern unsigned char gsmEchoOff(void);
extern unsigned char gsmEnableDtmf(void);
extern unsigned char gsmGetRegStatus(void);

extern unsigned char gsmDetectCall(void);
extern unsigned char gsmCallDisStatus(void);
extern unsigned char gsmConnectCall(void);
extern unsigned char gsmReadDtmf(void);


#endif