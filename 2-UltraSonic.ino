// Constants
const int TRIG_PIN = 6;
const int ECHO_PIN = 7;
const int RED_ALARM_PIN = 3;   // Red LED and Buzzer
const int GREEN_LED_PIN = 9;   // Green Status LED
const int DISTANCE_THRESHOLD = 50; 

float duration_us, distance_cm;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RED_ALARM_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
  // 1. Measure Distance
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.017 * duration_us;

  // 2. Logic for LEDs and Buzzer
  if (distance_cm > 0 && distance_cm < DISTANCE_THRESHOLD) {
    // Person detected: Green OFF, Red/Buzzer BLINK
    digitalWrite(GREEN_LED_PIN, LOW);
    
    // Blink 4 times a second = 250ms per cycle (125ms ON, 125ms OFF)
    for(int i = 0; i < 2; i++) { // Run twice to fill the ~500ms loop timing
      digitalWrite(RED_ALARM_PIN, HIGH);
      tone(RED_ALARM_PIN, 1000); // Only works if buzzer is on this pin
      delay(125);
      
      digitalWrite(RED_ALARM_PIN, LOW);
      noTone(RED_ALARM_PIN);
      delay(125);
    }
  } 
  else {
    // No detection: Green ON, Red/Buzzer OFF
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_ALARM_PIN, LOW);
    noTone(RED_ALARM_PIN);
  }

  // Debugging
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(100); // Small delay for stability
}