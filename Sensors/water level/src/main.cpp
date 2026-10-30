#include <Arduino.h>

// put function declarations here:
const byte LED[] = {8, 9};
const int LED_PIN = 13;
const int waterPower = 7;
const byte waterLevel[] = {A3, A4, A5};
const byte testSensor = 6;

// Functtion Declarations
int analogLevel(int samples = 10, byte sensorNumber = A3);
float waterHeight(byte sensorNumber);
void LedControl(float height);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  for (int i = 0; i < 2; i++) {
    pinMode(LED[i], OUTPUT);
  }
  pinMode(waterPower, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(waterLevel[i], INPUT);
  }
  pinMode(testSensor, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(waterPower, HIGH);
  delay(50);
  for (byte i = 0; i < sizeof(waterLevel)/sizeof(waterLevel[0]); i++) {
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(analogLevel(10, waterLevel[i]));
    delay(200);
    Serial.print("Water Height: ");
    Serial.println(waterHeight(waterLevel[i]));
    LedControl(waterHeight(waterLevel[i]));
    delay(200);
  }
  Serial.print("Test Sensor: ");
  Serial.println(digitalRead(testSensor));
  digitalWrite(waterPower, LOW);

  delay(5000);
}

// put function definitions here:

int analogLevel(int samples, byte sensorNumber) {
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(sensorNumber);
    delay(10);
  }
  return sum / samples;
}


float waterHeight(byte sensorNumber) {
  int level = analogLevel(10, sensorNumber);
  float height = (level * 5.0) / 1023.0; // Convert to voltage
  return height;
}

void LedControl(float height) {
  for (int i = 0; i < 2; i++) {
    digitalWrite(LED[i], height > (i * 1.0 + 1.0) ? HIGH : LOW);
  }
}