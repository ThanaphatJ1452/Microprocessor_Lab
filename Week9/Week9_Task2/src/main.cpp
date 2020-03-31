#include <Arduino.h>

#define ledPin_0 8
#define swPin 3

volatile float timer1_ovf;
void setupInterrupts(int period);
int toggle = 1;

void setup()
{
  pinMode(ledPin_0, OUTPUT);
  pinMode(swPin, INPUT_PULLUP);
  setupInterrupts(1);
}

void loop()
{
}

void setupInterrupts(int period)
{
  TCCR1A = 0; // initialize timer1
  TCCR1B = 0; //mode 0

  TCCR1B |= (1 << CS12);  // prescaler 256
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  timer1_ovf = 65535 - (period / 0.000016);
  TCNT1 = int(timer1_ovf); // preload timer

  sei(); //Global Interrupt
}

ISR(TIMER1_OVF_vect)
{
  TCNT1 = timer1_ovf;
  digitalWrite(ledPin_0, toggle = !toggle);
}