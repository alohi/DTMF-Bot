
#include "app.h"
#include "timer.h"
#include "motor.h"
#include "sensors.h"
#include "adc.h"
#include "gsm.h"
#include "avr_delay.h"

void initSystem(void)
{
	gsmBegin(__CLK__FREQUENCY,__BAUD_RATE___);
	motorBegin();
	ledBegin();
	sensorsBegin();
}






