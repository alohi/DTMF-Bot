#include "motor.h"

void motorBegin(void)
{
// Motor Enable as output
//EN_DIR  |= EN_BIT;

// Motor A Control Pins
/*MA1_DIR |= MA1_BIT;
MA2_DIR |= MA2_BIT;

// Motor B Control Pins
MB1_DIR |= MB1_BIT;
MB2_DIR |= MB2_BIT;*/
DDRD |= 1 << 4;
DDRD |= 1 << 5;
DDRD |= 1 << 6;
DDRD |= 1 << 7;

// Motor C Control Pins
MC1_DIR |= MC1_BIT;
MC2_DIR |= MC2_BIT;

// Motor D Control Pins
MD1_DIR |= MD1_BIT;
MD2_DIR |= MD2_BIT;

// Enable Pullup
//EN_PORT  |= EN_BIT;
/*MA1_PORT |= MA1_BIT;
MA2_PORT |= MA2_BIT;
MB1_PORT |= MB1_BIT;
MB2_PORT |= MB2_BIT;*/
PORTD |= 1 << 4;
PORTD |= 1 << 5;
PORTD |= 1 << 6;
PORTD |= 1 << 7;
MC1_PORT |= MC1_BIT;
MC2_PORT |= MC2_BIT;
MD1_PORT |= MD1_BIT;
MD2_PORT |= MD2_BIT;
}

void motorStop(void)
{
//EN_PORT  &= ~(EN_BIT);
/*MA1_PORT &= ~(MA1_BIT);
MA2_PORT &= ~(MA2_BIT);
MB1_PORT &= ~(MB1_BIT);
MB2_PORT &= ~(MB2_BIT);*/

PORTD = 1 << 4;
PORTD |= 1 << 5;
PORTD |= 1 << 6;
PORTD |= 1 << 7;
MC1_PORT &= ~(MC1_BIT);
MC2_PORT &= ~(MC2_BIT);
MD1_PORT &= ~(MD1_BIT);
MD2_PORT &= ~(MD2_BIT);
}

void motorForward(void)
{
// Speed has to set at below line
//EN_PORT  |= (EN_BIT);

/*MA1_PORT &= ~(MA1_BIT);
MA2_PORT |=  (MA2_BIT);
MB1_PORT &= ~(MB1_BIT);
MB2_PORT |=  (MB2_BIT);*/
PORTD &= ~(1 << 4);
PORTD |= 1 << 5;
PORTD &= ~(1 << 6);
PORTD |= 1 << 7;
MC1_PORT &= ~(MC1_BIT);
MC2_PORT |=  (MC2_BIT);
MD1_PORT &= ~(MD1_BIT);
MD2_PORT |=  (MD2_BIT);
}

void motorBackward(void)
{
// Speed has to set at below line
//EN_PORT  |= (EN_BIT);
/*
MA1_PORT |=  (MA1_BIT);
MA2_PORT &= ~(MA2_BIT);
MB1_PORT |=  (MB1_BIT);
MB2_PORT &= ~(MB2_BIT);
*/
PORTD |= 1 << 4;
PORTD &= ~(1 << 5);
PORTD |= (1 << 6);
PORTD &= ~(1 << 7);
MC1_PORT |=  (MC1_BIT);
MC2_PORT &= ~(MC2_BIT);
MD1_PORT |=  (MD1_BIT);
MD2_PORT &= ~(MD2_BIT);
}

void motorLeft(void)
{
	// Speed has to set at below line
	//EN_PORT  |= (EN_BIT);
/*
	MA1_PORT |=  (MA1_BIT);
	MA2_PORT &= ~(MA2_BIT);
	MB1_PORT &= ~(MB1_BIT);
	MB2_PORT &= ~(MB2_BIT);*/
PORTD |= 1 << 4;
PORTD &= ~(1 << 5);
PORTD &= ~(1 << 6);
PORTD &= ~(1 << 7);
	MC1_PORT &= ~(MC1_BIT);
	MC2_PORT &= ~(MC2_BIT);
	MD1_PORT |=  (MD1_BIT);
	MD2_PORT &= ~(MD2_BIT);
	_delay_milli(MOTOR_TURN_DELAY);
	motorStop();
}

void motorRight(void)
{
	// Speed has to set at below line
	//EN_PORT  |= (EN_BIT);

	/*MA1_PORT &= ~(MA1_BIT);
	MA2_PORT &= ~(MA2_BIT);
	MB1_PORT |=  (MB1_BIT);
	MB2_PORT &= ~(MB2_BIT);*/
	PORTD &= ~(1 << 4);
	PORTD &= ~(1 << 5);
	PORTD |=  (1 << 6);
	PORTD &= ~(1 << 7);
	
	MC1_PORT |=  (MC1_BIT);
	MC2_PORT &= ~(MC2_BIT);
	MD1_PORT &= ~(MD1_BIT);
	MD2_PORT &= ~(MD2_BIT);
	_delay_milli(MOTOR_TURN_DELAY);
	motorStop();
}