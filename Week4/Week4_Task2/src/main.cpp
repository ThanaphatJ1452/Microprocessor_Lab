#include <SPI.h>

#define DATA 11
#define CLK 13
#define SS 10
#define SS_2 9
#define btnIn 2
#define btnDe 3
#define btnCount 4
#define buzzer 5

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
bool flag = false;
uint8_t count = 10;

void setup(){
  Serial.begin(9600);
  pinMode(SS, OUTPUT);
  pinMode(SS_2, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(btnIn, INPUT_PULLUP);
  pinMode(btnDe, INPUT_PULLUP);
  pinMode(btnCount, INPUT_PULLUP);
  
}

void loop(){
  display_7Segment_With_Btn();
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

void display_7Segment_With_Btn(void)
{
  display_7Segment(count);
  if(flag) // flag = true
  {
    count--;
    if(!count)
    { 
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      flag = false;
    }
    if(!digitalRead(btnCount)) flag = false; 
  }
  else
  {
    if(!digitalRead(btnIn) && (count < 99)) count++;
    if(!digitalRead(btnDe) && (count > 0)) count--;
    if(!digitalRead(btnCount)  && count) flag = true;
  }

  delay(500);
}

void display_7Segment(uint8_t index)
{
  spi_2(num[index%10]); //1X
  spi_1(num[index/10]); //X1
}



