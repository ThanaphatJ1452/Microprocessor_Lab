#include <Arduino.h>

int clk_pin=2;//SHCP
int latch_pin=3;//STCP
int data_pin=4;//DS
unsigned short count = 0;

void setLed(uint8_t);
void led_Sequential(unsigned short);
uint8_t number[10][8] = {
                          {0, 1, 1 ,1, 1, 1, 1, 0}, //0
                          {0, 1, 1, 0, 0, 0, 0, 0}, //1
                          {1, 0, 1, 1, 0, 1, 1, 0}, //2  {g, c, b, a, f, e, d}
                          {1, 1, 1, 1, 0, 0, 1, 0}, //3
                          {1, 1, 1, 0, 1, 0, 0, 0}, //4
                          {1, 1, 0, 1, 1, 0, 1, 0}, //5
                          {1, 1, 0, 1, 1, 1, 1, 0}, //6
                          {0, 1, 1, 1, 0, 0, 0, 0}, //7
                          {1, 1, 1, 1, 1, 1, 1, 0}, //8
                          {1, 1, 1, 1, 1, 0, 1, 0}  //9
};
int number_1[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; 

void setup() {
  Serial.begin(9600);
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
  DDRB = 0xFF;
}

void loop() {

  for(int i = 0; i < 10; i++){
    led_Sequential(i);
    //setLed(number_1[i]);
    Serial.println(i);
    delay(500);
  }
}

void led_Sequential(unsigned short count)
{
    PORTB = 0x00; 
    for(unsigned short i = 0; i < 8; i++)
    {
      number[count][7-i] ? PORTB = 0x08 : PORTB = 0x00;
      PORTB = 0x20;
      PORTB = 0x00;
    }
    PORTB = 0x04; 
    delay(50);
}

void setLed(uint8_t state)
{
  digitalWrite(latch_pin,LOW);
  for(int i = 0;i<8;i++){
    digitalWrite(data_pin,(state>>(7-i)) &0x01);
    digitalWrite(clk_pin,HIGH);
    digitalWrite(clk_pin,LOW);
    }
  digitalWrite(latch_pin,HIGH);
}