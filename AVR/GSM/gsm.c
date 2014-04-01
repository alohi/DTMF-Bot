
unsigned char detectModem(void)
{

}

unsigned char detectCall(void)
{
if(uartNewLineFlag == 1)
{
if(uartReadBuffer[0] == 'R' && uartReadBuffer[1] == 'I' && uartReadBuffer[2] == 'N' && uartReadBuffer[3] == 'G')
{
Serialflush();
return 1;
}
else 
return 0;
}
else 
return 0;
}

unsigned char connectCall(void)
{
Serialprint("ATA;\r\n");
// Condition has to add
return 1;
}

unsigned char enableDtmf(void)
{
Serialprint("AT+DDET=1\r\n");
// Condition has to add
return 1;
}

unsigned char getDtmf(void)
{
unsigned char val;
if(uartNewLineFlag == 1)
{
if([0]  == '+' && uartReadBuffer[1]  == 'D' && uartReadBuffer[2]  == 'T' && uartReadBuffer[3] == 'M' && uartReadBuffer[4] == 'F' && uartReadBuffer[5] == ':')
{
val =  uartReadBuffer[6] - 48;
return val;
}
else
return 15;
}
else
return 15;
}


