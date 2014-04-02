
#include "avr_delay.h"

void delay_ms(unsigned int val)
{
	while(val > 0)
	{
		_delay_ms(1);
		val--;
	}
}

void delay_us(unsigned int val)
{
	while(val > 0)
	{
		_delay_us(1);
		val--;
	}
}