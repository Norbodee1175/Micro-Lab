const int bit_clock_pin = 4;
const int digit_clock_pin = 3;
const int data_pin = 2;
volatile int timer= 1;
const byte digit_pattern[16] =
{
  B00111111,B00000110,B01011011,B01001111,B01100110,  
  B01101101,B01111101,B00000111,B01111111,B01101111,  
  B01110111,B01111100,B00111001,B01011110,B01111001,  
  B01110001  
};
unsigned int counter = 0;
void setup()
{
  pinMode(data_pin, OUTPUT);
  pinMode(bit_clock_pin, OUTPUT);
  pinMode(digit_clock_pin, OUTPUT);  
  
  noInterrupts();  
  TCNT1 = timer;
  TCCR1A = 0; 
  TCCR1B = 0;  
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();
}
void update_one_digit(int data)
{
  int i;
  byte pattern;
  pattern = digit_pattern[data];
  digitalWrite(digit_clock_pin, LOW);  
  shiftOut(data_pin, bit_clock_pin, MSBFIRST, ~pattern);
  digitalWrite(digit_clock_pin, HIGH);
}
void loop()
{ 
}
ISR(TIMER1_OVF_vect)
{
  TCNT1 = timer;
  int i;
  unsigned int digit_base;
  counter++;
  digit_base = 16;
  update_one_digit(counter % digit_base);
}
