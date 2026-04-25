// Pins
int indicatorPin = 3;  // Formerly ledPin3
int red = 12;          
int yellow = 11;       
int green = 10;        

void setup() {
  pinMode(indicatorPin, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
}

void loop() {
  // 1. GREEN PHASE: 5 seconds solid
  digitalWrite(green, HIGH);
  delay(5000); 
  
  // 2. GREEN TRANSITION: 2 seconds blinking
  blinkLED(green, 2); 
  digitalWrite(green, LOW); // Ensure green is fully OFF before yellow starts

  // 3. YELLOW TRANSITION: 2 seconds blinking
  blinkLED(yellow, 2); 
  digitalWrite(yellow, LOW); // Ensure yellow is fully OFF before red starts

  // 4. RED PHASE: 6 seconds solid
  digitalWrite(red, HIGH);
  delay(6000);
  digitalWrite(red, LOW);
  
  // Simple indicator on Pin 3 to show the loop is restarting
  digitalWrite(indicatorPin, HIGH);
  delay(100);
  digitalWrite(indicatorPin, LOW);
}

// --- Helper function for the 3 blinks per second math ---
void blinkLED(int pin, int seconds) {
  // 3 blinks per second means 6 state changes (High/Low) per second
  // Each cycle is ~333ms (166ms On, 167ms Off)
  int totalBlinks = seconds * 3; 
  for (int i = 0; i < totalBlinks; i++) {
    digitalWrite(pin, HIGH);
    delay(166);
    digitalWrite(pin, LOW);
    delay(167);
  }
}