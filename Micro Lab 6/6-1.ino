#define LED_PIN 11 
float brightness = 0; 
String buff; 
int a;
void setup() { 
 // put your setup code here, to run once: 
 Serial.begin(9600); 
} 
void loop() { 
 // put your main code here, to run repeatedly: 
 if (Serial.available() > 0) { 
 char inByte = Serial.read(); 
 if(inByte=='1')
 a=11;
 if(inByte=='2')
 a=10;
 if(inByte == 'B')
 buff=' ';
 if(('0'<= inByte) && (inByte <= '9')){ 
 buff += inByte; 
 } 
 if(inByte == '\n'){ 
 brightness = buff.toInt(); 
 Serial.println(brightness); 
 analogWrite(a,int(brightness*2.54));
 }
 }
}
