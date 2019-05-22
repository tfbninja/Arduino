#include <pitches.h>

int buzzerPin = 8; // buzzer pin (woah)

int min = 31;
int max = 4978;
int bigMultiplier = 4;
int smallMultiplier = 1;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int vX = analogRead(A0);
  int vY = analogRead(A1);
  int button = analogRead(A2);
  Serial.print("x: ");
  Serial.println(vX);
  Serial.print("y: ");
  Serial.println(vY);
  Serial.print("b: ");
  Serial.println(button);
  if (button == 0) {
    noTone(buzzerPin);
  } else {
    tone(buzzerPin, vX * bigMultiplier + vY * smallMultiplier);
  }
  delay(1);
}
