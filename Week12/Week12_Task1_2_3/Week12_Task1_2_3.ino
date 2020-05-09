#include <LiquidCrystal.h>

// pin motor
#define enA 5
#define in1 4
#define in2 6
#define chA 2
#define chB 13

// pin switch button
#define switchP A3
#define switchI A2
#define switchD A1
#define switchEnter 3

#define tmp A4
#define buzzer A5

bool current_A, current_B, previous_A, previous_B;
int encoderval = 0;

volatile float timer1_ovf;
volatile float currentTime, previousTime = 0, elapsedTime;
volatile int control_value, current_rpm;
float error = 0, lastError = 0, sumError = 0, rateError;

float kp = 5.0;
float ki = 0; //20.5
float kd = 0;
int setpoint = 100;

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void showLCD(void);
void enterSwitch(void){ 
    kp = map(analogRead(switchP), 0, 1023, 500, 0)/100.0;
    ki = map(analogRead(switchI), 0, 1023, 500, 0)/100.0;
    kd = map(analogRead(switchD), 0, 1023, 500, 0)/100.0;
    setpoint = map(((analogRead(tmp) - 20) * 3.04), 0, 1023, -40, 125);
  showLCD();};
void speedControl(int);
void setupInterrupts(float period);

void setup(){
    Serial.begin(9600);
    
    lcd.begin(16, 2);
    lcd.setCursor(1, 1);
    lcd.print("Enter Button..");
    
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
    
    pinMode(switchP, INPUT);
    pinMode(switchI, INPUT);
    pinMode(switchD, INPUT);
    
    pinMode(chA, INPUT_PULLUP);
    pinMode(chB, INPUT_PULLUP);
  
    pinMode(tmp, INPUT);
    pinMode(buzzer, OUTPUT);
    speedControl(1);  
  
    attachInterrupt(digitalPinToInterrupt(chA), endcoderAnalyze, RISING);
    attachInterrupt(digitalPinToInterrupt(switchEnter), enterSwitch, RISING);
}

void loop()
{
  pidControl();
}

void showLCD(void){
    String showLine1;
    
    lcd.clear();
    lcd.setCursor(4, 0);
    showLine1 = String(setpoint) + " kp:" + String(kp);
    lcd.print(showLine1);
    lcd.setCursor(1, 1);
    String showLine2 = "ki:" + String(ki) + " kd:" + String(kd);
    lcd.print(showLine2); 
}

void speedControl(int speed) {
  if(speed >= 0){
    if(speed > 255) speed = 255;
    analogWrite(enA, speed);
    digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  }
  else {
    if(speed < -255) speed = -255;
    analogWrite(enA, -1*speed);
    digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  }
}

void endcoderAnalyze() {
    if(digitalRead(chB) == HIGH){encoderval--;}
    else if(digitalRead(chB) == LOW){encoderval++;}
}

void pidControl(){
    currentTime = millis() ; //get current time 
    elapsedTime = (currentTime - previousTime)/1000.0;
    
    current_rpm = 9.55*((60*1000*10)/pulseIn(chA,HIGH));
    error = setpoint - current_rpm;
    sumError += error * elapsedTime; 
    rateError = (error - lastError)/elapsedTime;
    if(error < ((0.2)*setpoint)){digitalWrite(buzzer, HIGH); delay(500); digitalWrite(buzzer, LOW);}
    control_value = (int)(kp*error + ki*sumError + kd*rateError);
    
    lastError = error;
    previousTime = currentTime;

    Serial.println(current_rpm);
    speedControl(control_value);
    delay(1);
}
