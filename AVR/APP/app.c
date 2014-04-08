
#include "app.h"
#include "timer.h"
#include "motor.h"
#include "sensors.h"
#include "adc.h"
#include "gsm.h"
#include "avr_delay.h"
#include "led.h"

unsigned char flag = 0;
unsigned char CallFlag = 0;

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
		
		_delay_milli(200);
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
			CallFlag = 1;
				ledBlinkOne(1,50,2);
				ledBlinkOne(2,50,2);
				ledBlinkOne(3,50,2);
				ledBlinkOne(4,50,2);
				ledNo(0);	
		}
		else
		{
							ledBlinkOne(1,500,2);
							ledBlinkOne(2,500,2);
							ledBlinkOne(3,500,2);
							ledBlinkOne(4,500,2);
							ledNo(0);
		}
	}
		
 // Read Dtmf
  dtmfVal = gsmReadDtmf();
  if(dtmfVal < 15)
  {
	  ledNo(dtmfVal);
	  switch(dtmfVal)
	  {
		  case DTMF_FW : motorForward();
		                 break;
		  case DTMF_BW : motorBackward();
		                 break;
		  case DTMF_LT : motorLeft();
		                 break;
          case DTMF_RT : motorRight();
		                 break;
		  case DTMF_ST : motorStop();
		                 break;
	  }
  }
  
  // Check Disconnect
  var = gsmCallDisStatus();
  if(var == 0)
  {
	  CallFlag = 0;
	  			    motorStop();
	  				ledBlinkOne(1,50,2);
	  				ledBlinkOne(2,50,2);
	  				ledBlinkOne(3,50,2);
	  				ledBlinkOne(4,50,2);
	  				ledNo(0);
  }
  
  if(sensorsDetectObstacle() == 0)
  {
	  ledBlinkOne(1,20,10);
	  /*var = gsmSetSmsFormat(1);
	  if(var == 0)
	  {
		  ledBlinkOne(1,100,20);
		  //gsmSendSms(MOB_NO,"Obstacle Detected");
		  // gsmSendSmsTemp(0);
	  }*/
	 if(flag == 0 && CallFlag == 1)
	 {
      flag = 1;
	  motorLeft();
	 }
	 else if(flag == 1 && CallFlag == 1)
	 {
		 flag = 0;
		 motorRight();
	 }
  }
  else if(sensorsDetectFire() == 0)
  {
	  ledBlinkOne(2,20,10);
	  var = gsmSetSmsFormat(1);
	  if(var == 0)
	  {
		  ledBlinkOne(2,100,20);
		  	  //gsmSendSms(MOB_NO,"Fire Detected");
//				 gsmSendSmsTemp(1);
	  }
  }
    else if(sensorsDetectSmoke() == 0)
    {
		ledBlinkOne(3,20,10);
	    	  var = gsmSetSmsFormat(1);
	    	  if(var == 0)
	    	  {
		    	  ledBlinkOne(3,100,20);
	//	    	  gsmSendSmsTemp(2);
    }
	}
  
  }


