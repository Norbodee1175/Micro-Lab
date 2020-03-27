int speed = 200,count=0,pcount=0,dis=0,C,B;
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
  Serial.print("direction ");
  if(count==1)
    Serial.print("CW");
  if(count==0)
    Serial.print("CCW");
  //BACK(speed); //move back
  FOW(speed);    //move fowward
  Serial.print(" distance ");
  Serial.println(dis);
  delay(100);
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
    count++;
  int B = digitalRead(2);
  int C = digitalRead(3);
  if(B!=C)
    dis++;
  if(B<C)
    count=0;
}
void S() 
{
  int B = digitalRead(2);
  int C = digitalRead(3);
  if(B!=C)
  dis--;
  if(B>C)
    count=1;
}
