#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);           // Connect servo signal to D9
  Serial.begin(9600);
  Serial.println("Servo Test Starting...");
}

void loop() {
  // Sweep from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos += 5) {
    myServo.write(pos);
    delay(200);
  }

  // Sweep back from 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos -= 5) {
    myServo.write(pos);
    delay(200);
  }

  delay(1000); // Pause before next cycle
}
