#include <ESP32Servo.h>

Servo servo;
int servoPin = 18;  // Pin connected to the servo

int pos = 0;      // Current servo position
int increment = 1; // Amount to increment the servo position
int delayTime = 15; // Delay between each position increment (adjust for desired speed)

void setup() {
  servo.attach(servoPin); // Attaches the servo on the specified pin
}

void loop() {
  // Sweep from 0 to 180 degrees
  for (pos = 0; pos <= 180; pos += increment) {
    servo.write(pos);     // Set the servo position
    delay(delayTime);     // Delay to allow the servo to reach the position
  }

  // Sweep from 180 to 0 degrees
  for (pos = 180; pos >= 0; pos -= increment) {
    servo.write(pos);     // Set the servo position
    delay(delayTime);     // Delay to allow the servo to reach the position
  }
}
