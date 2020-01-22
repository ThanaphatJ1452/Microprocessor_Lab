#define pinSwitch1 0
#define pinSwitch2 1

unsigned short ledD = 0b00000000;
unsigned short ledB = 0b00000000;

unsigned short key1;
unsigned short key2;

unsigned short led_Position = 0; //Start Position

void setup() {
  Serial.begin(9600);
  DDRD = 0b11111100; // Pin 2 - 7 Output 
  DDRB = 0b00000011; // pin 8, 9 output

  convertToBit(led_Position);  
}

void loop() {

  key1 = analogRead(pinSwitch1);
  key2 = analogRead(pinSwitch2);

  if(key1 < 500 && led_Position < 7)
  {
    led_Position++;
    //Serial.println(led_Position);
    //Serial.println("1");
  }
  if(key2 < 500 && led_Position > 0)
  {
    led_Position--;
    //Serial.println(led_Position);
    //Serial.println("2");
  }
  convertToBit(led_Position);
  delay(150);
}

void convertToBit(int num)
{
  ledD = 0b00000100;
  ledB = 0b00000001;
  
  if(num >= 0 && num <= 5)
  {
    PORTB = 0;
    ledD = ledD << num;
    PORTD = ledD;
  }
  else if(num == 6 || num == 7)
  {
    PORTD = 0;
    ledB = ledB << (num % 6);
    PORTB = ledB;
  }
}
