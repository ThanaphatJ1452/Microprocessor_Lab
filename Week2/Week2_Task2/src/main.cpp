/*
  Connect 16LEDs to the Arduino board as shown in the picture and write a program to make the LED blink sequentially.
  write  the  program  to  illuminate  LED separately  and  use  the  push  switch  to  select  the  LED  for  illumination.
*/
#include <Arduino.h>

#define clk_1 2
#define clk_2 3

bool flag = true;
unsigned short clkSig_1, clkSig_2, count = 0;

void led_Sequential(unsigned short);

void setup() {
  DDRB = 0xFF;
  pinMode(clk_1, INPUT_PULLUP);
  pinMode(clk_2, INPUT_PULLUP);
}

void loop() {

  clkSig_1 = PIND & 0x04;
  clkSig_2 = PIND & 0x08;

  led_Sequential(count);

  if(!clkSig_1 && flag)
  {
    count == 15? count =0 : count++;
    flag = false;
  }
  
  else if(!clkSig_2 && flag)
  {
    count == 0? count =15 : count--;
    flag = false;
  }

  else if(clkSig_1 && clkSig_2)
    flag = true;

}

void led_Sequential(unsigned short count)
{
    PORTB = 0x00; 
    for(unsigned short i = 0; i < 16; ++i)
    {
      i == count ? PORTB = 0x08 : PORTB = 0x00; //DS
      //delay(10);
      PORTB = 0x20;
      PORTB = 0x00;
    }
    PORTB = 0x04; 
    delay(50);
}
