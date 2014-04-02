
#include "app.h"
#include "timer.h"
#include "motor.h"
#include "sensors.h"
#include "adc.h"
#include "gsm.h"
#include "avr_delay.h"
#include "led.h"

void initSystem(void)
{
	Serialbegin(__CLK__FREQUENCY,__BAUD_RATE___);
	setSerialinterrupt();
	motorBegin();
	ledBegin();
	sensorsBegin();
	gsmPortinit();
	if(gsmStatus() == 1)
	{
		gsmReset();
		_delay_milli(500);
	    gsmPowerUp();
		_delay_milli(500);
	}
}

void bootTest(void)
{
	unsigned char var;
	
	// Echo Off
	
	// Detect Test
	var = gsmDetectModem();
	if(var == 0)
	{
	ledBlinkOne(1,50,20);
	}
	else
	{
		while (1)
		{
					ledBlinkOne(1,1000,5);
		}
	}
		ledNo(0);
		
	// Register Test
	var = gsmGetRegStatus();
	if(var == 0)
	{
		ledBlinkOne(2,50,20);
	}
	else
	{
		while (1)
		{
			ledBlinkOne(2,1000,5);
		}
	}
	ledNo(0);
	
	// Enable Dtmf
	var = gsmEnableDtmf();
		if(var == 0)
		{
			ledBlinkOne(3,50,20);
		}
		else
		{
			while (1)
			{
				ledBlinkOne(3,1000,5);
			}
		}
		ledNo(0);
	
}

void app(void)
{
	unsigned char var;
	unsigned char dtmfVal;
	// Check for new Call
	if(gsmDetectCall() == 0)
	{
		var = gsmConnectCall();
		if(var == 0)
		{
				ledBlinkOne(1,50,10);
				ledBlinkOne(2,50,10);
				ledBlinkOne(3,50,10);
				ledBlinkOne(4,50,10);
				ledNo(0);	
		}
		else
		{
							ledBlinkOne(1,500,10);
							ledBlinkOne(2,500,10);
							ledBlinkOne(3,500,10);
							ledBlinkOne(4,500,10);
							ledNo(0);
		}
	}
		
 // Read Dtmf
  dtmfVal = gsmReadDtmf();
  if(dtmfVal < 15)
  {
	  ledNo(dtmfVal);
  }
  
  // Check Disconnect
  var = gsmCallDisStatus();
  if(var == 0)
  {
	  				ledBlinkOne(1,50,10);
	  				ledBlinkOne(2,50,10);
	  				ledBlinkOne(3,50,10);
	  				ledBlinkOne(4,50,10);
	  				ledNo(0);
  }
}


