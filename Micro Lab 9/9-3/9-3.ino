int previous_error;
int integral;
int error;
int derivative;
int setpoint=100;
int kp=10,ki=20,kd=55;
int speed=0,C,B,dis;
const byte interruptPin2 = 2;
const byte interruptPin3 = 3;
void setup()
{
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(interruptPin2, INPUT_PULLUP);
  pinMode(interruptPin3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin2),S,RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin3),D,RISING);
  Serial.begin(9600);
}

void loop()
{
 setpoint=analogRead(A0);
 error=setpoint-dis;
 integral=integral+error; 
 derivative= error - previous_error;
 speed=(kp*error)+(ki*integral)+(kd*derivative);
 previous_error=error;
 if(speed>255)
 speed=255;
 if(error>0)
  FOW(speed);
 if(error<0)
  BACK(speed);
 Serial.println(dis);
}
void FOW(int A)
{
 digitalWrite(4,HIGH);
 digitalWrite(5,LOW);
 analogWrite(6,A);
}
void BACK(int A)
{
 digitalWrite(4,LOW);
 digitalWrite(5,HIGH);
 analogWrite(6,A);
}
void D() 
{
  B = digitalRead(interruptPin2);
  C = digitalRead(interruptPin3);
  if((B==0)&&(C==1))
    dis++;
}
void S() 
{
  B = digitalRead(interruptPin2);
  C = digitalRead(interruptPin3);
  if((B==1)&&(C==0))
    dis--;
}
