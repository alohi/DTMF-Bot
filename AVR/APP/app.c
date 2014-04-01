
void setPullup(void)
{
IR_PORT  |= IR_BIT;
SMK_PORT |= SMK_BIT;
FIR_PORT |= FIR_BIT;

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
IR_DIR  &= ~(IR_BIT);
// Smoke sensor as input
SMK_DIR &= ~(SMK_BIT);
// Fire Sensor as input
FIR_DIR &= ~(FIR_BIT);

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

void stopMotor(void)
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

}


