

#include "gsm.h"
#include "app.h"

unsigned char detectModem(void)
{
Serialflush();
Serialprint("AT\r\n");
timerClearCount(HW_TIMER0);
timerBegin(__CLK__FREQUENCY,__GSM_MODEM_TIMEOUT_US,HW_TIMER0);
timerEnableInterrupt(HW_TIMER0);
timerStart(HW_TIMER0);
while(timerCount0 < __GSM_MODEM_TIMEOUT_COUNT && uartNewLineCount < 2);
timerStop(HW_TIMER0);
timerDisableInterrupt(HW_TIMER0);
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

unsigned char echoOff(void)
{
	Serialflush();
	Serialprint("ATE0\r\n");
	timerClearCount(HW_TIMER0);
	timerBegin(__CLK__FREQUENCY,__GSM_MODEM_TIMEOUT_US,HW_TIMER0);
	timerEnableInterrupt(HW_TIMER0);
	timerStart(HW_TIMER0);
	while(timerCount0 < __GSM_MODEM_TIMEOUT_COUNT && uartNewLineCount < 2);
	timerStop(HW_TIMER0);
	timerDisableInterrupt(HW_TIMER0);
	if(uartNewLineCount >= 2)
	{
		if(uartReadBuffer[2] == 'O' && uartReadBuffer[1] == '3')
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

unsigned char detectCall(void)
{
if(uartNewLineCount >= 2)
{
if(uartReadBuffer[2] == 'R' && uartReadBuffer[3] == 'I' && uartReadBuffer[4] == 'N' && uartReadBuffer[5] == 'G') // If string is "RING"
{
Serialflush();
return 0;
}
else 
return 1;
}
else 
return 2;
}

unsigned char Callstatus(void)
{
	if(uartNewLineCount >= 2)
	{
		if(uartReadBuffer[2] == 'N' && uartReadBuffer[3] == 'O' && uartReadBuffer[4] == ' ' && uartReadBuffer[5] == 'C' && uartReadBuffer[6] == 'A' && uartReadBuffer[7] == 'R' && uartReadBuffer[8] == 'R' && uartReadBuffer[9] == 'I' && uartReadBuffer[10] == 'E' && uartReadBuffer[11] == 'R') // If string is "RING"
		{
			Serialflush();
			return 0; // Call disconnected
		}
		else
		return 1;
	}
	else
	return 2;
}

unsigned char connectCall(void)
{
	Serialflush();
	Serialprint("ATA\r\n");
	timerClearCount(HW_TIMER0);
	timerBegin(__CLK__FREQUENCY,__GSM_MODEM_TIMEOUT_US,HW_TIMER0);
	timerEnableInterrupt(HW_TIMER0);
	timerStart(HW_TIMER0);
	while(timerCount0 < __GSM_MODEM_TIMEOUT_COUNT && uartNewLineCount < 2);
	timerStop(HW_TIMER0);
// Condition has to add
//return 1;
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

unsigned char enableDtmf(void)
{
	Serialflush();
	Serialprint("AT+DDET=1\r\n");
	timerClearCount(HW_TIMER0);
	timerBegin(__CLK__FREQUENCY,__GSM_MODEM_TIMEOUT_US,HW_TIMER0);
	timerEnableInterrupt(HW_TIMER0);
	timerStart(HW_TIMER0);
	while(timerCount0 < __GSM_MODEM_TIMEOUT_COUNT && uartNewLineCount < 2);
	timerStop(HW_TIMER0);
	// Condition has to add
	//return 1;
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



unsigned char getRegisterStatus(void)
{
	unsigned int i;
	for(i = 0;i <= GSM_REGISTER_STATUS_TRIAL_MAX;i++)
	{
		Serialflush();
		Serialprint("AT+CREG?\r\n");
		timerClearCount(HW_TIMER0);
		timerBegin(__CLK__FREQUENCY,__GSM_MODEM_TIMEOUT_US,HW_TIMER0);
		timerEnableInterrupt(HW_TIMER0);
		timerStart(HW_TIMER0);
		while(timerCount0 < __GSM_MODEM_TIMEOUT_COUNT && uartNewLineCount < 2);
		timerStop(HW_TIMER0);
		// Condition has to add
		//return 1;
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



unsigned char getDtmf(void)
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

void gsmBegin(unsigned long osc,unsigned long baud)
{
	Serialbegin(osc,baud);
}


