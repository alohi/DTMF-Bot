
#include "app.h"
#include "timer.h"
#include "motor.h"
#include "sensors.h"
#include "adc.h"
#include "gsm.h"
#include "avr_delay.h"
#include "led.h"
#include "avr/wdt.h"

unsigned char flag = 0;
unsigned char CallFlag = 0;
unsigned char appLedCount = 1;
unsigned char var;
unsigned char dtmfVal;
unsigned char callPickTrials = 0;
unsigned char FireWarn = 0;
unsigned char SmokeWarn = 0;
unsigned char ObstFlag = 1;

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
	wdt_disable();
	Serialbegin(__CLK__FREQUENCY,__BAUD_RATE___);
	setSerialinterrupt();
	motorBegin();
	ledBegin();
	sensorsBegin();
	#ifndef FAST_MODE
	appTimerStart();
	#endif
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
	#ifndef FAST_MODE_START_UP
	ledBlinkDouble(1,2,50,10);
	#endif
	}
	else
	{
		#ifndef FAST_MODE_START_UP
		ledOn(1,1);
		ledOn(2,1);
		#endif
		goto test1;
	}
	#ifndef FAST_MODE_START_UP
		ledNo(0);
		
		_delay_milli(3000);
   #endif
	
	test2:
	// Register Test
	var = gsmGetRegStatus();
	if(var == 0)
	{
		//ledBlinkOne(2,50,20);
		#ifndef FAST_MODE_START_UP
		ledBlinkDouble(1,3,50,10);
		#endif
	}
	else
	{
		#ifndef FAST_MODE_START_UP
				ledOn(1,1);
				ledOn(3,1);
				#endif
				goto test2;
	}
	#ifndef FAST_MODE_START_UP
	ledNo(0);
	#endif
	
	// Enable Dtmf
	test3:
	var = gsmEnableDtmf();
		if(var == 0)
		{
			//ledBlinkOne(3,50,20);
			#ifndef FAST_MODE_START_UP
			ledBlinkDouble(2,4,50,10);
			#endif
		}
		else
		{
			#ifndef FAST_MODE_START_UP
					ledOn(2,1);
					ledOn(4,1);
					#endif
					goto test3;
		}
	
	#ifdef STARTUP_SMS
	var = gsmSetSmsFormat(SMS_TXT_MODE);
	if(var == 0)
	{
		ledBlinkDouble(1,2,100,10);
	}
	else
	ledBlinkDouble(3,4,100,50);
	ledNo(0);
	
	var = gsmSendSms(MOB_NO,MSG_START);
	if(var == SEND_SMS_STRING_ERROR)
	ledNo(1);
	else if(var == SEND_SMS_UNKNWN_ERROR)
	ledNo(2);
		else if(var == SEND_SMS_TIMEOUT_ERROR)
		ledNo(3);
			else if(var == SEND_SMS_TIMEOUT_ERROR_WHILE_SENDING)
			ledNo(4);
				else if(var == SEND_SMS_STRING_ERROR_WHILE_SENDING)
				ledNo(5);
								else if(var == SEND_SMS_ERROR_WHILE_READING_LOC)
								ledNo(6);
								else
								ledBlinkDouble(3,4,50,30);
								_delay_milli(100);
								ledNo(0);
								Serialflush();
	#endif
}

ISR(WDT_vect)
{
	asm volatile ("  jmp 0");
}

void app(void)
{
	// Check for new Call
	if(CallFlag == 0)
	{
	if(gsmDetectCall() == 0)
	{
		#ifndef FAST_MODE
		timerCount1 = 0; 
		AppTimerStop();
		#endif
		back:
		var = gsmConnectCall();
		CallFlag = 1;
		#ifndef FAST_MODE
			ledNo(15);	
			#endif
		if(var == 0)
		{
			    CallFlag = 1;
				#ifndef FAST_MODE
						ledNo(0);
						#endif	
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
			 #ifndef FAST_MODE
		 	if(appTimerGetTimeOut() == 0)
		 	{
			 	timerCount1 = 0;
			 	ledNo(appLedCount);
				appLedCount = appLedCount*2;
			 	if(appLedCount == 16)
			 appLedCount = 1;
	        }
			#endif
	}
		
// If Call is connected
 else
 {
	  // Read Dtmf		 
  dtmfVal = gsmReadDtmf();
  if(dtmfVal < 15)
  {
	  switch(dtmfVal)
	  {
		  case DTMF_FW : 
		  #ifndef FAST_MODE
		                 ledOn(1,1);
						 ledOn(2,1);
						 ledOn(3,0);
						 ledOn(4,0); 
		#endif
						 motorForward();
		                 break;
		  case DTMF_BW :
		   #ifndef FAST_MODE
		                 ledOn(1,0);
		                 ledOn(2,0);
		                 ledOn(3,1);
		                 ledOn(4,1);
						 #endif
						 motorBackward();
		                 break;
		  case DTMF_LT :
		   #ifndef FAST_MODE
		                 ledOn(1,1);
		                 ledOn(2,0);
		                 ledOn(3,0);
		                 ledOn(4,0);
						 #endif
						 motorLeft(); 
		                 break;
          case DTMF_RT :
		  #ifndef FAST_MODE
		                ledOn(1,0);
		                ledOn(2,1);
		                ledOn(3,0);
		                ledOn(4,0);
						 #endif
						 motorRight();
		                 break;
		  case DTMF_ST :
		   #ifndef FAST_MODE
		                ledOn(1,1);
		                ledOn(2,1);
		                ledOn(3,1);
		                ledOn(4,1); 
						#endif
						motorStop();
	                   break;
		 case DTMF_DO :
					   #ifndef FAST_MODE
					   ledBlinkDouble(1,2,50,10);
					   #endif
					   ObstFlag = 0;
					   break;
		case DTMF_EO :
		 #ifndef FAST_MODE
					   ledBlinkDouble(3,4,50,10);
					   #endif
					   ObstFlag = 1;
	  }
  }
  
  // Check Disconnect
  var = gsmCallDisStatus();
  if(var == 0)
  {
	                
	  			    motorStop();
					Serialflush();
                    CallFlag = 0;
					#ifndef FAST_MODE
	  				ledBlinkOne(1,50,2);
	  				ledBlinkOne(2,50,2);
	  				ledBlinkOne(3,50,2);
	  				ledBlinkOne(4,50,2);
	  				ledNo(0);
					timerCount1 = 0;
					appTimerStart();
					#endif
					FireWarn = 0;
					SmokeWarn = 0;
					ObstFlag = 0;
					/*wdt_enable(WDTO_1S);
					wdt_reset();
					sei();*/
  }
  
    #ifdef SENSOR_ENABLE
  if(sensorsDetectObstacle() == 0 && ObstFlag == 1)
    {
		#ifdef AUTO_STOP
	    motorStop();
		ledNo(15);
		#endif
    }
	
	#ifdef FIRE_ENABLE
	  else if(sensorsDetectFire() == 0 && FireWarn < 20)
	  {
		  FireWarn++;
		  #ifdef SMS_ENABLE
		  if(FireWarn == 20) 
		  {
		  var = gsmSetSmsFormat(1);
		  if(var == 0)
		  {
			gsmSendSmsTemp(1);
		  }
		  }
		  #endif

		  
	  }
	  
#endif	  
	  
	      else if(sensorsDetectSmoke() == 0 && SmokeWarn == 0)
	      {
			  SmokeWarn = 1;
			  #ifdef SMS_ENABLE
		      var = gsmSetSmsFormat(1);
		      if(var == 0)
		      {
     	    	  gsmSendSmsTemp(2);
		      }
			  #endif
 }
 #endif
 }
  }


