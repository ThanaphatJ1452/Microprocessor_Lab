#include <Arduino.h>

#include <SPI.h>

#define DATA_PIN 11
#define CLOCK_PIN 13
#define SS_PIN_1 10

volatile float timer1_ovf;
int count = 0;
void setupInterrupts(int period);

int map7seg[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void spi_write_1(unsigned char cData)
{
  Serial.begin(9600);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite(SS_PIN_1, HIGH);
  digitalWrite(SS_PIN_1, LOW);
}

void setup()
{
  Serial.begin(9600);
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

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
  spi_write_1(map7seg[count++]);
  count %= 10;
}