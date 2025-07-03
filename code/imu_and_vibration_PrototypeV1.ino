#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

const byte MOTOR_PIN = 5;        // PWM pin driving transistor
const float ALPHA    = 0.10;     // smoothing factor (0–1, lower = smoother)

// Pitch zones (integers)
const int GOOD_MIN   = 0;
const int GOOD_MAX   = 4;
const int FWD_MIN    = 20;
const int FWD_MAX    = 30;
const int BACK_MIN   = -60;
const int BACK_MAX   = -20;

float baseline = 0, emaPitch = 0;
bool  buzzing  = false;

// ─── helpers ──────────────────────────────────────────────
float rawPitchDeg() {
  float ax = mpu.getAccX();
  float ay = mpu.getAccY();
  float az = mpu.getAccZ();
  return atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
}

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);

  Serial.begin(9600);
  Wire.begin();

  if (mpu.begin() != 0) {
    Serial.println(F("MPU6050 not found – check wiring!"));
    while (1);
  }
  Serial.println(F("Calibrating… keep still"));
  mpu.calcGyroOffsets();// initialise from library

  baseline = rawPitchDeg();      // upright reference
  emaPitch = 0;                  // init filter
  Serial.print(F("Baseline = ")); Serial.println(baseline, 1);
}

void loop() {
  mpu.update();

  float relPitch = rawPitchDeg() - baseline;
  // Exponential moving average
  emaPitch = ALPHA * relPitch + (1 - ALPHA) * emaPitch;

  // Round to nearest whole degree
  int pitchDeg = (int)round(emaPitch);

  // Debug every 300 ms
  static unsigned long t0 = 0;
  if (millis() - t0 > 300) {
    Serial.print(F("Pitch_raw=")); Serial.print(relPitch, 1);
    Serial.print(F("  Pitch_filt=")); Serial.print(emaPitch, 1);
    Serial.print(F("  Rounded=")); Serial.println(pitchDeg);
    t0 = millis();
  }

  // Bad-posture test with integers
  bool bad = (pitchDeg >= FWD_MIN  && pitchDeg <= FWD_MAX) ||
             (pitchDeg >= BACK_MIN && pitchDeg <= BACK_MAX);

  if (bad && !buzzing) {
    digitalWrite(MOTOR_PIN, LOW);   // ON
    buzzing = true;
  }
  else if (!bad && buzzing) {
    digitalWrite(MOTOR_PIN, HIGH);     // OFF
    buzzing = false;
  }

  delay(30);                       // 30 Hz loop
}
