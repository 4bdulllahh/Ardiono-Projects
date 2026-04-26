const int potPin = A4; // Potentiometer middle pin
const int greenLED = A1;
const int yellowLED = A2;
const int redLED = A3;

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(potPin);
  Serial.println(sensorValue); // Helpful for debugging the knob position

  // Green LED lights up first (low power)
  if (sensorValue > 250) {
    digitalWrite(greenLED, HIGH);
  } else {
    digitalWrite(greenLED, LOW);
  }

  // Yellow LED lights up second (medium power)
  if (sensorValue > 600) {
    digitalWrite(yellowLED, HIGH);
  } else {
    digitalWrite(yellowLED, LOW);
  }

  // Red LED lights up last (high power)
  if (sensorValue > 900) {
    digitalWrite(redLED, HIGH);
  } else {
    digitalWrite(redLED, LOW);
  }
}