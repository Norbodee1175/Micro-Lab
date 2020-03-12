#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
void setup() {
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
display.clearDisplay();
display.display();
DDRD=0xFF; 
Serial.begin(9600);
}

void loop() {
  int A=analogRead(A0);
  Serial.print(A);
  String B=Serial.readString();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print(B);
  display.display(); // actually display all of the above
  delay(100);
   
  display.clearDisplay();
}
