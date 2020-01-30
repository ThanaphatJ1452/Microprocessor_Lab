#include <Arduino.h>

#define clk_1 2
#define clk_2 3
#define pinPotentiometer 0

unsigned short led_Position = 0; //Start Position
unsigned short clkSig_1, clkSig_2;
unsigned short key;

enum DIRECTION{left, right};
DIRECTION led_Direction = left;

void led_Sequential(unsigned short num);

void setup() {
  
  pinMode(clk_1, INPUT_PULLUP);
  pinMode(clk_2, INPUT_PULLUP);
  DDRB = 0xFF; 
  led_Sequential(led_Position);
  
}

void loop() {

  clkSig_1 = PIND & 0x04;
  clkSig_2 = PIND & 0x08;
  key = analogRead(pinPotentiometer);

  if(!clkSig_1 && led_Position < 15)
    led_Direction = left;
  else if(!clkSig_2 && led_Position > 0)
    led_Direction = right;
  
  if (led_Direction == left)
    led_Position == 15 ? led_Position = 0 : led_Position++;
  else
    led_Position == 0 ? led_Position = 15 : led_Position--;
  
  led_Sequential(led_Position);
 
}

void led_Sequential(unsigned short count)
{
    PORTB = 0x00; 
    for(unsigned short i = 0; i < 16; ++i)
    {
      i == count ? PORTB = 0x16 : PORTB = 0x00;
      PORTB = 0x20;
      PORTB = 0x00;
    }
    PORTB = 0x04; 
     delay(analogRead(pinPotentiometer));
}
