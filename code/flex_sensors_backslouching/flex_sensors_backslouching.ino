#include <Servo.h>

const int FLEX_PIN = A0;
const int SERVO_PIN = 9;

Servo actuator;

int flexValue = 0;
int pushAngle = 90;    // Servo neutral angle
int maxPushAngle = 140;
int minPushAngle = 90; // No correction

void setup() {
  Serial.begin(9600);
  actuator.attach(SERVO_PIN);
  actuator.write(minPushAngle);
}

void loop() {
  flexValue = analogRead(FLEX_PIN);
  Serial.print("Flex: "); Serial.println(flexValue);

  // If posture is bad, push more
  if (flexValue > 540) {
    pushAngle = maxPushAngle;
  } else {
    pushAngle = minPushAngle;
  }

  actuator.write(pushAngle);

  delay(200);
}
