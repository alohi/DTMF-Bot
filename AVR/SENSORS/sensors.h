
#ifndef __sensors_h__
#define __sensors_h__

#include "adc.h"

#define IR_CH  4
#define FIR_CH 5

#define AVG_SAMPLE_RATE 50

extern void         sensorsBegin(void);
extern unsigned int sensorsReadIR(void);
extern unsigned int sensorsReadFire(void);

#endif