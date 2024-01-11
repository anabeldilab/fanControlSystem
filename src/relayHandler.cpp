#include <Arduino.h>

const int RELAY_K1_PIN = 14;
const int RELAY_K2_PIN = 27;
const int RELAY_K3_PIN = 16;
const int RELAY_K4_PIN = 17;

void initializeRelays() {
  pinMode(RELAY_K1_PIN, OUTPUT);
  pinMode(RELAY_K2_PIN, OUTPUT);
  pinMode(RELAY_K3_PIN, OUTPUT);
  pinMode(RELAY_K4_PIN, OUTPUT);

  // Initialize relays to off (negative logic)
  digitalWrite(RELAY_K1_PIN, HIGH);
  digitalWrite(RELAY_K2_PIN, HIGH);
  digitalWrite(RELAY_K3_PIN, HIGH);
  digitalWrite(RELAY_K4_PIN, HIGH);
}

void startRelay() {
  digitalWrite(RELAY_K4_PIN, LOW);
  delay(200);
  digitalWrite(RELAY_K4_PIN, HIGH);
}

void stopRelay() {
  digitalWrite(RELAY_K2_PIN, LOW);
  delay(200);
  digitalWrite(RELAY_K2_PIN, HIGH);
}

void reverseRelay() {
  digitalWrite(RELAY_K3_PIN, LOW);
  delay(200);
  digitalWrite(RELAY_K3_PIN, HIGH);
}
