#define INT_PIN1 2 //Ch A
#define INT_PIN2 3 //Ch B
#define PWM 5
#define IN1 A1
#define IN2 A2

int i,j;
int position;
double rpm;
int sp;
double fbspeed;

double proportional, integral, derivative,last_proportional, PID;
double pwm=0.0;

void setup()
{
  pinMode(INT_PIN1,INPUT_PULLUP);
  pinMode(INT_PIN2,INPUT_PULLUP);
  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(INT_PIN1),encoder_A,RISING);
  //attachInterrupt(digitalPinToInterrupt(INT_PIN1),encoder_B,RISING);
  Serial.begin(9600);
  direction(1);
  speed(1);
  
  // TIMER 1 for interrupt frequency 2 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 2 Hz increments
  OCR1A = 31249; // = 16000000 / (256 * 2) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 256 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts

}

void loop()
{
  if(Serial.available())
  {
    String a = Serial.readString();
    sp=a.toInt();
    if(sp>15)
    {
      Serial.println("Not support number greater than 15 setting to 15....");
      sp=15;
    }
    if(sp<-15)
    {
      Serial.println("Not support number greater than -15 setting to -15....");
      sp=-15;
    }
    speed(a.toInt());
    direction(a.toInt());
  }
  
}

void direction(double a)
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

void speed(double b)
{
  int a=b;
  analogWrite(PWM,absolute(a));
}

void feedbackspeed()
{
  //find a speed every 0.5s
  fbspeed = position/0.5; //convert into second
  
  rpm = (fbspeed*60*2)/5500.0;
  Serial.print(sp);
  Serial.print(" , ");
  Serial.print(PID);
  Serial.print(" , ");
  Serial.print(proportional);
  Serial.print(" , ");
  Serial.print(integral);
  Serial.print(" , ");
  Serial.print(derivative);
  Serial.print(" , ");
  Serial.println(rpm);
  position = 0;
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
    position--;
  }
  else
  {
    position++;
  }
}

ISR(TIMER1_COMPA_vect)
{
  //interrupt commands for TIMER1 here
  feedbackspeed(); //just called
  proportional= rpm-(double)sp;
  //integral+=proportional;
  derivative=proportional-last_proportional;
  PID=proportional*2+derivative*2;//+integral*0.0000001;
  pwm-=PID;
  if(pwm<1&&pwm>-1)
    pwm=1.0;
  speed(pwm);
  direction(pwm);
}
