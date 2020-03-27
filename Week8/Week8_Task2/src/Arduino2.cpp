#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial =  SoftwareSerial(13, 12);

#define LED_PIN_1 11
String buff;
float brightness = 0;

void setup()
{
  mySerial.begin(4800);
  pinMode(LED_PIN_1, OUTPUT);
}

void loop()
{
  if (mySerial.available()>0)
  {
    char inByte = mySerial.read();
    
    if (('0' <= inByte) && (inByte <= '9')){
      buff += inByte;
    }
    else if (inByte == '\n'){
      brightness = buff.toInt();
      analogWrite(LED_PIN_1, (int(brightness)) * 2.54);
      buff = "";
    }
  }
}