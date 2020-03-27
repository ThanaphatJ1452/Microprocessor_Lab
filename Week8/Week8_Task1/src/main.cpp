#include <Arduino.h>

#define LED_PIN_1 11
#define LED_PIN_2 3

float brightness = 0;
int pin_led, pin_on;
String buff;

void setup()
{ 
  Serial.begin(9600);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0)
  {
    char inByte = Serial.read();
    if (inByte == 'L'){
      buff = "";
    }
    else if (('0' <= inByte) && (inByte <= '9')){
      buff += inByte;
    }
    else if (inByte == 'B'){
      if(buff.toInt() == 1) { pin_on = 11; }
      if(buff.toInt() == 2) { pin_on = 5; }
      buff = "";
    }
    else if (inByte == 'N'){
      brightness = buff.toInt();
      Serial.println(brightness);
      analogWrite(pin_on, (int(brightness)) * 2.54);
    }
  }
}