#include <Arduino.h>

byte ledD = 0b00000000;
byte ledB = 0b00000000;

unsigned short led_Position = 0; //Start Position

void setup() {
  Serial.begin(9600);
  DDRD = 0b11111100; // Pin 2 - 7 Output 
  DDRB = 0b00000011; // pin 8, 9 output
  convertToBit(led_Position);
  delay(250);  
}

void loop() {
  led_Position == 7 ? led_Position = 0 : led_Position++;
  convertToBit(led_Position);
  delay(250);
}

void convertToBit(int num)
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