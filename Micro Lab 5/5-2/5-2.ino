#include <DS1302.h>
 
// Init the DS1302
DS1302 rtc(2, 3, 4);
 
// Init a Time-data structure
Time t;
 
void setup()
{
// Set the clock to run-mode, and disable the write protection
rtc.halt(false);
rtc.writeProtect(false);
 
// Setup Serial connection
Serial.begin(9600);
 
// The following lines can be commented out to use the values already stored in the DS1302
 //rtc.setDOW(THURSDAY); // Set Day-of-Week to FRIDAY
 rtc.setTime(0,0,0); // Set the time to 12:00:00 (24hr format)
 //rtc.setDate(20,2,2020); // Set the date to August 6th, 2010
}
 
void loop()
{
//// Get data from the DS1302'
Serial.print("start!!");
delay(60000);
Serial.print("stop!!");
}
// 
//// Send date over serial connection
//Serial.print("Today is the ");
//Serial.print(t.date, DEC);
//Serial.print("Day,");
//Serial.print(rtc.getMonthStr());
//Serial.print(" Month,");
//Serial.print(t.year, DEC);
//Serial.println(" year");
// 
//// Send Day-of-Week and time
//Serial.print(t.hour, DEC);
//Serial.print(" hour,");
//Serial.print(t.min, DEC);
//Serial.print(" minute,");
//Serial.print(t.sec, DEC);
//Serial.println(" second");
//Serial.println(t.sec);
// 
//// Send a divider for readability
//Serial.println(" - - - - - - - - - - - - - - - - - - - - -");
// 
//// Wait one second before repeating :)
//delay (1000);
//}
