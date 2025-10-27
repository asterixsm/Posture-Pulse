## How to Assemble Posture-Pulse
### 1. Gather Materials
- ESP32-C3 microcontroller
- IMU 5060
- Battery pack or power-supply module
- Vibration Motor
- Jumper Wires
- Resistors
- Neck Collar Frame
- Adjustable straps (optional)
- Heatshrink Tubing

### 2. Hardware Assembly
- Assemble the circuit as prescribed by the schematic diagram
- Secure all wires with Heatshrink tubing for safety
- Secure all components inside a wearable enclosure or onto a suitable strap so that the device sits comfortably and sensors are correctly oriented on the user's upper back.
- Connect the power supply or battery, and make sure it can run remotely.

### 3. Code Upload
- Download and install dependencies for the ESP32-C3 environment (use Arduino IDE)
- Upload the posture-monitoring firmware from the repository’s code folder to the microcontroller.
- Run the code, and the ESP32-C3 will recall the code, so there is no need for it to be constantly connected to your laptop.

### 4. Initial Calibration
- Wear the assembled device in an upright, correct posture.
- Feed the IMU readings for good posture as prescribed in the repository.
- Allow the device to record the baseline posture; finalize calibration.

### 5. Operation
- Use the device during study, work, or other periods requiring good posture.
- When slouching is detected by the IMU sensor, the vibration motor will activate to gently alert you.
- You can also use the adjustable straps to secure it in a more tight manner if you would like to.

### Maintenance & Troubleshooting
- If the vibration motor feedback does not work, check wiring, battery charge, and confirm that the correct code is the last used one. We personally experienced most problems with the wiring while testing.
- For inaccurate IMU calibration, attempt to recalibrate while it is kept straight using the prototype housing or the final.

### Licensing
- Hardware: CERN OHL-S 2.0
- Software: MIT
- Documentation: CC BY 4.0

