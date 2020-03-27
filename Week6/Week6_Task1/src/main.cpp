#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define adjustHeight 15
#define adjustWidth 20
#define cursor 20

#define display_sw_off_1 display.fillCircle((SCREEN_WIDTH/2) + adjustWidth, (SCREEN_HEIGHT/2) - adjustHeight, 11, BLACK)
#define display_sw_on_1 display.fillCircle((SCREEN_WIDTH/2) + adjustWidth, (SCREEN_HEIGHT/2) - adjustHeight, 11, WHITE)
#define display_sw_off_2 display.fillCircle((SCREEN_WIDTH/2) + adjustWidth, (SCREEN_HEIGHT/2) + adjustHeight, 11, BLACK)
#define display_sw_on_2 display.fillCircle((SCREEN_WIDTH/2) + adjustWidth, (SCREEN_HEIGHT/2) + adjustHeight, 11, WHITE)

#define sw1 2
#define sw2 3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup(){
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
  
  display.clearDisplay(); // clears the screen and buffer
  display.setTextSize(1);display.setTextColor(WHITE);
  
  display.setCursor(cursor, (SCREEN_HEIGHT/2) - adjustHeight - 5);display.println("Switch1");
  display.drawCircle((SCREEN_WIDTH/2) + adjustWidth, (SCREEN_HEIGHT/2) - adjustHeight, 12, WHITE);
  
  display.setCursor(cursor, (SCREEN_HEIGHT/2) + adjustHeight - 5);display.println("Switch2");
  display.drawCircle((SCREEN_WIDTH/2) + adjustWidth, (SCREEN_HEIGHT/2) + adjustHeight, 12, WHITE);
  
  display.display();

  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
}
void loop(){
  !digitalRead(sw1) ? display_sw_on_1 : display_sw_off_1;
  !digitalRead(sw2) ? display_sw_on_2 : display_sw_off_2;
  display.display();
}

