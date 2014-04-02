
#include "led.h"


void ledBegin(void)
{
// Set As output
LED1_DIR |= LED1_BIT;
LED1_DIR |= LED1_BIT;
LED1_DIR |= LED1_BIT;
LED1_DIR |= LED1_BIT;

// Pull up
LED1_PORT |= LED1_BIT;
LED1_PORT |= LED1_BIT;
LED1_PORT |= LED1_BIT;
LED1_PORT |= LED1_BIT;
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
		case 0 : led_indicate(4,0);
		         led_indicate(3,0);
				 led_indicate(2,0);
				 led_indicate(1,0);
				 break;
		case 1 : led_indicate(4,1);
		         led_indicate(3,0);
		         led_indicate(2,0);
		         led_indicate(1,0);
		         break;
		case 2 : led_indicate(4,0);
		         led_indicate(3,1);
		         led_indicate(2,0);
		         led_indicate(1,0);
		         break;
		case 3 : led_indicate(4,1);
		         led_indicate(3,1);
		         led_indicate(2,0);
		         led_indicate(1,0);
		         break;
        case 4 : led_indicate(4,0);
		         led_indicate(3,0);
		         led_indicate(2,1);
		         led_indicate(1,0);
		         break;
	    case 5 : led_indicate(4,1);
		         led_indicate(3,0);
		         led_indicate(2,1);
		         led_indicate(1,0);
		         break;
		case 6 : led_indicate(4,0);
		         led_indicate(3,1);
		         led_indicate(2,1);
		         led_indicate(1,0);
		         break;
		case 7 : led_indicate(4,1);
		         led_indicate(3,1);
		         led_indicate(2,1);
		         led_indicate(1,0);
		         break;
	    case 8 : led_indicate(4,0);
		         led_indicate(3,0);
		         led_indicate(2,0);
		         led_indicate(1,1);
		         break;
		case 9 : led_indicate(4,1);
		         led_indicate(3,0);
		         led_indicate(2,0);
		         led_indicate(1,1);
		         break;
		case 10: led_indicate(4,0);
		         led_indicate(3,1);
		         led_indicate(2,0);
		         led_indicate(1,1);
		         break;
		case 11: led_indicate(4,1);
		         led_indicate(3,1);
		         led_indicate(2,0);
		         led_indicate(1,1);
		         break;
		case 12: led_indicate(4,0);
		         led_indicate(3,0);
		         led_indicate(2,1);
		         led_indicate(1,1);
		         break;
		case 13: led_indicate(4,1);
		         led_indicate(3,0);
		         led_indicate(2,1);
		         led_indicate(1,1);
		         break;
		case 14: led_indicate(4,0);
		         led_indicate(3,1);
		         led_indicate(2,1);
		         led_indicate(1,1);
		         break;
	    case 15: led_indicate(4,1);
		         led_indicate(3,1);
		         led_indicate(2,1);
		         led_indicate(1,1);
		         break;
}
}

void ledBlink(unsigned char _led,)
{

}

void ledRun(unsigned char )
{

}