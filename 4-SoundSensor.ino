const int SOUND_PIN = 2;   // Sound sensor DO connected here
const int GREEN_LED = 9;   // Green LED connected here

void setup() {
  pinMode(SOUND_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  
  // Start with the light off
  digitalWrite(GREEN_LED, LOW);
}

void loop() {
  // Read the sound sensor
  int sensorState = digitalRead(SOUND_PIN);

  // If a sound is detected (HIGH)
  if (sensorState == HIGH) {
    digitalWrite(GREEN_LED, HIGH); // Turn light ON
    delay(300);                    // Stay on for 300ms
    digitalWrite(GREEN_LED, LOW);  // Turn light OFF
    
    // Brief pause to prevent the echo of the clap 
    // from triggering the light again immediately
    delay(100); 
  }
}