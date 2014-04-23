
#include "test.h"
#include "gsm.h"
#include "avr_delay.h"
#include "sensors.h"
#include "motor.h"
#include "led.h"
#include "app.h"
#include "timer.h"

void testledOnOff(void)
{
unsigned char i;
for(i=1;i<=4;i++)
{
_delay_milli(LED_ON_OFF_DELAY);
ledOn(i,1);
}
for(i=1;i<=4;i++)
{
_delay_milli(LED_ON_OFF_DELAY);
ledOn(i,0);
}
}

void testledNo(void)
{
	unsigned int i;
for(i=0;i<=15;i++)
{
ledNo(i);
_delay_milli(LED_ON_OFF_DELAY);
}
}

void testgsmSimul(void)
{
unsigned char var;

// Set Echo Off 
var = gsmEchoOff();
if(var == 0)
{
Serialprint("Echo OFF: Success\n");
}
else if(var == 1)
{
Serialprint("Echo OFF: String Error\n");
}
else if(var == 2)
{
Serialprint("Echo OFF: Timeout Error\n");
}
else if(var == 3)
{
Serialprint("Echo OFF: Unknown Error\n");
}

// Detect Modem
var = gsmDetectModem();
if(var == 0)
{
Serialprint("Detect Modem: Success\n");
}
else if(var == 1)
{
Serialprint("Detect Modem: String Error\n");
}
else if(var == 2)
{
Serialprint("Detect Modem: Timeout Error\n");
}
else if(var == 3)
{
Serialprint("Detect Modem: Unknown Error\n");
}

// Get Register Status
var = gsmGetRegStatus();
if(var == 0)
{
Serialprint("Reg Status: Success\n");
}
else if(var == 1)
{
Serialprint("Reg Status: String Error\n");
}
else if(var == 2)
{
Serialprint("Reg Status: Timeout Error\n");
}

// Enable Dtmf
var = gsmEnableDtmf();
if(var == 0)
{
Serialprint("DTMF Set: Success\n");
}
else if(var == 1)
{
Serialprint("DTMF Set: String Error\n");
}
else if(var == 2)
{
Serialprint("DTMF Set: Timeout Error\n");
}
else if(var == 3)
{
Serialprint("DTMF Set: Unknown Error\n");
}

var = gsmSignalStrength();
if(var == 0)
{
Serialprint("Network Test: Success\n");
}
else if(var == 1)
{
Serialprint("Network Test: String Error\n");
}
else if(var == 2)
{
Serialprint("Network Test: Timeout Error\n");
}
else if(var == 3)
{
Serialprint("Network Test: Unknown Error\n");
}
else if(var == 3)
{
Serialprint("Network Test: No Signal\n");
}


while(1)
{
// If Call is detected ('RING')
if(gsmDetectCall() == 0)
{
// Connect Call ('ATA')
var = gsmConnectCall();
if(var == 0)
{
Serialprint("Connect Voice Call: Success\n");
}
else if(var == 1)
{
Serialprint("Connect Voice Call: String Error\n");
}
else if(var == 2)
{
Serialprint("Connect Voice Call: Timeout Error\n");
}
else if(var == 3)
{
Serialprint("Connect Voice Call: Unknown Error\n");
}
}

// Read DTMF Value
var = gsmReadDtmf();
if(var < 15)
{
Serialprint("DTMF:-");
SerialIntWrite(var,10);
Serialwrite('\n');
}

// If Call is disconncted ('NO CARRIER')
if(gsmCallDisStatus() == 0)
{
Serialprint("Voice Call Disconnected\n");
}
}
}

void testSesnors(void)
{
	if(sensorsDetectObstacle() == 0)
	{
		Serialprint("Obstacle Detected\n");
	}
	
		if(sensorsDetectFire() == 0)
		{
			Serialprint("Fire Detected\n");
		}
		
				if(sensorsDetectSmoke() == 0)
				{
					Serialprint("Smoke Detected\n");
				}
}

void testReadSensors(void)
{
unsigned int val1,val2,val3;
val1 = sensorsReadIR();
val2 = sensorsReadFire();
val3 = sensorsDetectSmoke();
SerialIntWrite(val1,10);
Serialwrite(9);
SerialIntWrite(val2,10);
Serialwrite(9);
SerialIntWrite(val3,10);
Serialwrite('\n');
}

void testMotor(void)
{
char c;
Serialflush();
Serialprint("Motor Test\n");
while(1)
{
if(uartNewLineFlag == 1)
{
	Serialprint("LF received\n");
c = uartReadBuffer[0];
Serialflush();
switch(c)
{
case 'a': motorForward();
Serialprint("Motor FW\n");
          break;
case 'b': motorBackward();
Serialprint("Motor BW\n");
          break;
case 'c': motorLeft();
Serialprint("Motor Left\n");
          break;
case 'd': motorRight();
Serialprint("Motor Right\n");
          break;
case 'e': motorStop();
Serialprint("Motor Stop\n");
          break;		  
}
}
}
}


void testTimer(void)
{
	unsigned int count = 0;
	signed int ms = 0;
	signed int ss = 0;
	timerClearCount(HW_TIMER2);
	timerBegin(__CLK__FREQUENCY,__GSM_MODEM_TIMEOUT_US,HW_TIMER2);
	timerEnableInterrupt(HW_TIMER2);
	timerStart(HW_TIMER2);
	while(1)
	{
		if(timerCount2 >= 1000)
		{
			timerCount2 = 0;
			ms++;
		/*	if(ms == 1000)
			{
				ms = 0;
				ss++;
				SerialIntWrite(ss,10);
			    Serialwrite(LF);
			}*/
						SerialIntWrite(ms,10);
						Serialwrite(LF);
		}
	}
}

void uartISRTest(void)
{
	while(1)
	{
		if(uartNewLineFlag == 1)
		{
			Serialprint((char*)uartReadBuffer);
			Serialflush();
		}
	}
}