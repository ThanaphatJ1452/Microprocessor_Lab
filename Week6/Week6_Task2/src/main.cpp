#include <Arduino.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define adjustHeight 15
#define cursor_height_1 20
#define cursor_width_1 50
#define cursor_height_2 40
#define cursor_width_2 40

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

ThreeWire myWire(8, 9, 10); // IO, SCLK, CE
RtcDS1302<ThreeWire> 
Rtc(myWire);

void displayDate(const RtcDateTime& dt)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(cursor_width_2, cursor_height_1);
  display.print(String(dt.Day()) + " / " + String(dt.Month()) + " / " + String(dt.Year()));

  display.setCursor(cursor_width_2, cursor_height_2);
  display.print(String(dt.Hour()) + " : " + String(dt.Minute()) + " : " + String(dt.Second()));
  
  display.display();    
}

void setup() 
{
  Serial.begin(9600);
  Rtc.Begin();
  RtcDateTime setting_time(2020, 3, 9, 15, 35, 10);// year, month, dayOfMonth, hour, minute, second
  Rtc.SetDateTime(setting_time);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
  display.clearDisplay(); // clears the screen and buffer
  display.display();
 }
void loop() 
{
  RtcDateTime now = Rtc.GetDateTime();
  displayDate(now);
  delay(1000);
}