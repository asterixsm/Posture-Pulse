#include <Servo.h>

const byte FLEX_PIN  = A0;   // Analog pin
const byte SERVO_PIN = 9;    // PWM pin for servo signal

const int  THRESHOLD = 300;  // Flex ADC limit to trigger actuator
const byte SAMPLES   = 10;   // Moving-average window

// Servo angles (tune for your actuator)
const int RETRACT_ANGLE = 90;   // upright / rest
const int EXTEND_ANGLE  = 140;  // push posture

Servo actuator;
bool isExtended = false;

void setup() {
  Serial.begin(9600);
  actuator.attach(SERVO_PIN);
  actuator.write(RETRACT_ANGLE);     // Start retracted
}

void loop() {
  // ── Smooth the flex reading ──
  long sum = 0;
  for (byte i = 0; i < SAMPLES; i++) {
    sum += analogRead(FLEX_PIN);
    delay(3);                       // 3 ms between samples
  }
  int flexAvg = sum / SAMPLES;

  Serial.print("Flex = ");
  Serial.println(flexAvg);

  // ── Decide actuator position ──
  if (flexAvg > THRESHOLD && !isExtended) {
    actuator.write(EXTEND_ANGLE);
    isExtended = true;
    Serial.println("Actuator: EXTEND");
  }
  else if (flexAvg <= THRESHOLD && isExtended) {
    actuator.write(RETRACT_ANGLE);
    isExtended = false;
    Serial.println("Actuator: RETRACT");
  }

  delay(100);                       // main loop ≈10 Hz
}
