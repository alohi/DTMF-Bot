

#include "gsm.h"
#include "app.h"
#include "avr_delay.h"

void gsmTimerStart(void)
{
timerClearCount(HW_TIMER0);
timerBegin(__CLK__FREQUENCY,__GSM_MODEM_TIMEOUT_US,HW_TIMER0);
timerEnableInterrupt(HW_TIMER0);
timerStart(HW_TIMER0);
}

void gsmTimerStop(void)
{
timerStop(HW_TIMER0);
timerDisableInterrupt(HW_TIMER0);
}

unsigned char gsmGetTimeout(void)
{
if(timerCount0 >= __GSM_MODEM_TIMEOUT_COUNT)
return 0;
else 
return 1;
}

unsigned char gsmDetectModem(void)
{
Serialflush();
Serialprint("AT\r\n");
gsmTimerStart();
while(gsmGetTimeout() == 1 && uartNewLineCount < 2);
gsmTimerStop();
if(uartNewLineCount >= 2)
{
	if(uartReadBuffer[2] == 'O' && uartReadBuffer[3] == 'K')
	{
		Serialflush();
		return 0;  // Detected
	}
	else
	{
	Serialflush();
	return 1;	   // String Error	
	}

}
else if(timerCount0 >= __GSM_MODEM_TIMEOUT_COUNT)
{
			Serialflush();
			return 2; // Timeout Error
}
else
return 3; // Unknown Error

}

unsigned char gsmEchoOff(void)
{
	Serialflush();
	Serialprint("ATE0\r\n");
    gsmTimerStart();
	while(gsmGetTimeout() == 1 && uartNewLineCount < 2);
    gsmTimerStop();
	if(uartNewLineCount >= 2)
	{
		if(uartReadBuffer[2] == 'O' && uartReadBuffer[3] == 'K')
		{
			Serialflush();
			return 0;  // Detected
		}
		else
		{
			Serialflush();
			return 1;	   // String Error
		}

	}
	else if(timerCount0 >= __GSM_MODEM_TIMEOUT_COUNT)
	{
		Serialflush();
		return 2; // Timeout Error
	}
	else
	return 3; // Unknown Error

}

unsigned char gsmDetectCall(void)
{
if(uartNewLineCount >= 2)
{
if(uartReadBuffer[2] == 'R' && uartReadBuffer[3] == 'I' && uartReadBuffer[4] == 'N' && uartReadBuffer[5] == 'G') // If string is "RING"
{
Serialflush();
return 0;
}
else 
{
	//Serialflush();
	return 1;
}

}
else 
return 2;
}

unsigned char gsmCallDisStatus(void)
{
	if(uartNewLineCount >= 2)
	{
		if(uartReadBuffer[2] == 'N' && uartReadBuffer[3] == 'O' && uartReadBuffer[4] == ' ' && uartReadBuffer[5] == 'C' && uartReadBuffer[6] == 'A' && uartReadBuffer[7] == 'R' && uartReadBuffer[8] == 'R' && uartReadBuffer[9] == 'I' && uartReadBuffer[10] == 'E' && uartReadBuffer[11] == 'R') // If string is "RING"
		{
			Serialflush();
			return 0; // Call disconnected
		}
		else
		{
		//	Serialflush();
					return 1;
		}
	}
	else
	return 2;
}

unsigned char gsmConnectCall(void)
{
	Serialflush();
	Serialprint("ATA\r\n");
    gsmTimerStart();
	while(gsmGetTimeout() == 1 && uartNewLineCount < 2);
    gsmTimerStop();
if(uartNewLineCount >= 2)
{
		if(uartReadBuffer[2] == 'O' && uartReadBuffer[3] == 'K')
		{
			Serialflush();
			return 0;  // Detected
		}
		else
		{
			Serialflush();
			return 1;	   // String Error
		}
}
else if(timerCount0 >= __GSM_MODEM_TIMEOUT_COUNT)
{
	Serialflush();
	return 2;
}
else
return 3;
}

unsigned char gsmEnableDtmf(void)
{
	Serialflush();
	Serialprint("AT+DDET=1\r\n");
	gsmTimerStart();
	while(gsmGetTimeout() == 1 && uartNewLineCount < 2);
    gsmTimerStop();
	if(uartNewLineCount >= 2)
	{
		if(uartReadBuffer[2] == 'O' && uartReadBuffer[3] == 'K')
		{
			Serialflush();
			return 0;  // Detected
		}
		else
		{
			Serialflush();
			return 1;	   // String Error
		}
	}
	else if(timerCount0 >= __GSM_MODEM_TIMEOUT_COUNT)
	{
		Serialflush();
		return 2;
	}
	else
	return 3;
}



unsigned char gsmGetRegStatus(void)
{
	unsigned int i;
	for(i = 0;i <= GSM_REGISTER_STATUS_TRIAL_MAX;i++)
	{
		Serialflush();
		Serialprint("AT+CREG?\r\n");
		gsmTimerStart();
		while(gsmGetTimeout() == 1 && uartNewLineCount < 2);
		gsmTimerStop();
		if(uartNewLineCount >= 2)
		{
		if(uartReadBuffer[2] == '+' && uartReadBuffer[3] == 'C' &&  uartReadBuffer[4] == 'R' && uartReadBuffer[5] == 'E' && uartReadBuffer[6] == 'G' && uartReadBuffer[7] == ':')
		{
			// Responce +CREG: <n>,<stat>[,<lac>,<ci>] OK (We are checking status [<stat>] index is 9
		if(uartReadBuffer[11]-48 == 1 )
		{
					Serialflush();
					return 0;
		}
        else if(uartReadBuffer[11]-48 != 0)
		{
			Serialflush();
					return 1; // String Error	
		}		
	    }
		}	
		}
		return 2; // Timeout Error
	}



unsigned char gsmReadDtmf(void)
{
unsigned char val;
if(uartNewLineCount >= 2)
{
if(uartReadBuffer[2]  == '+' && uartReadBuffer[3]  == 'D' && uartReadBuffer[4]  == 'T' && uartReadBuffer[5] == 'M' && uartReadBuffer[6] == 'F' && uartReadBuffer[7] == ':')
{
val =  uartReadBuffer[8] - 48;
Serialflush();
return val;
}
else
return 15;
}
else
return 15;
}

unsigned char gsmSignalStrength(void)
{
    unsigned char Rssi = 0;
    Serialflush();
	Serialprint("AT+CSQ=?\r\n");
	gsmTimerStart();
	while(gsmGetTimeout() == 1 && uartNewLineCount < 2);
    gsmTimerStop();
	if(uartNewLineCount >= 2)
	{
		if(uartReadBuffer[2] == '+' && uartReadBuffer[3] == 'C' && uartReadBuffer[4] == 'S' && uartReadBuffer[5] == 'Q' && uartReadBuffer[6] == ':' )
		{
		    if(uartReadBuffer[8] == ',')
			Rssi = uartReadBuffer[7] - 48;
			else
			Rssi = (uartReadBuffer[7] - 48) * 10 + uartReadBuffer[8] - 48;
			Serialflush();
			if(Rssi > 0 && Rssi <= 31)
			return 0;                  // Signal Found
			else
			return 4;                  // No Signal
		}
		else
		{
			Serialflush();
			return 1;	   // String Error
		}
	}
	else if(timerCount0 >= __GSM_MODEM_TIMEOUT_COUNT)
	{
		Serialflush();
		return 2;
	}
	else
	return 3;
}



unsigned int gsmSendSms(char *No,char *Msg)
{
unsigned char temp;
unsigned char Var = 0;
unsigned int  var = 1;
unsigned int  loc = 0;
Serialflush();
gsmTimerStart();
Serialprint("AT+CMGS=\"");
Serialprint(No);
Serialprint("\"\r\n");
while(gsmGetTimeout() == 1 && uartReadBuffer[uartReadCount] != ' ');
gsmTimerStop();
if(uartReadCount >= 3)
{
if(uartReadBuffer[2] != 0x3E && uartReadBuffer[uartReadCount] != 0x20)
{
return SEND_SMS_STRING_ERROR;
}
else if(uartReadBuffer[2] == 0x3E && uartReadBuffer[uartReadCount] == 0x20) // Now you can send sms
{
Serialflush();
gsmTimerStart();
Serialprint(Msg);
Serialwrite(SUB);
while(gsmGetTimeout() == 1 && uartNewLineCount < 4);
gsmTimerStop();
// Check location
if(uartReadBuffer[2] == '+' && uartReadBuffer[3] == 'C' && uartReadBuffer[4] == 'M' && uartReadBuffer[5] == 'G' && uartReadBuffer[6] == 'S' && uartReadBuffer[7] == ':' && uartReadBuffer[8] == ' ')
{
gsmTimerStart();
for(temp = 9;uartReadBuffer[temp]  != 0x0D && gsmGetTimeout() == 1;temp++);
gsmTimerStop();
if(timerCount0 >= __GSM_MODEM_TIMEOUT_COUNT)
return SEND_SMS_ERROR_WHILE_READING_LOC;
else 
{
for(Var=temp;Var <= 8;Var--)
{
loc = loc + (loc * var)
var = var * 10;
}
return loc;
}
}
else
return SEND_SMS_STRING_ERROR_WHILE_SENDING;
else if(timerCount0 >= __GSM_MODEM_TIMEOUT_COUNT)
return SEND_SMS_TIMEOUT_ERROR_WHILE_SENDING;
}
else
return SEND_SMS_UNKNWN_ERROR;
}
else if(timerCount0 >= __GSM_MODEM_TIMEOUT_COUNT)
return SEND_SMS_TIMEOUT_ERROR;
}

unsigned char gsmSetSmsFormat(unsigned char _Mode)
{
    Serialflush();
	Serialprint("AT+CMGF=");
	Serialwrite(_Mode+48);
	Serialprint("\r\n");
	gsmTimerStart();
	while(gsmGetTimeout() == 1 && uartNewLineCount < 2);
    gsmTimerStop();
	if(uartNewLineCount >= 2)
	{
		if(uartReadBuffer[2] == 'O' && uartReadBuffer[3] == 'K')
		{
			Serialflush();
			return 0;  // Detected
		}
		else
		{
			Serialflush();
			return 1;	   // String Error
		}
	}
	else if(timerCount0 >= __GSM_MODEM_TIMEOUT_COUNT)
	{
		Serialflush();
		return 2;
	}
	else
	return 3;
}

void gsmReset(void)
{
	MODEM_RST_KEY_PORT &= ~(MODEM_RST_KEY_BIT);
	_delay_milli(GSM_PWR_KEY_COUNT);
	MODEM_RST_KEY_PORT |= MODEM_RST_KEY_BIT;
	_delay_milli(GSM_PWR_KEY_COUNT);
}

void gsmPowerUp(void)
{
	MODEM_RST_KEY_PORT |= MODEM_RST_KEY_BIT;
	MODEM_PWR_KEY_PORT &= ~(MODEM_PWR_KEY_BIT);
	_delay_milli(GSM_PWR_KEY_COUNT);
	MODEM_PWR_KEY_PORT |= MODEM_PWR_KEY_BIT;
	_delay_milli(GSM_PWR_KEY_COUNT);
}

unsigned char gsmStatus(void)
{
return MODEM_STA_KEY_PIN & MODEM_STA_KEY_BIT;
}

/*unsigned char gsmTryPowerUp(void)
{
	MODEM_RST_KEY_PORT |= MODEM_RST_KEY_BIT;
	MODEM_PWR_KEY_PORT &= ~(MODEM_PWR_KEY_BIT);
	delay_ms(GSM_PWR_KEY_COUNT);
	MODEM_PWR_KEY_PORT |= MODEM_PWR_KEY_BIT;
	delay_ms(GSM_PWR_KEY_COUNT);
}*/

void gsmPortinit(void)
{
MODEM_PWR_KEY_DIR |= MODEM_PWR_KEY_BIT;
MODEM_RST_KEY_DIR |= MODEM_RST_KEY_BIT;
MODEM_STA_KEY_DIR &= MODEM_STA_KEY_BIT;

// Enable Pull Up 
MODEM_PWR_KEY_PORT |= MODEM_PWR_KEY_BIT;
MODEM_RST_KEY_PORT |= MODEM_RST_KEY_BIT;
MODEM_STA_KEY_PORT |= MODEM_STA_KEY_BIT;
}


