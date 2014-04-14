
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
unsigned char appLedCount = 1;
unsigned char FireFlag = 0;
	unsigned char var;
	unsigned char dtmfVal;
	unsigned char callPickTrials = 0;

void appTimerStart(void)
{
	timerClearCount(HW_TIMER1);
	timerBegin(__CLK__FREQUENCY,2000,HW_TIMER1);
	timerEnableInterrupt(HW_TIMER1);
	timerStart(HW_TIMER1);
}

void AppTimerStop(void)
{
	timerStop(HW_TIMER1);
	timerDisableInterrupt(HW_TIMER1);
}

unsigned char appTimerGetTimeOut(void)
{
	if(timerCount1 >= __APP_TIMER_TIMEOUT)
	return 0;
	else
	return 1;
}

void initSystem(void)
{
	Serialbegin(__CLK__FREQUENCY,__BAUD_RATE___);
	setSerialinterrupt();
	motorBegin();
	ledBegin();
	sensorsBegin();
	gsmPortinit();
	/*if(gsmStatus() == 0)
	{
		gsmReset();
		_delay_milli(500);
	    gsmPowerUp();
		_delay_milli(500);
	}*/
	appTimerStart();
}

void bootTest(void)
{
	unsigned char var;
	
	// Echo Off
	
	// Detect Test
	test1:
	var = gsmDetectModem();
	if(var == 0)
	{
	//ledBlinkOne(1,50,20);
	ledBlinkDouble(1,2,50,10);
	}
	else
	{
		/*while (1)
		{
					ledBlinkOne(1,1000,5);
		}*/
		//Serialflush();
		ledOn(1,1);
		ledOn(2,1);
		goto test1;
	}
		ledNo(0);
		
		_delay_milli(3000);
	
	test2:
	// Register Test
	var = gsmGetRegStatus();
	if(var == 0)
	{
		//ledBlinkOne(2,50,20);
		ledBlinkDouble(1,3,50,10);
	}
	else
	{
		/*while (1)
		{
			ledBlinkOne(2,1000,5);
		}*/
				ledOn(1,1);
				ledOn(3,1);
				goto test2;
	}
	ledNo(0);
	
	// Enable Dtmf
	test3:
	var = gsmEnableDtmf();
		if(var == 0)
		{
			//ledBlinkOne(3,50,20);
			ledBlinkDouble(2,4,50,10);
		}
		else
		{
			/*while (1)
			{
				ledBlinkOne(3,1000,5);
			}*/
					ledOn(2,1);
					ledOn(4,1);
					goto test3;
		}
	
}

void app(void)
{


	// Check for new Call
	if(CallFlag == 0)
	{
	if(gsmDetectCall() == 0)
	{
		timerCount1 = 0; 
		AppTimerStop();
		back:
		var = gsmConnectCall();
		CallFlag = 1;
			ledNo(15);	
		if(var == 0)
		{
			    CallFlag = 1;
						ledNo(15);	
		}
		else
		{
							callPickTrials++;
							CallFlag = 0;
							if(callPickTrials < CALL_PICK_TRIAL_MAX)
							{
													goto back;
													Serialflush();		
							}
							else
							{
								callPickTrials = 0;
								//app();
								return;
							}

		}
	}
		 	// Toggle LED's
		 	if(appTimerGetTimeOut() == 0)
		 	{
			 	timerCount1 = 0;
			 	ledNo(appLedCount);
				appLedCount = appLedCount*2;
			 	if(appLedCount == 16)
			 appLedCount = 1;
	        }
	}
		
// If Call is connected
 /*else if(CallFlag == 1)
 {*/
	  // Read Dtmf		 
  dtmfVal = gsmReadDtmf();
  if(dtmfVal < 15)
  {
	  //ledNo(dtmfVal);
	  switch(dtmfVal)
	  {
		  case DTMF_FW : 
		                 ledOn(1,1);
						 ledOn(2,1);
						 ledOn(3,0);
						 ledOn(4,0);
						 motorForward();
		                 break;
		  case DTMF_BW : 
		                 ledOn(1,0);
		                 ledOn(2,0);
		                 ledOn(3,1);
		                 ledOn(4,1);
						 motorBackward();
		                 break;
		  case DTMF_LT : 
		                 ledOn(1,1);
		                 ledOn(2,0);
		                 ledOn(3,0);
		                 ledOn(4,0);
						 motorLeft();
		                 break;
          case DTMF_RT :
		                ledOn(1,0);
		                ledOn(2,1);
		                ledOn(3,0);
		                ledOn(4,0);
						 motorRight();
		                 break;
		  case DTMF_ST : 
		                ledOn(1,1);
		                ledOn(2,1);
		                ledOn(3,1);
		                ledOn(4,1);
						motorStop();
	                   break;
	  }
  }
  
  // Check Disconnect
  var = gsmCallDisStatus();
  if(var == 0)
  {
	                
	  			    motorStop();
					Serialflush();
                    CallFlag = 0;
	  				ledBlinkOne(1,50,2);
	  				ledBlinkOne(2,50,2);
	  				ledBlinkOne(3,50,2);
	  				ledBlinkOne(4,50,2);
	  				ledNo(0);
					timerCount1 = 0;
					appTimerStart();
  }
  
    #ifdef SENSOR_ENABLE
  if(sensorsDetectObstacle() == 0)
    {
		#ifdef AUTO_STOP
	    motorStop();
		#endif
	  /*  ledOn(1,0);
	    ledOn(2,0);
	    ledOn(3,1);
	    ledOn(4,1);*/
    }
	
	  else if(sensorsDetectFire() == 0)
	  {
		  				  #ifdef SMS_ENABLE
		  var = gsmSetSmsFormat(1);
		  if(var == 0)
		  {
			//  ledBlinkOne(3,10,100);
			/*  var = gsmSendSms(MOB_NO,"Fire Detected");
			  ledBlinkOne(3,10,20);*/
			gsmSendSmsTemp(1);
		  }
		  #endif
		  
	  }
	  
	      else if(sensorsDetectSmoke() == 0)
	      {
			  				  #ifdef SMS_ENABLE
		      var = gsmSetSmsFormat(1);
		      if(var == 0)
		      {
			     // ledBlinkOne(4,10,100);
     	    	  gsmSendSmsTemp(2);
				
		      }
			  #endif
 }
 #endif
// }
// }


	//  ledBlinkOne(1,20,10);
	  //var = gsmSetSmsFormat(1);
	/*  if(var == 0)
	  {
		  ledBlinkOne(1,100,20);*/
		  //gsmSendSms(MOB_NO,"Obstacle Detected");
		  // gsmSendSmsTemp(0);
	  //}
/*	 if(flag == 0 && CallFlag == 1)
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
	}*/
  
  }


