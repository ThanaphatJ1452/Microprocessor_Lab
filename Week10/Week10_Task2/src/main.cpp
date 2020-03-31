#include <Arduino.h>

#define enA 6
#define in1 8
#define in2 7
#define chA 3

volatile float timer1_ovf;
void speedControl(int speed);
void setupInterrupts(int period);

void setup()
{
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(chA, INPUT);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  setupInterrupts(1);
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

void setupInterrupts(int period)
{
  TCCR1A = 0; // initialize timer1
  TCCR1B = 0; //mode 0

  TCCR1B |= (1 << CS12);  // prescaler 256
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  timer1_ovf = 65535 - (period / 0.000016);
  //Serial.println(timer1_ovf);
  TCNT1 = int(timer1_ovf); // preload timer

  sei(); //Global Interrupt
}

ISR(TIMER1_OVF_vect)
{
  TCNT1 = timer1_ovf;
  Serial.println(analogRead(chA));
}