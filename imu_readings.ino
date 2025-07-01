/*
 *  Smart Posture IMU Angle Demo
 *  Board   : Seeed XIAO ESP32-C3  (I²C on GPIO 4 = SDA, GPIO 5 = SCL)
 *  Sensor  : MPU6050 (GY-521 breakout)
 *  Library : MPU6050_light  (Author: Rafael Couto, rc-github)
 */

#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

// ─────────────────────────────
void initIMU() {
  Wire.begin();                     // default SDA/SCL on ESP32-C3 pins 4/5
  Serial.println(F("Initialising MPU6050 …"));
  byte status = mpu.begin();
  if (status != 0) {
    Serial.print(F("IMU init failed. Error code ")); Serial.println(status);
    while (1);                      // stop here if not found
  }
  Serial.println(F("Calibrating – keep device still"));
  mpu.calcGyroOffsets(true);        // takes ~2 s
  Serial.println(F("Calibration done"));
}
// ─────────────────────────────
void setup() {
  Serial.begin(9600);
  delay(1000);
  initIMU();
}
// ─────────────────────────────
void loop() {
  mpu.update();                     // refresh accel & gyro data

  /* Calculate absolute pitch (using accelerometer only) */
  float ax = mpu.getAccX();
  float ay = mpu.getAccY();
  float az = mpu.getAccZ();
  float pitch = atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI;

  Serial.print(F("Pitch (deg): "));
  Serial.println(pitch, 2);

  delay(200);                       // 5 Hz output to Serial Monitor
}
