
#ifndef __gsm_h__
#define __gsm_h__

#include "uart.h"
#include "timer.h"

#define GSM_REGISTER_STATUS_TRIAL_MAX 100

extern unsigned char getDtmf(void);
extern unsigned char enableDtmf(void);
extern unsigned char getDtmf(void);
extern unsigned char connectCall(void);
extern unsigned char detectCall(void);
extern unsigned char detectModem(void);
extern void          gsmBegin(unsigned long,unsigned long);
extern unsigned char Callstatus(void);
extern unsigned char echoOff(void);
extern unsigned char getRegisterStatus(void);

#endif