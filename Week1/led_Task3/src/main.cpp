#include <Arduino.h>
#define pinSwitch1 0
#define pinSwitch2 1
#define pinPotentiometer 2

byte ledD = 0b00000000;
byte ledB = 0b00000000;

unsigned short key1;
unsigned short key2;
unsigned short key3;

unsigned short led_Position = 0; //Start Position

enum DIRECTION{left, right}led_Direction;

void convertToBit(unsigned short num);

void setup() {
  
  Serial.begin(9600);
  DDRD = 0b11111100; // Pin 2 - 7 Output 
  DDRB = 0b00000011; // pin 8, 9 output
  led_Direction = left;
  convertToBit(led_Position);  

}

void loop() {

  key1 = analogRead(pinSwitch1);
  key2 = analogRead(pinSwitch2);
  key3 = analogRead(pinPotentiometer);

  if(key1 < 500 && led_Position < 7)
    led_Direction = left;
  else if(key2 < 500 && led_Position > 0)
    led_Direction = right;
  
  if (led_Direction == left)
    led_Position == 7 ? led_Position = 0 : led_Position++;
  else
    led_Position == 0 ? led_Position = 7 : led_Position--;
  
  convertToBit(led_Position);
  delay(analogRead(pinPotentiometer));
}

void convertToBit(unsigned short num)
{
  ledD = 0b00000100;
  ledB = 0b00000001;
  
  if(num >= 0 && num <= 5)
  {
    PORTB = 0;
    ledD = ledD << num;
    PORTD = ledD;
  }
  else if(num == 6 || num == 7)
  {
    PORTD = 0;
    ledB = ledB << (num % 6);
    PORTB = ledB;
  }
}