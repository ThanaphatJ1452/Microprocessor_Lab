#include <SPI.h>

#define DATA 11
#define CLK 13
#define SS 10
#define SS_2 9

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

unsigned char num[10] = {num0, num1, num2, num3, num4, num5, num6, num7, num8, num9};
uint8_t count = 0;

void setup(){
  pinMode(SS, OUTPUT);
  pinMode(SS_2, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLK, OUTPUT);
}

void loop(){
  display_7Segment(count);
  count == 99 ? count = 0 : count++;
  delay(1000);
}

void spi_1(unsigned char cData){
  shiftOut(DATA, CLK, MSBFIRST, cData);
  digitalWrite(SS, HIGH);
  digitalWrite(SS, LOW);
  digitalWrite(SS_2, LOW);
  digitalWrite(SS_2, LOW);
}

void spi_2(unsigned char cData){
  shiftOut(DATA, CLK, MSBFIRST, cData);
  digitalWrite(SS, LOW);
  digitalWrite(SS, LOW);
  digitalWrite(SS_2, HIGH);
  digitalWrite(SS_2, LOW);
}

void display_7Segment(uint8_t index)
{
  spi_2(num[index%10]); //1X
  spi_1(num[index/10]); //X1
}
