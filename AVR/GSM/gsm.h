
#ifndef __gsm_h__
#define __gsm_h__

#include "uart.h"
#include "timer.h"

extern unsigned char getDtmf(void);
extern unsigned char enableDtmf(void);
extern unsigned char getDtmf(void);
extern unsigned char connectCall(void);
extern unsigned char detectCall(void);
extern unsigned char detectModem(void);


#endif