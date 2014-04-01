
#include "app.h"
#include "adc.h"

#define F_CPU 8000000UL
#include "avr/delay.h"



void setPullup(void)
{
	
//IR_PORT  |= IR_BIT;
//IR_PORT  &= ~(IR_BIT);
SMK_PORT |= SMK_BIT;
//FIR_PORT |= FIR_BIT
//FIR_PORT &= ~(FIR_BIT);

EN_PORT  |= EN_BIT;
MA1_PORT |= MA1_BIT;
MA2_PORT |= MA2_BIT;
MB1_PORT |= MB1_BIT;
MB2_PORT |= MB2_BIT;
MC1_PORT |= MC1_BIT;
MC2_PORT |= MC2_BIT;
MD1_PORT |= MD1_BIT;
MD2_PORT |= MD2_BIT;
}

void setPortDir(void)
{
// IR as input
//IR_DIR  &= ~(IR_BIT);
// Smoke sensor as input
SMK_DIR &= ~(SMK_BIT);
// Fire Sensor as input
//FIR_DIR &= ~(FIR_BIT);

// Indicators as output
LED1_DIR |= LED1_BIT;
LED2_DIR |= LED2_BIT;
LED3_DIR |= LED3_BIT;
LED4_DIR |= LED4_BIT;

// Motor Enable as output
EN_DIR  |= EN_BIT;

// Motor A Control Pins
MA1_DIR |= MA1_BIT;
MA2_DIR |= MA2_BIT;

// Motor B Control Pins
MB1_DIR |= MB1_BIT;
MB2_DIR |= MB2_BIT;

// Motor C Control Pins
MC1_DIR |= MC1_BIT;
MC2_DIR |= MC2_BIT;

// Motor D Control Pins
MD1_DIR |= MD1_BIT;
MD2_DIR |= MD2_BIT;
}

void initSystem(void)
{
	setPortDir();
	setPullup();
	motorStop();
	led_indicate_numbers(15);
	Adcbegin();
	analogReference(EXTERNAL_AVCC);
}

void led_indicate(int led_no,int OnOff)
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

void led_indicate_numbers(unsigned char No)
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

void motorStop(void)
{
EN_PORT  &= ~(EN_BIT);
MA1_PORT &= ~(MA1_BIT);
MA2_PORT &= ~(MA2_BIT);
MB1_PORT &= ~(MB1_BIT);
MB2_PORT &= ~(MB2_BIT);
MC1_PORT &= ~(MC1_BIT);
MC2_PORT &= ~(MC2_BIT);
MD1_PORT &= ~(MD1_BIT);
MD2_PORT &= ~(MD2_BIT);
}

void motorForward(void)
{
// Speed has to set at below line
EN_PORT  |= (EN_BIT);

MA1_PORT &= ~(MA1_BIT);
MA2_PORT |=  (MA2_BIT);
MB1_PORT &= ~(MB1_BIT);
MB2_PORT |=  (MB2_BIT);
MC1_PORT &= ~(MC1_BIT);
MC2_PORT |=  (MC2_BIT);
MD1_PORT &= ~(MD1_BIT);
MD2_PORT |=  (MD2_BIT);
}

void motorBackward(void)
{
	// Speed has to set at below line
	EN_PORT  |= (EN_BIT);

MA1_PORT |=  (MA1_BIT);
MA2_PORT &= ~(MA2_BIT);
MB1_PORT |=  (MB1_BIT);
MB2_PORT &= ~(MB2_BIT);
MC1_PORT |=  (MC1_BIT);
MC2_PORT &= ~(MC2_BIT);
MD1_PORT |=  (MD1_BIT);
MD2_PORT &= ~(MD2_BIT);
}

void motorLeft(void)
{
	// Speed has to set at below line
	EN_PORT  |= (EN_BIT);

	MA1_PORT |=  (MA1_BIT);
	MA2_PORT &= ~(MA2_BIT);
	MB1_PORT &= ~(MB1_BIT);
	MB2_PORT &= ~(MB2_BIT);
	MC1_PORT &= ~(MC1_BIT);
	MC2_PORT &= ~(MC2_BIT);
	MD1_PORT |=  (MD1_BIT);
	MD2_PORT &= ~(MD2_BIT);
	_delay_ms(2000);
	motorStop();
}

void motorRight(void)
{
	// Speed has to set at below line
	EN_PORT  |= (EN_BIT);

	MA1_PORT &= ~(MA1_BIT);
	MA2_PORT &= ~(MA2_BIT);
	MB1_PORT |=  (MB1_BIT);
	MB2_PORT &= ~(MB2_BIT);
	MC1_PORT |=  (MC1_BIT);
	MC2_PORT &= ~(MC2_BIT);
	MD1_PORT &= ~(MD1_BIT);
	MD2_PORT &= ~(MD2_BIT);
	_delay_ms(2000);
	motorStop();
}

unsigned int readIR(void)
{
	unsigned int val = 0;
	unsigned int i;
	for(i=0;i<=50;i++)
	{
		val = val +  analogRead(IR_CH);
	}
	return val / 50;
}

unsigned int readFire(void)
{
		unsigned int val = 0;
		unsigned int i;
		for(i=0;i<=50;i++)
		{
			val = val +  analogRead(FIR_CH);
		}
		return val / 50;
}



