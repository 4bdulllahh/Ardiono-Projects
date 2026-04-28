#include <Servo.h>

// --- PIN DEFINITIONS ---
const int joyXPin = A0;      // Joystick X
const int joyYPin = A1;      // Joystick Y
const int joyButtonPin = 2;  // Joystick Button (Press down)
const int panServoPin = 9;   // X-Axis (180 degree motor)
const int tiltServoPin = 10; // Y-Axis (360 degree motor)
const int laserPin = 8;      // Laser / LED

Servo panServo;  
Servo tiltServo; 

// --- CALIBRATION ---
int panAngle = 90; // Start centered
int tiltStopValue = 90; // The value that forces your 360 motor to sit still

// --- STATE VARIABLES ---
bool isManualMode = true; 
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  
  panServo.attach(panServoPin);
  tiltServo.attach(tiltServoPin);
  
  pinMode(laserPin, OUTPUT);
  pinMode(joyButtonPin, INPUT_PULLUP);
  
  digitalWrite(laserPin, HIGH); // Turn laser/LED on
  
  // Center servos on boot
  panServo.write(panAngle);
  tiltServo.write(tiltStopValue); 
}

void loop() {
  // --- 1. HANDLE BUTTON PRESS (MODE SWITCHING) ---
  bool currentButtonState = digitalRead(joyButtonPin);
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    isManualMode = !isManualMode; 
    tiltServo.write(tiltStopValue); // Force Y-axis to stop during transition
    delay(200); // Debounce delay
  }
  lastButtonState = currentButtonState;

  // --- 2. MANUAL MODE (JOYSTICK) ---
  if (isManualMode) {
    int joyX = analogRead(joyXPin);
    int joyY = analogRead(joyYPin);

    // X-Axis (180 motor): Reversed for proper Left/Right
    if (joyX > 700 && panAngle < 180) panAngle++;
    if (joyX < 300 && panAngle > 0) panAngle--;
    panServo.write(panAngle);

    // Y-Axis (360 motor): Reversed for proper Up/Down
    if (joyY > 700) {
      tiltServo.write(tiltStopValue - 10); 
    } else if (joyY < 300) {
      tiltServo.write(tiltStopValue + 10); 
    } else {
      tiltServo.write(tiltStopValue);      // STOP when joystick is centered
    }
    
    delay(15); // Smoothness delay
  }

  // --- 3. AUTO MODE (FACE TRACKING) ---
  else {
    if (Serial.available() > 0) {
      int targetPan = Serial.parseInt();       // X command (position)
      int targetTiltSpeed = Serial.parseInt(); // Y command (speed)
      
      if (Serial.read() == '\n') {
        // Move 180 motor to position
        panAngle = constrain(targetPan, 0, 180);
        panServo.write(panAngle);
        
        // Write the speed command to the 360 motor
        tiltServo.write(targetTiltSpeed);
      }
    }
  }
}