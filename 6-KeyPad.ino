#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

// LED Pins (Change these to match your current wiring)
const int greenLED = A1; 
const int redLED = A3; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String inputCode = "";
String secretCode = "5867"; 

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (inputCode == secretCode) {
        // Correct: Green LED blinks
        digitalWrite(greenLED, HIGH);
        delay(1000);
        digitalWrite(greenLED, LOW);
      } else {
        // Wrong: Red LED blinks
        digitalWrite(redLED, HIGH);
        delay(1000);
        digitalWrite(redLED, LOW);
      }
      inputCode = ""; 
    } 
    else if (key == '*') {
      inputCode = "";
      // Quick double blink on Red to show it's cleared
      digitalWrite(redLED, HIGH); delay(100); digitalWrite(redLED, LOW);
      delay(100);
      digitalWrite(redLED, HIGH); delay(100); digitalWrite(redLED, LOW);
    }
    else {
      inputCode += key;
    }
  }
}