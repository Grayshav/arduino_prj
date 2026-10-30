#include <Arduino.h>

// put function declarations here:
const int LED_PIN = 13;
const int firstLed = 8;
const int secondLed = 9;
const int waterPower = 7;
const int waterLevel = A5;

// Functtion Declarations
int analogLevel(int samples = 10);
float waterHeight();
void LedControl(float height);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(firstLed, OUTPUT);
  pinMode(secondLed, OUTPUT);
  pinMode(waterPower, OUTPUT);
  pinMode(waterLevel, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(waterPower, HIGH);
  delay(50);
  Serial.print("Analog Value: ");
  Serial.println(analogLevel());
  digitalWrite(waterPower, LOW);
  delay(100);
  Serial.print("Water Height: ");
  Serial.println(waterHeight());
  LedControl(waterHeight());
  delay(5000);
}

// put function definitions here:

int analogLevel(int samples) {
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(waterLevel);
    delay(10);
  }
  return sum / samples;
}


float waterHeight() {
  int level = analogLevel();
  float height = (level * 5.0) / 1023.0; // Convert to voltage
  return height;
}

void LedControl(float height) {
  digitalWrite(firstLed, height > 1.0 ? HIGH : LOW);
  digitalWrite(secondLed, height > 3.0 ? HIGH : LOW);
}