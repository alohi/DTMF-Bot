
// DTMF Based Landrover
// Author : Sriharsha

#define _BAUD     9600

// DTMF Decoder Pinouts
#define D3        A0
#define D2        A1
#define D1        A2
#define D0        A3

#define INITIAL_SPEED 100

// LED
#define LED       13

// Motor Pinouts
#define IR        2
#define EN        3
#define MA1       4
#define MA2       5
#define MB1       6
#define MB2       7
#define MC1       8
#define MC2       9
#define MD1       10
#define MD2       11
#define SMOKE     A4
#define FIRE      A5

#define DTMF_FW   1
#define DTMF_BW   2
#define DTMF_LT   3
#define DTMF_RT   4
#define DTMF_ST   5
#define DTMF_SI   6
#define DTMF_SD   7

unsigned int __Speed = INITIAL_SPEED;

void sendSms(char *No,char *Msg)
{
  Serial.println("AT+CMGS=\"");
  delay(5);
  Serial.print(No);
  Serial.print("\"\n\r");
  delay(5);
  Serial.println(Msg);
  delay(5);
  Serial.write(0x1A);
}
  
void setup(void)
{
  pinMode(D3,INPUT);
  pinMode(D2,INPUT);
  pinMode(D1,INPUT);
  pinMode(D0,INPUT);
  
  pinMode(IR,INPUT);
  
  pinMode(EN,OUTPUT);
  pinMode(MA1,OUTPUT);
  pinMode(MA2,OUTPUT);
  pinMode(MB1,OUTPUT);
  pinMode(MB2,OUTPUT);
  pinMode(MC1,OUTPUT);
  pinMode(MC2,OUTPUT);
  pinMode(MD1,OUTPUT);
  pinMode(MD2,OUTPUT);
  
  pinMode(SMOKE,INPUT);
  pinMode(FIRE,INPUT);
  
  Serial.begin(_BAUD);
}

void set_Speed(unsigned int _speed)
{
  analogWrite(EN,_speed);
}

void motorFw(void)
{
}

void motorBw(void)
{
}

void motorLeft(void)
{
}

void motorRight(void)
{
}

void motorStop(void)
{
}

void loop(void)
{
  unsigned char dtmfVal;
  dtmfVal = (digitalRead(D3) * 8) + (digitalRead(D2) * 4) + (digitalRead(D1) * 2) + (digitalRead(D0) * 1);
  
  #define DEBUG
  Serial.println(dtmfVal);
  #endif
  
  switch(dtmfVal)
  {
    case DTMF_FW : motorFw();
                   break;
    case DTMF_BW : motorBw();
                   break;
    case DTMF_LT : motorLeft();
                   break;
    case DTMF_RT : motorRight();
                   break;
    case DTMF_ST : motorStop();
                   break;
    case DTMF_SI : set_Speed(__Speed++);
                   break;
    case DTMF_SD : set_Speed(__Speed--);
                   break;
  }
  
  // IR obstacle sensor handle
  
  // Smoke sensor
  
  // Fire Sensor
}
