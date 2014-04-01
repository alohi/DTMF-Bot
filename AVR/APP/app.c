
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
EN_DIR |= EN_BIT;

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

