#include <Arduino.h>

#define a  0b00000001
#define b  0b00000010
#define c  0b00000100
#define d  0b00001000
#define e  0b00010000
#define f  0b00100000
#define g  0b01000000
#define dp 0b10000000

#define num0 a | b | c | d | e | f
#define num1 b | c
#define num2 a | b | d | e | g
#define num3 a | b | c | d | g
#define num4 b | c | f | g
#define num5 a | c | d | f | g
#define num6 a | c | d | e | f | g
#define num7 a | b | c | f
#define num8 a | b | c | d | e | f | g 
#define num9 a | b | c | d | f | g

unsigned short count = 0;
unsigned short charecter[10] = {num0, num1, num2, num3, num4, num5, num6, num7, num8, num9};
void led_Sequential(unsigned short);

void setup() {
  DDRD = 0xFF;
}

void loop() {
  led_Sequential(charecter[count]);
	count == 9 ? count = 0 : count++;
  delay(1000);    
}

void led_Sequential(unsigned short led)
{
    PORTD = 0x00; //latch off
    for(unsigned short i = 0; i < 8; ++i)
    {
      (led >> (7-i)) & 0x01 ? PORTD = 0x10 : PORTD = 0x00; // data 0b0001 0000
      PORTD = 0x04 | PORTD; //clock
      PORTD = 0x00;
    }
    PORTD = 0x08; //latch on 0b0000 1000
}