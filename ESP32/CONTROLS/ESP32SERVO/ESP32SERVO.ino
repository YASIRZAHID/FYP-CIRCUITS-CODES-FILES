#include <ESP32Servo.h>

static const int AirServoPin = 18; 
static const int GasServoPin = 19; // confirm esp32 pwm pins

Servo AirServo;
Servo GasServo;

void setup() {
  // put your setup code here, to run once:
 AirServo.attach(AirServoPin);
 GasServo.attach(GasServoPin);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  int AngleVlue = 0;   // range is 0 to 180
  AirServo.write(AngleVlue);
  GasServo.write(AngleVlue);
 
}
