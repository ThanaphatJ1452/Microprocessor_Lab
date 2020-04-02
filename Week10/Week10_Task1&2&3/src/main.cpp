#include <Arduino.h>
#define enA 6
#define in1 8
#define in2 7
#define chA 3
#define chB 2

void speedControl(int);
String CW();
String CCW();

int count = 0;
bool current_A, current_B, previous_A, previous_B;

void setup()
{
  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(chA, INPUT_PULLUP);
  pinMode(chB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(chA), endcoderAnalyze, RISING);
  attachInterrupt(digitalPinToInterrupt(chB), endcoderAnalyze, RISING);

  speedControl(0);
}

void loop()
{
  speedControl(-1);
  delay(1000);
  speedControl(1);
  delay(1000);
}

void speedControl(int speed)
{
  if (speed >= 0)
  {
    analogWrite(enA, speed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else
  {
    analogWrite(enA, -1 * speed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
}

void endcoderAnalyze()
{

  current_A = digitalRead(chA);
  current_B = digitalRead(chB);

  previous_A &&current_A && !previous_B && current_B ? Serial.println(CW()) : !previous_A && current_A && previous_B && current_B ? Serial.println(CCW()) : false;

  previous_A = current_A;
  previous_B = current_B;
}

String CW()
{
  Serial.print("Count: " + String(++count) + " Direction: ");
  return "CW";
}
String CCW()
{
  Serial.print("Count: " + String(--count) + " Direction: ");
  return "CCW";
}