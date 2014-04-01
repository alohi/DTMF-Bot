
#include "uart.h"
#include "app.h"
#include "gsm.h"
#include <util/delay.h>

void gsmTest(void)
{
	unsigned char var;
	unsigned char dtmfVal = 15;
	Serialprint("Gsm Test\n");
		var = detectModem();
		if(var == 0)
		{
			Serialprint("Detect Success\n");
		}
		else if(var == 1)
		{
			Serialprint("Detect String Error\n");
		}
				else if(var == 2)
				{
					Serialprint("Detect Timeout Error\n");
				}
				else
				{
					Serialprint("Detect Unknown Error\n");
				}
				
		var = getRegisterStatus();
		if(var == 0)
		{
			Serialprint("Network test success\n");
		}
		else if(var == 1)
		{
			Serialprint("Network test String Error\n");
		}
		else if(var == 2)
		{
			Serialprint("Network test timeout Error\n");
		}
		var = enableDtmf();
		if(var == 0)
		{
			Serialprint("DTMF set success\n");
		}
		else if(var == 1)
		{
			Serialprint("DTMF Set String Error\n");
		}
				else if(var == 2)
				{
					Serialprint("DTMF Set Timeout Error\n");
				}
				else
				{
					Serialprint("DTMF Set Unknown Error\n");
				}
				
				while(1)
				{
					if(detectCall() == 0)
					{
						Serialprint("Incoming Call\n");
						var = connectCall();
						if(var == 0)
						{
							Serialprint("Connect Call success\n");
						}
												else if(var == 1)
												{
													Serialprint("Connect Call String Error\n");
												}
																		else if(var == 2)
																		{
																			Serialprint("Connect Call Timeout Error\n");
																		}
																		else
																		Serialprint("Connect Call Unknown Error\n");
					}
					dtmfVal = getDtmf();
					if(dtmfVal < 15)
					{
						Serialprint("DTMF: ");
						Serialwrite(dtmfVal+48);
						Serialwrite('\n');
						dtmfVal = 15;
					}
					if(Callstatus() == 0)
					{
						Serialprint("Call disconnected\n");
					}
				}
}

void detectTest(void)
{
	unsigned char var;
		var = detectModem();
led_indicate_numbers(var);
}

void sensorTest(void)
{
	unsigned char var;
	Serialprint("Sensor Test\n");
	while(1)
	{
	/*	if(readIR() > IR_THRESHOLD)
		{
			Serialprint("Obstacle Detected\n");
		}
				if(readFire() > FIRE_THRESHOLD)
				{
					Serialprint("Fire Detected\n");
				}*/
/*if(SMK_PIN &SMK_BIT)
{
	Serialprint("Smoke Detected\n");
}*/
	SerialIntWrite(readIR(),10);
	Serialwrite(9);
	SerialIntWrite(readFire(),10);
	Serialwrite('\n');
	_delay_ms(3000);
	}

		
}

void indicatorTest(void)
{
	unsigned char i;
	while (1)
	{
			for(i=0;i<=15;i++)
			{
				led_indicate_numbers(i);
				_delay_ms(_test_delay);
			}
	}	
}

void testModem(void)
{
	unsigned char var;
	var = detectModem();
	led_indicate_numbers(var+1);
	_delay_ms(_TEST_INTERVAL);
	led_indicate_numbers(0);
	_delay_ms(_TEST_INTERVAL);
	var = getRegisterStatus();
	led_indicate_numbers(var+1);
	_delay_ms(_TEST_INTERVAL);
	led_indicate_numbers(0);
	_delay_ms(_TEST_INTERVAL);
	var = enableDtmf();
	led_indicate_numbers(var+1);
	_delay_ms(_TEST_INTERVAL);
	led_indicate_numbers(15);			
}

void callManageloop(void)
{
	unsigned char dtmfVal;
	while(1)
	{
		if(detectCall() == 0)
		{
			//led_indicate_numbers(connectCall() + 1);
			if(connectCall() == 0)
			{
				led_indicate_numbers(0);
				_delay_ms(_TEST_INTERVAL);
				led_indicate_numbers(2);
				_delay_ms(_TEST_INTERVAL);
				led_indicate_numbers(4);
				_delay_ms(_TEST_INTERVAL);
				led_indicate_numbers(8);
				_delay_ms(_TEST_INTERVAL);
				led_indicate_numbers(15);
			}
		}
		dtmfVal = getDtmf();
		if( dtmfVal < 15)
		led_indicate_numbers(dtmfVal);
		if(Callstatus() == 0)
		led_indicate_numbers(15);
	}
}

int main(void)
{
	unsigned char var;
	gsmBegin(__CLK__FREQUENCY,__BAUD_RATE___);
	initSystem();

	//gsmTest();
	//indicatorTest();
	//sensorTest();
	//detectTest();
	testModem();
	callManageloop();
	while(1);
}