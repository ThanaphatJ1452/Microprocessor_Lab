#include <Arduino.h>
#define ledPin_0 8
#define swPin 3

int toggle = 1, mode = 1;
void blink();

void setup()
{
  pinMode(ledPin_0, OUTPUT);
  pinMode(swPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(swPin), blink, FALLING);
}

void blink()
{
  mode < 3 ? mode++ : mode = 1;
}

void loop()
{
  digitalWrite(ledPin_0, toggle = !toggle);
  delay(mode * 1000);
}
