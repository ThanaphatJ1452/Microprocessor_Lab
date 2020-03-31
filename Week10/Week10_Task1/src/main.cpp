#include <Arduino.h>

#define enA 6
#define in1 8
#define in2 7

void speedControl(int speed);

void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void loop()
{
  speedControl(100);
}

void speedControl(int speed)
{
  if (speed >= 0)
  {
    analogWrite(enA, speed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else if (speed < 0)
  {
    analogWrite(enA, -1 * speed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
}