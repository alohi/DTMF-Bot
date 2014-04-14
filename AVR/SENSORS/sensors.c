
#include "sensors.h"
#include "avr_delay.h"

void sensorsBegin(void)
{
SMK_DIR &= ~(SMK_BIT);
/*Adcbegin();
analogReference(EXTERNAL_AREF);*/
DDRC &= ~(1 << 4);
DDRC &= ~(1 << 5);
/*PORTC |= 1 << 4;
PORTC |= 1 << 5;*/
  //  ADMUX  = 0x00;
    ADCSRA = (1<<ADEN); 
}

unsigned int readAnalog(unsigned char Ch)
{
/*	volatile int temp;
	    if(Ch == IR_CH)
		{
		ADMUX =  (0b00000100);
		}
		else if(Ch == FIR_CH)
		{
	    ADMUX =  (0b00000101);
		}
   ADCSRA |= (1<<ADSC);
  
  // wait for conversion to complete
  // ADSC becomes ’0? again
  // till then, run loop continuously
  		while (ADCSRA &  (1<<ADSC));
  //ADCSRA &= ~(1 << ADIF);
 temp = ADCW;
 return temp;*/
 ADMUX = (1<<REFS0) | ( Ch & 0x0f); 

   ADCSRA |= (1<<ADEN)|(1<<ADSC);
   while ((ADCSRA & 0x10)==0);
   ADCSRA|=0x10;
   return ADC;
}



unsigned int sensorsReadIR(void)
{
	unsigned int val = 0;
	unsigned int i;
	/*for(i=0;i<=AVG_SAMPLE_RATE;i++)
	{
		val = val +  readAnalog(IR_CH);
	}
	return val / AVG_SAMPLE_RATE;*/
	return readAnalog(IR_CH);
}

unsigned int sensorsReadFire(void)
{
		unsigned int val = 0;
		unsigned int i;
		/*for(i=0;i<=AVG_SAMPLE_RATE;i++)
		{
			val = val +  readAnalog(FIR_CH);
		}
		return val / AVG_SAMPLE_RATE;*/
		return readAnalog(FIR_CH);
}

unsigned char sensorsDetectObstacle(void)
{
if(sensorsReadIR() > IR_THRESHOLD)
{
//	_delay_milli(1000);
	return 0;  // Obstacle Found
}
else
return 1; // No obstacle
}

unsigned char sensorsDetectFire(void)
{
if(sensorsReadFire() > FIRE_THRESHOLD)
{
//	_delay_milli(1000);
return 0;  // Fire Detected	
}
else
return 1; // No Fires
}

unsigned char sensorsDetectSmoke(void)
{
return ~(SMK_PORT & SMK_BIT);
}