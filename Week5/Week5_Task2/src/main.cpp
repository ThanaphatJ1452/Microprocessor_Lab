
/*
 * The different between time from program and from timer clock is only 0.10 sec. 
 * I think it happens because of the time which using between the program
 * but it is very little so it might not be recognize 
 * 
 * Thanaphat Jiamcharoendet 61011452
 * 
 */

#include <Arduino.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>

#define led 3

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> 
Rtc(myWire);
RtcDateTime now_ini;
unsigned int count = 0, second = 0;

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
  //printDateTime(setting_time);//Try to comment This line
  Rtc.SetDateTime(setting_time);
  pinMode(led, OUTPUT);
  now_ini = Rtc.GetDateTime();
  second = now_ini.Second();
  Serial.println("Start");
  printDateTime(now_ini);
}
void loop() 
{
  RtcDateTime now = Rtc.GetDateTime();
  if(now.TotalSeconds() >= now_ini.TotalSeconds() + 120)
  {
    Serial.println("End");
    printDateTime(now);
    digitalWrite(led, LOW);
  }
  else
  {
    now.Second()%2 ? digitalWrite(led, HIGH) : digitalWrite(led, LOW);  
  }
  delay(50);
}