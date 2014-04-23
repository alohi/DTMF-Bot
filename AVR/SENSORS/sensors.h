
#ifndef __sensors_h__
#define __sensors_h__

#include "adc.h"

#define IR_CH  4
#define FIR_CH 5


#define SMK_DIR         DDRD
#define SMK_PIN         PIND
#define SMK_PORT        PORTD
#define SMK_BIT         1 << 2


#define AVG_SAMPLE_RATE 10

#define IR_THRESHOLD    300 // 200 is for more distance
#define FIRE_THRESHOLD  300

extern void          sensorsBegin(void);
extern unsigned int  sensorsReadIR(void);
extern unsigned int  sensorsReadFire(void);
extern unsigned char sensorsDetectObstacle(void);
extern unsigned char sensorsDetectFire(void);
extern unsigned char sensorsDetectSmoke(void);

#endif