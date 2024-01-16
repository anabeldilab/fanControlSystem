#include <Arduino.h>
#include <ArduinoJson.h>
#include "DHT.h"
#include <time.h>
#include <Fuzzy.h>

#include "../include/fanControlHandler.h"
#include "../include/sensorsHandler.h"
#include "../include/lightPriceDataHandler.h"
#include "../include/fuzzyLogic.h"
#include "../include/timeManagement.h"
#include "../include/relayHandler.h"

FanMode currentFanMode = AUTO;

const int PWM_PIN = 4;
const int PWM_CHANNEL = 0; // Canal PWM
const int FREQ = 10000; // Frecuencia en Hz
const int PWM_RESOLUTION = 8; // Resolución en bits (máximo 16 bits)

float temperaturePercentage = 0.0;
float pricePercentage = 0.0;

bool clockwise = true;


void initializePWM() {
  ledcAttachPin(PWM_PIN, PWM_CHANNEL);
  ledcSetup(PWM_CHANNEL, FREQ, PWM_RESOLUTION);
  setFanSpeed(50);
}


bool isCurrentFanModeAuto() {
  return currentFanMode == AUTO;
}


bool isCurrentFanModeManual() {
  return currentFanMode == MANUAL;
}


void setFanSpeed(int speedPercentege) {
  float duty = speedPercentege * 255 / 100;
  ledcWrite(PWM_CHANNEL, duty);
}


void setFanMode(FanMode mode) {
  currentFanMode = mode;
}


void setFanSpeedManual(int speed) {
  if (currentFanMode == MANUAL) {
    setFanSpeed(speed);
  }
}


void handleFanControl() {
  if (currentFanMode == AUTO) {
    if (hasHourChanged() || pricePercentage < 0.0 || useLightMocks) {
      pricePercentage = getCurrentPricePercentage();
      updateLastHourChecked();
    }
    temperaturePercentage = getTemperaturePercentage();
    float fanSpeed = meanLogic(temperaturePercentage, pricePercentage);

    Serial.print("Temperature: ");
    Serial.print(temperaturePercentage);
    Serial.print("%, Price percentage: ");
    Serial.print(pricePercentage);
    Serial.print("%, Fuzzy result: ");
    Serial.println(fanSpeed);

    setFanSpeed(fanSpeed);
  }
}



void turnFanOff() {
  stopRelay();
}


void turnFanOn() {
  if (clockwise) {
    clockwiseRelay();
  } else {
    anticlockwiseRelay();
  }
}


void changeFanDirection() {
  clockwise = !clockwise;
  turnFanOn();
}