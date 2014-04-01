
// DTMF Based Landrover
// Author : Sriharsha

#define DEBUG

#define _BAUD     9600

#define MobNo "9342833087"
#define SMOKE_WARNING "Warning, Smoke Detected"
#define FIRE_WARNING  "Warning, Fire Detected"

// DTMF Decoder Pinouts
#define D3        A0
#define D2        A1
#define D1        A2
#define D0        A3

#define INITIAL_SPEED 100

// LED
#define LED       13

// Motor Pinouts
#define EN        3
#define MA1       4
#define MA2       5
#define MB1       6
#define MB2       7
#define MC1       8
#define MC2       9
#define MD1       10
#define MD2       11
#define SMOKE     2
#define IR        A4
#define FIRE      A5

#define DTMF_FW   1
#define DTMF_BW   2
#define DTMF_LT   3
#define DTMF_RT   4
#define DTMF_ST   5
#define DTMF_SI   6
#define DTMF_SD   7

#define TURN_DELAY 1000

// MC, MD : Back  Wheels
// MA, MB : Front Wheels

unsigned int __Speed = INITIAL_SPEED;

boolean ObstFlag = false;

boolean FireFlag = false;
boolean SmokeFlag = false;

void sendSms(char *No,char *Msg)
{
  Serial.println("AT+CMGF=1");
  delay(200);
  Serial.println("AT+CMGS=");
  Serial.println(No);
  delay(200);
  Serial.println(Msg);
  delay(200);
  Serial.write(0x1A);
  delay(1000);
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
  
  // Pull up here
  ///////////////////
}

void set_Speed(unsigned int _speed)
{
  //analogWrite(EN,_speed);
  digitalWrite(EN,HIGH);
}

void motorStop(void)
{
  digitalWrite(EN,LOW);
  digitalWrite(MA1,LOW);
  digitalWrite(MA2,LOW);
  digitalWrite(MB1,LOW);
  digitalWrite(MB2,LOW);
  digitalWrite(MC1,LOW);
  digitalWrite(MC2,LOW);
  digitalWrite(MD1,LOW);
  digitalWrite(MD2,LOW);
}

void motorBw(void)
{
  set_Speed(__Speed);
  digitalWrite(MA1,HIGH);
  digitalWrite(MA2,LOW);
  digitalWrite(MB1,HIGH);
  digitalWrite(MB2,LOW);
  digitalWrite(MC1,HIGH);
  digitalWrite(MC2,LOW);
  digitalWrite(MD1,HIGH);
  digitalWrite(MD2,LOW);
}

void motorFw(void)
{
  set_Speed(__Speed);
  digitalWrite(MA1,LOW);
  digitalWrite(MA2,HIGH);
  digitalWrite(MB1,LOW);
  digitalWrite(MB2,HIGH);
  digitalWrite(MC1,LOW);
  digitalWrite(MC2,HIGH);
  digitalWrite(MD1,LOW);
  digitalWrite(MD2,HIGH);
}

void motorLeft(void)
{
  set_Speed(__Speed);
  digitalWrite(MA1,HIGH);
  digitalWrite(MA2,LOW);
  digitalWrite(MB1,LOW);
  digitalWrite(MB2,LOW);
  digitalWrite(MC1,HIGH);
  digitalWrite(MC2,LOW);
  digitalWrite(MD1,LOW);
  digitalWrite(MD2,LOW);
  
  delay(2000);
  motorStop();
}

void motorRight(void)
{
  set_Speed(__Speed);
  digitalWrite(MA1,LOW);
  digitalWrite(MA2,LOW);
  digitalWrite(MB1,HIGH);
  digitalWrite(MB2,LOW);
  digitalWrite(MC1,LOW);
  digitalWrite(MC2,LOW);
  digitalWrite(MD1,HIGH);
  digitalWrite(MD2,LOW);
  
  delay(2000);
  motorStop();
}

void SmsTest(void)
{
  while(1)
  {
  if(digitalRead(IR) == HIGH)
  {
//  sendSms("9342833087","Obstacle is detected");
Serial.println("AT+CMGF=1");
delay(200);
Serial.println("AT+CMGS=\"9342833087\"");
delay(200);
Serial.println("Obstacle is detected");
delay(200);
Serial.write(0x1A);
delay(2000);
  }
  }
}


void motorTest(void)
{
  char c;
   digitalWrite(EN,HIGH);
   Serial.println("Motor test is running..");
  while(1)
  {
    if(Serial.available())
    {
    c = Serial.read();
    switch(c)
    {
      case 'a' : motorFw();
                 break;
       case 'b' : motorBw();
                 break;
                       case 'c' : motorLeft();
                 break;
                       case 'd' : motorRight();
                 break;
                                        case 'e' : motorStop();
                 break;
                                 
    }
  }
}
}

unsigned char prevVal = 0;

void dtmfTest(void)
{
  unsigned char dtmfVal;
  Serial.println("Dtmf test is running..");
  while(1)
  {
  dtmfVal = (digitalRead(D3) * 8) + (digitalRead(D2) * 4) + (digitalRead(D1) * 2) + (digitalRead(D0) * 1);  
  if(dtmfVal != prevVal)
  {
    Serial.println(dtmfVal);
    prevVal = dtmfVal;
  }
  }
}

void loop(void)
{
  
  unsigned char dtmfVal;
//  motorTest();
//dtmfTest();
//SmsTest();
  dtmfVal = (digitalRead(D3) * 8) + (digitalRead(D2) * 4) + (digitalRead(D1) * 2) + (digitalRead(D0) * 1);
  
  #ifdef DEBUG
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
  if(digitalRead(IR) == HIGH)
  {
    // Add logic here
    /////////////////////////////
    /////////////////////////////
    motorStop();
    FireFlag = false;
    SmokeFlag = false;
  }
  
  // Smoke sensor
  if(digitalRead(SMOKE) == HIGH)
  {
    if(FireFlag == false)
    {
    delay(100);
    Serial.println("AT+CMGF=1");
    delay(200);
    Serial.println("AT+CMGS=\"9342833087\"");
    delay(200);
    Serial.println("Smoke detected");
    delay(200);
    Serial.write(0x1A);
    delay(2000);
    FireFlag = true;
    }
  }
  
  // Fire Sensor
  if(digitalRead(FIRE) == HIGH)
  {
    if(SmokeFlag == false)
    {
    delay(100);
    Serial.println("AT+CMGF=1");
    delay(200);
    Serial.println("AT+CMGS=\"9342833087\"");
    delay(200);
    Serial.println("Fire detected");
    delay(200);
    Serial.write(0x1A);
    delay(2000);
    SmokeFlag = true;
    }
  }
}
