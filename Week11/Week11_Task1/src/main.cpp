#include <Arduino.h>
#define enA 6
#define in1 7
#define in2 8
#define chA 3
#define chB 2
#define setpoint 100
#define kp 0.1000
#define ki 20.500
#define kd 0.000

void speedControl(int);
String CW();
String CCW();

int encoderval = 0;
bool current_A, current_B, previous_A, previous_B;

volatile float timer1_ovf;
void setupInterrupts(float period);

int control_value, current_rpm;
volatile float currentTime, previousTime = 0, elapsedTime;
float error = 0, lastError = 0, sumError = 0, rateError;

void setup()
{
  	Serial.begin(9600);
  
  	pinMode(enA, OUTPUT);
  	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
  
  	pinMode(chA, INPUT_PULLUP);
  	pinMode(chB, INPUT_PULLUP);
  
  	attachInterrupt(digitalPinToInterrupt(chA), endcoderAnalyze, RISING);
  
  	setupInterrupts(0.01);
}

void loop()
{
  //pidControl();
  //speedControl(10);
  //Serial.println(encoderval);
}
void serialReadSpeed()
{
  if(Serial.available() > 0)
  {
    String speed = Serial.readString();
    speedControl(speed.toInt());
  }
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
  	if(digitalRead(chB) == HIGH){encoderval++;}
  	else if(digitalRead(chB) == LOW){encoderval--;}
}

void pidControl(){
  	currentTime = millis() ; //get current time 
  	elapsedTime = (currentTime - previousTime)/1000.0;
  	
  	error = setpoint - encoderval;
  	sumError += error * elapsedTime;
    rateError = (error - lastError)/elapsedTime;
  	
  	control_value = (int)(kp*error + ki*sumError + kd*rateError);
  	
  	lastError = error;
  	previousTime = currentTime;

  	Serial.println(encoderval);
  	speedControl(control_value);
  	delay(1);
}

void setupInterrupts(float period)
{
  TCCR1A = 0; // initialize timer1
  TCCR1B = 0; //mode 0

  TCCR1B |= (1 << CS12);  // prescaler 256
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  timer1_ovf = 65535 - (period / 0.000016);
  TCNT1 = uint16_t(timer1_ovf); // preload timer
  
  sei(); //Global Interrupt
}

ISR(TIMER1_OVF_vect)
{
  	currentTime = millis() ; //get current time 
 	elapsedTime = (currentTime - previousTime)/1000.0;
  	
  	current_rpm = int((encoderval*60.0)/(229.0 * elapsedTime));
  	
  	error = setpoint - current_rpm;
  	sumError += error * elapsedTime;
    rateError = (error - lastError)/elapsedTime;
  	
  	control_value = (int)(kp*error + ki*sumError + kd*rateError);
  	
  	lastError = error;
  	previousTime = currentTime;
	Serial.println(current_rpm);
  	
  	speedControl(control_value);
  	
  	encoderval = 0;
  	TCNT1 = uint16_t(timer1_ovf);
}
