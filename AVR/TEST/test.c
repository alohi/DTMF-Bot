
#include "test.h"
#include "gsm.h"
#include "avr_delay.h"

void testledOnOff(void)
{
unsigned char i;
for(i=0;i<=3;i++)
{
_delay_milli(LED_ON_OFF_DELAY);
ledOn(i,1);
}
for(i=0;i<=3;i++)
{
_delay_milli(LED_ON_OFF_DELAY);
ledOn(i,0);
}
}

void testledNo(void)
{
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

void testReadSensors(void)
{
unsigned int val1,val2;
val1 = sensorsReadIR();
val2 = sensorsReadFire();
SerialIntWrite(val1);
Serialwrite(9);
SerialIntWrite(val2);
Serialwrite('\n');
}

void testMotor(void)
{
char c;
Serialflush();
while(1)
{
if(uartNewLineFlag == 1)
{
c = uartReadBuffer[0];
Serialflush();
switch(c)
{
case 'a': motorForward();
          break;
case 'b': motorBackward();
          break;
case 'c': motorLeft();
          break;
case 'd': motorRight();
          break;
case 'e': motorStop();
          break;		  
}
}
}
}