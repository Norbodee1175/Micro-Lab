#include <SPI.h>

#define INT_PIN1 2
#define INT_PIN2 4
#define PWM 3
#define IN1 A1
#define IN2 A2
#define Data 11
#define Clk 13
#define Latch_1 10
#define Latch_2 9
#define LED 8

int position=0;
int setpoint=0;
int PID, Proportional, Integral, Derivative;
int lastproportional;
int x,y;

char number[10]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void setup()
{
  pinMode(INT_PIN1,INPUT_PULLUP);
  pinMode(INT_PIN2,INPUT_PULLUP);
  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(Data,OUTPUT);
  pinMode(Clk,OUTPUT);
  pinMode(Latch_1,OUTPUT);
  pinMode(Latch_2,OUTPUT);
  pinMode(LED,OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(INT_PIN1),encoder_A,RISING);
  
  direction(1);
  speed(1);
  Serial.begin(9600);
}

void spi_write_1(unsigned char cData)
{
  shiftOut(Data, Clk, MSBFIRST, cData);
  digitalWrite(Latch_1,HIGH);
  digitalWrite(Latch_1,LOW);
}

void spi_write_2(unsigned char cData)
{
  shiftOut(Data, Clk, MSBFIRST, cData);
  digitalWrite(Latch_2,HIGH);
  digitalWrite(Latch_2,LOW);
}

void loop()
{
  //Input
  if(Serial.available()>0)
  {
    String a = Serial.readString();
    setpoint = a.toInt();
  }
  Proportional= position-setpoint;
  Integral= Integral+Proportional;
  Derivative= Proportional-lastproportional;
  lastproportional=Proportional;
  
  PID=(Proportional*10)+(Integral*0.000001)+(Derivative*5);
  speed(PID);
  direction(PID);
  //if(position<10)
  //{
    //spi_write_1(number[position]);
    //spi_write_2(number[position]);
  //}
  //else
  //{
     //position=0;
  //}
}

void direction(int a)
{
  if(a<0)
  {
    digitalWrite(A1,LOW);
    digitalWrite(A2,HIGH);
  }
  else
  {
    digitalWrite(A1,HIGH);
    digitalWrite(A2,LOW);
  }
}

void speed(int b)
{
  int a;
  if(b==0)
   a=1;
  else
    a=b;
  //if(absolute(a)>255)
  //{
  //  a=255;
  //}
  analogWrite(PWM,absolute(a));
}

int absolute(int t)
{
  if(t<0)
  {
    return t*-1;
  }
  else
  {
    return t;
  }
}

void encoder_A()
{
  if(digitalRead(INT_PIN1) == 1 && digitalRead(INT_PIN2) == 0) //Ch A is HIGH. Ch B is LOW.
  {
    //Serial.println("Left");
    position++;
  }
  else
  {
    //Serial.println("Right");
    position--;
  }
  
  if(position<0)
  {
    digitalWrite(LED,HIGH);
  }
  else
  {
    digitalWrite(LED,LOW);
  }
  Serial.print(position);
  Serial.print(",");
  Serial.println(setpoint);
  
  x=position/100;
  y=x%10;
  spi_write_2(number[y]);
  x=x/10;
  spi_write_1(number[x]); 
}
