#define LED_PIN 9
#define INT_PIN 2

int mode = 1;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INT_PIN),ISR_Callback,RISING);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(LED_PIN,HIGH);
  delay(mode*1000);
  digitalWrite(LED_PIN,LOW);
  delay(mode*1000);
}

void ISR_Callback()
{
  if(mode<3)
  {
    mode = mode + 1;
  }
  else
  {
    mode = 1;
  }
    
}
