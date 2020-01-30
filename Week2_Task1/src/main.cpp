/*
  Connect 16 LEDsto the Arduino board as shown in the picture and write a program to make the LED blink sequentially.
*/
#include <Arduino.h>

unsigned short count = 0;

void led_Sequential(unsigned short);

void setup() {
  DDRB = 0xFF;
}

void loop() {
  led_Sequential(count);
  count == 15 ? count = 0 : count++;
}

void led_Sequential(unsigned short count)
{
    PORTB = 0x00; 
    for(unsigned short i = 0; i < 16; ++i)
    {
      i == count ? PORTB = 0x08 : PORTB = 0x00;
      PORTB = 0x20;
      PORTB = 0x00;
    }
    PORTB = 0x04; 
    delay(50);
}
