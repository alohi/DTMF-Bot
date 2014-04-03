
#include "adc.h"
#include "app.h"
#include "avr_delay.h"
#include "gsm.h"
#include "led.h"
#include "motor.h"
#include "sensors.h"
#include "timer.h"
#include "uart.h"
#include "test.h"


int main(void)
{
initSystem();
_delay_milli(3000);
bootTest();
Serialflush();
while(1)
{
app();	
//testReadSensors();
//testSesnors();
}

/*while (1)
{
	testMotor();
}*/
}