
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
	unsigned char c;
initSystem();
/*while(1)
testTimer();*/
DDRD |= 1 << 4;
DDRD |= 1 << 5;
DDRD |= 1 << 6;
DDRD |= 1 << 7;
DDRD |= (1 << 3);
DDRB &= ~(1 << 4);
DDRB |= 1 << 0;
DDRB |= 1 << 1;
DDRB |= 1 << 2;
DDRB |= 1 << 3;

_delay_milli(3000);
//testTimer();
/*testgsmSimul();*/
//testMotor();
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
/*DDRD |= 1 << 4;
DDRD |= 1 << 5;
DDRD |= 1 << 6;
DDRD |= 1 << 7;
while(1)
{

PORTD |= 1 << 4;
PORTD &= ~(1 << 5);
PORTD |= 1 << 6;
PORTD &= ~(1 << 7);	
_delay_milli(500);

PORTD |= 1 << 5;
PORTD &= ~(1 << 4);
PORTD |= 1 << 7;
PORTD &= ~(1 << 6);
_delay_milli(500);
}*/

}