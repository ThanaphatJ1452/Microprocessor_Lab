#include <Arduino.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>

#define led 3
ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> 
Rtc(myWire);

void printDateTime(const RtcDateTime& dt)
{
  Serial.print(dt.Year(), DEC);
  Serial.print('/');
  Serial.print(dt.Month(), DEC);
  Serial.print('/');
  Serial.print(dt.Day(), DEC);
  Serial.print(' ');
  Serial.print(dt.Hour(), DEC);
  Serial.print(':');
  Serial.print(dt.Minute(), DEC);
  Serial.print(':');
  Serial.print(dt.Second(), DEC);
  Serial.println();
  Serial.print("Total Seconds since 1/1/2000 : ");
  Serial.print(dt.TotalSeconds());
  Serial.println();
}

void setup() 
{
  Serial.begin(9600);
  Rtc.Begin();
  RtcDateTime setting_time(2020,2,2,23,31,10);// year, month, dayOfMonth, hour, minute, second
  printDateTime(setting_time);//Try to comment This line
  Rtc.SetDateTime(setting_time);
  pinMode(led, OUTPUT);
}
void loop() 
{
  RtcDateTime now = Rtc.GetDateTime();
  now.Second()%2 ? digitalWrite(led, HIGH) : digitalWrite(led, LOW);
  printDateTime(now);
  delay(1000);
}