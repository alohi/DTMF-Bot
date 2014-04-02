
#include "led.h"


void ledBegin(void)
{
// Set As output
LED1_DIR |= LED1_BIT;
LED1_DIR |= LED2_BIT;
LED1_DIR |= LED3_BIT;
LED1_DIR |= LED4_BIT;

// Pull up
LED1_PORT |= LED1_BIT;
LED1_PORT |= LED2_BIT;
LED1_PORT |= LED3_BIT;
LED1_PORT |= LED4_BIT;
}

void ledOn(unsigned char led_no,unsigned char OnOff)
{
if(led_no == 1)
{
if(OnOff == 1)
LED1_PORT &= ~(LED1_BIT);
else
LED1_PORT |=  (LED1_BIT);
}
else if(led_no == 2)
{
if(OnOff == 1)
LED2_PORT &= ~(LED2_BIT);
else
LED2_PORT |=  (LED2_BIT);
}
else if(led_no == 3)
{
if(OnOff == 1)
LED3_PORT &= ~(LED3_BIT);
else
LED3_PORT |=  (LED3_BIT);
}
else if(led_no == 4)
{
if(OnOff == 1)
LED4_PORT &= ~(LED4_BIT);
else
LED4_PORT |=  (LED4_BIT);
}
}

void ledNo(unsigned char No)
{
	switch(No)
	{
		case 0 : ledOn(4,0);
		         ledOn(3,0);
				 ledOn(2,0);
				 ledOn(1,0);
				 break;
		case 1 : ledOn(4,1);
		         ledOn(3,0);
		         ledOn(2,0);
		         ledOn(1,0);
		         break;
		case 2 : ledOn(4,0);
		         ledOn(3,1);
		         ledOn(2,0);
		         ledOn(1,0);
		         break;
		case 3 : ledOn(4,1);
		         ledOn(3,1);
		         ledOn(2,0);
		         ledOn(1,0);
		         break;
        case 4 : ledOn(4,0);
		         ledOn(3,0);
		         ledOn(2,1);
		         ledOn(1,0);
		         break;
	    case 5 : ledOn(4,1);
		         ledOn(3,0);
		         ledOn(2,1);
		         ledOn(1,0);
		         break;
		case 6 : ledOn(4,0);
		         ledOn(3,1);
		         ledOn(2,1);
		         ledOn(1,0);
		         break;
		case 7 : ledOn(4,1);
		         ledOn(3,1);
		         ledOn(2,1);
		         ledOn(1,0);
		         break;
	    case 8 : ledOn(4,0);
		         ledOn(3,0);
		         ledOn(2,0);
		         ledOn(1,1);
		         break;
		case 9 : ledOn(4,1);
		         ledOn(3,0);
		         ledOn(2,0);
		         ledOn(1,1);
		         break;
		case 10: ledOn(4,0);
		         ledOn(3,1);
		         ledOn(2,0);
		         ledOn(1,1);
		         break;
		case 11: ledOn(4,1);
		         ledOn(3,1);
		         ledOn(2,0);
		         ledOn(1,1);
		         break;
		case 12: ledOn(4,0);
		         ledOn(3,0);
		         ledOn(2,1);
		         ledOn(1,1);
		         break;
		case 13: ledOn(4,1);
		         ledOn(3,0);
		         ledOn(2,1);
		         ledOn(1,1);
		         break;
		case 14: ledOn(4,0);
		         ledOn(3,1);
		         ledOn(2,1);
		         ledOn(1,1);
		         break;
	    case 15: ledOn(4,1);
		         ledOn(3,1);
		         ledOn(2,1);
		         ledOn(1,1);
		         break;
}
}

void ledBlinkOne(unsigned char _led,unsigned int _delay,unsigned char _repeat)
{
unsigned char i;
ledNo(0);
for(i=0;i<=_repeat;i++)
{
ledOn(_led,1);
_delay_milli(_delay);
ledOn(_led,0);
_delay_milli(_delay);
}
ledNo(0);
}

void ledBlinkDouble(unsigned char _led1,unsigned char _led2,unsigned int _delay,unsigned char _repeat)
{
unsigned char i;
ledNo(0);
for(i=0;i<=_repeat;i++)
{
ledOn(_led1,1);
ledOn(_led2,1);
_delay_milli(_delay);
ledOn(_led1,0);
ledOn(_led2,0);
_delay_milli(_delay);
}
ledNo(0);
}

void ledBlinkTriple(unsigned char _led1,unsigned char _led2,unsigned char _led3,unsigned int _delay,unsigned char _repeat)
{
unsigned char i;
ledNo(0);
for(i=0;i<=_repeat;i++)
{
ledOn(_led1,1);
ledOn(_led2,1);
ledOn(_led3,1);
_delay_milli(_delay);
ledOn(_led1,0);
ledOn(_led2,0);
ledOn(_led3,0);
_delay_milli(_delay);
}
ledNo(0);
}

void ledBlinkAll(unsigned int _delay,unsigned char _repeat)
{
unsigned char i;
ledNo(0);
for(i=0;i<=_repeat;i++)
{
ledOn(1,1);
ledOn(2,1);
ledOn(3,1);
ledOn(4,1);
_delay_milli(_delay);
ledOn(1,0);
ledOn(2,0);
ledOn(3,0);
ledOn(4,0);
_delay_milli(_delay);
}
ledNo(0);
}

void ledRun(unsigned char _val)
{

}