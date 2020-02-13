#include<SPI.h>
#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN 9
#define SS1_PIN 8
int num[10]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,
           0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
int count=0,i=0;



void setup()
{
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(5,OUTPUT);

}

void loop()
{
  int a=digitalRead(2);
  int b=digitalRead(3);
  int c=digitalRead(4);
  if(a==0)
  {
    i++;
    if(i>9)
    {
    i=0;
    count++;
    }
    if(count>9)
    count=0;  
  }
  
    if(b==0)
  {
    i--;
    if(i<0)
    {
    i=10;
    count--;
    }
    if(count<0)
    count=9;  
  }
  if(count<0)
    count=0;
   if(i<0)
   {
   i=0;
   }
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,num[i]);  
  digitalWrite(SS1_PIN,HIGH);
  delay(200);
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,num[count]);  
  digitalWrite(SS_PIN,HIGH);
  delay(200);
   digitalWrite(SS1_PIN,LOW);
  digitalWrite(SS_PIN,LOW);
    if(c==0)
  {
  while(count>=0)
  {
    i--;
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,num[i]);  
  digitalWrite(SS1_PIN,HIGH);
  delay(200);
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,num[count]);  
  digitalWrite(SS_PIN,HIGH);
  delay(200);
  digitalWrite(SS1_PIN,LOW);
  digitalWrite(SS_PIN,LOW);
       if(i<0)
  {
    count--;
    i=10;
  }
  }
      digitalWrite(5,HIGH);
  }
}
  
