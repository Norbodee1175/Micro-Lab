#define DATA_PIN 4
#define CLOCK_PIN 5
#define LATCH_PIN 6

int i=0;
int data;
void setup()
{
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

void loop()
{
  data=0b10000000;
  for(i=0;i<16;i++){
    
    digitalWrite(DATA_PIN, (data>>(i))&0x01);                                                                                     
    digitalWrite(CLOCK_PIN, HIGH);
    delay(100);
    digitalWrite(CLOCK_PIN, LOW);
    delay(100);
      digitalWrite(LATCH_PIN, HIGH);
    delay(10);
    digitalWrite(LATCH_PIN, LOW);
    delay(10);
  }
}
