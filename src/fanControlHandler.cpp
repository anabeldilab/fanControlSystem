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

float temperature = 0.0;
float pricePercentage = 0.0;


void initializePWM() {
  pinMode(PWM_PIN, OUTPUT);
  setFanSpeed(0);
}


bool isCurrentFanModeAuto() {
  return currentFanMode == AUTO;
}


bool isCurrentFanModeManual() {
  return currentFanMode == MANUAL;
}


void setFanSpeed(int speedPercentege) {
  float duty = speedPercentege * 255 / 100;
  analogWrite(PWM_PIN, duty);
}


void setFanMode(FanMode mode) {
  currentFanMode = mode;
}


void setFanSpeedManual(int speed) {
  if (currentFanMode == MANUAL) {
    setFanSpeed(speed);
    Serial.print("Manual fan speed set to: ");
    Serial.println(speed);
  }
}


void handleFanControl() {
  if (currentFanMode == AUTO) {
    if (hasHourChanged() || pricePercentage < 0.0 || useLightMocks) {
      pricePercentage = getCurrentPricePercentage();
      updateLastHourChecked();
    }
    float temperature = getTemperature();
    float fanSpeed = fuzzyLogic(temperature, pricePercentage);

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Price percentage: ");
    Serial.print(pricePercentage);
    Serial.print("%, Fuzzy result: ");
    Serial.println(fanSpeed);

    if (fanSpeed < 10) {
      turnFanOff();
    } else if (fanSpeed > 90) {
      fanSpeed = 90;
    } else {
      turnFanOn();
    }
    setFanSpeed(fanSpeed);
  }
}



void turnFanOff() {
  stopRelay();
  Serial.println("Fan turned off");
}


void turnFanOn() {
  startRelay();
  Serial.println("Fan turned on");
}


void changeFanDirection() {
  reverseRelay();
  Serial.println("Fan direction changed");
}