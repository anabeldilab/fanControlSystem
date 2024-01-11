#include "DHT.h"
#include <Wire.h> 

#include "../include/sensorsHandler.h"

const int DHT_PIN = 25;
#define DHTTYPE DHT11
DHT dhtSensor(DHT_PIN, DHTTYPE);

const int speedSensorPin = 13; 

float mockTemperature = 0;

bool useTemperatureMocks = false;

volatile unsigned long rpm = 0;
volatile unsigned long previousTime = 0;

int pulseCount = 0;

void IRAM_ATTR isr() {
  pulseCount++;
  delayMicroseconds(5);
}


void initializeDHTSensor() {
  dhtSensor.begin();
}


void initializeSpeedSensor() {
  pinMode(speedSensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(speedSensorPin), isr, FALLING);
}


float setMockTemperature(float temperature) {
  mockTemperature = temperature;
}


void useMocksTemperature(bool useMocks) {
  useTemperatureMocks = useMocks;
}


float getTemperature() {
  if (useTemperatureMocks) {
    return mockTemperature;
  }
  float temperature = dhtSensor.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return -1.0;
  }
  return temperature;
  //return mockTemperature;
}


float getTemperaturePercentage() {
  float temperature = getTemperature();
  float temperatureMin = 20;
  float temperatureMax = 35;
  if (temperature < 0) {
    return -1.0;
  }
  if (temperature < 20) {
    return 0.0;
  } else if (temperature > 35) {
    return 100.0;
  } else {
    return (temperature - temperatureMin) / (temperatureMax - temperatureMin) * 100;
  }


}



float getHumidity() {
  float humidity = dhtSensor.readHumidity();
  if (isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return -1.0;
  }
  return humidity;
}


void calculateRPM() {
  unsigned long currentTime = micros();
  unsigned long elapsedTime = currentTime - previousTime;
  // Calculate RPM (Revolutions Per Minute) and reset the counter
  rpm = ((pulseCount / 2) * 60000000) / (elapsedTime);

  previousTime = currentTime;
  pulseCount = 0;  // Reset the counter
}


int getRPM() {
  return rpm;
}


void printTemperature(float temperature) {
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
}


void printHumidity(float humidity) {
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}