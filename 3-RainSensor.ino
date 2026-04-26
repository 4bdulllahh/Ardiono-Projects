const int SENSOR_PIN = A0;
const int RED_ALARM_PIN = 3;
const int GREEN_LED_PIN = 9;

// Adjust this threshold based on your tests
// 1023 is bone dry, 0 is completely submerged
const int RAIN_THRESHOLD = 800; 

void setup() {
  Serial.begin(9600);
  pinMode(RED_ALARM_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);
  Serial.print("Moisture Level: ");
  Serial.println(sensorValue);

  if (sensorValue < RAIN_THRESHOLD) {
    // RAIN DETECTED
    digitalWrite(GREEN_LED_PIN, LOW);
    
    // Alert: Red LED and Buzzer blink
    digitalWrite(RED_ALARM_PIN, HIGH);
    tone(RED_ALARM_PIN, 1200); // Slightly higher pitch for rain
    delay(200);
    digitalWrite(RED_ALARM_PIN, LOW);
    noTone(RED_ALARM_PIN);
    delay(200);
  } else {
    // DRY
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_ALARM_PIN, LOW);
    noTone(RED_ALARM_PIN);
  }

  delay(100); 
}