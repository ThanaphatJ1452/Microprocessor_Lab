#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial =  SoftwareSerial(12, 13);

#define pin_input A0

void setup()
{
  mySerial.begin(4800);
  pinMode(pin_input, INPUT);
}

void loop()
{	
  mySerial.println(int((analogRead(pin_input)/1023.00)*100)); 
  delay(1000);
}