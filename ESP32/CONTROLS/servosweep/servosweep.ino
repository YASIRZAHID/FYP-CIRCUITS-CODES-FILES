#include <ESP32Servo.h>

// Create a servo object
Servo servo;

void setup() {
  Serial.begin(9600);

  // Attach the servo to GPIO pin 13
  servo.attach(13);

  // Set the servo range to 0-180 degrees
//  servo.writeRange(0, 180);
}

void loop() {
  // Move the servo from 0 to 180 degrees with a step of 5
  for (int angle = 0; angle <= 90; angle += 10) {
    // Set the servo angle
    servo.write(angle);

    // Print the servo angle
    Serial.print("Servo Angle: ");
    Serial.println(angle);

    delay(500);
  }

  // Move the servo from 180 to 0 degrees with a step of -5
  for (int angle = 90; angle >= 0; angle -= 10) {
    // Set the servo angle
    servo.write(angle);

    // Print the servo angle
    Serial.print("Servo Angle: ");
    Serial.println(angle);

    delay(500);
  }
}
