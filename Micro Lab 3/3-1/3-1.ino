int c[10]={0b11111100,0b01100000,0b11011010,0b11110010,0b01100110,
           0b10110110,0b10111110,0b11100000,0b11111110,0b11110110};
void setup()
{
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  for(int j=0;j<10;j++)
  {
    digitalWrite(10,LOW);
    delay(10);
    for(int i=0;i<8;i++)
    {
      {
      digitalWrite(9,c[j]>>(i)&0x01);
      delay(10);
      digitalWrite(11, HIGH);
      delay(10);
      digitalWrite(11, LOW);
      delay(10);
      }
    }
  digitalWrite(10, HIGH);
  delay(10);
  delay(500);
  }
}
