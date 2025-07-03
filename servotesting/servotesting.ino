#include <Servo.h>
Servo test;

void setup() {
  test.attach(9);
  Serial.begin(9600);
  test.write(-180);
}

void loop() {
  // Sweep 0→180° and back
  
  for (int angle = 0; angle <= 160; angle += 5) {
    test.write(angle);
    delay(30);
  }
  
}
