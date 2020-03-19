int toggle;
int timer = 1;
const byte ledPin = 13;
const byte interruptPin = 2;
int state =0,count=1,i=1,time=1;
void setup()
{
  noInterrupts();  // Disable allinterrupt
  TCNT1 = timer;
  TCCR1A = 0; //Reset Timer 
  TCCR1B = 0;  //inittimer 
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin),D,FALLING);
}
void loop()
{
   Serial.println(count);
}
ISR(TIMER1_OVF_vect)
{
  if(i>=time)
  {
  TCNT1 = timer;
  digitalWrite(13, toggle);
  toggle = !toggle; 
    i=0;
  }
  i++;
}
void D() 
{
  if(count==0)
  time=1;
  if(count==1)
  time=2;
  if(count==2)
  time=3;
  count++;
  if(count>2)
    count=0;
}
