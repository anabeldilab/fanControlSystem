#include <Arduino.h>
#include <ArduinoJson.h>

#include "../include/lightPriceDataHandler.h"
#include "../include/networkHandler.h"

// URL of the API providing current light price data.
const String currentLightPriceUrl = "https://api.preciodelaluz.org/v1/prices/now?zone=PCB";
const String maxLightPriceUrl = "https://api.preciodelaluz.org/v1/prices/max?zone=PCB";
const String minLightPriceUrl = "https://api.preciodelaluz.org/v1/prices/min?zone=PCB";

float currentLightPrice = 0;
float maxLightPrice = 0;
float minLightPrice = 0;

unsigned long lastCurrentPriceUpdate = 0;
unsigned long lastMaxMinPriceUpdate = 0;

const unsigned long oneHourMillis = 3600000; // 1 hour in miliseconds
const unsigned long oneDayMillis = 86400000; // 1 day in miliseconds

float mockLightPrice = 0;
const float mockMaxLightPrice = 300;
const float mockMinLightPrice = 100;

bool useLightMocks = false;

float fetchLightPrice(const String& jsonResponse) {
  DynamicJsonDocument doc(256); // max size of JSON object
  DeserializationError error = deserializeJson(doc, jsonResponse);
  if (error) {
    Serial.print("JSON parse failed: ");
    Serial.println(error.c_str());
    return -1.0;
  }
  if (!doc.containsKey("price") || !doc["price"].is<float>()) {
    Serial.println("Price not found or is not a number");
    return -1.0;
  }
  return doc["price"].as<float>();
}


float getCurrentLightPrice() {
  if (useLightMocks) {
    return mockLightPrice;
  }
  unsigned long currentTime = millis();
  if (currentTime - lastCurrentPriceUpdate >= oneHourMillis || lastCurrentPriceUpdate == 0) {
    lastCurrentPriceUpdate = currentTime;
    String jsonResponse = httpGETRequest(currentLightPriceUrl);
    currentLightPrice = fetchLightPrice(jsonResponse);
  }
  return currentLightPrice;
}


float getMaxLightPrice() {
  if (useLightMocks) {
    return mockMaxLightPrice;
  }
  unsigned long currentTime = millis();
  if (currentTime - lastMaxMinPriceUpdate >= oneDayMillis || lastMaxMinPriceUpdate == 0) {
    lastMaxMinPriceUpdate = currentTime;
    String jsonResponse = httpGETRequest(maxLightPriceUrl);
    maxLightPrice = fetchLightPrice(jsonResponse);
  }
  return maxLightPrice;
}


float getMinLightPrice() {
  if (useLightMocks) {
    return mockMinLightPrice;
  }
  unsigned long currentTime = millis();
  if (currentTime - lastMaxMinPriceUpdate >= oneDayMillis || lastMaxMinPriceUpdate == 0) {
    lastMaxMinPriceUpdate = currentTime;
    String jsonResponse = httpGETRequest(minLightPriceUrl);
    minLightPrice = fetchLightPrice(jsonResponse);
  }
  return minLightPrice;
}


float getCurrentPricePercentage() {
  float currentLightPrice = getCurrentLightPrice();
  float maxLightPrice = getMaxLightPrice();
  float minLightPrice = getMinLightPrice();
  if (currentLightPrice < 0 || maxLightPrice < 0 || minLightPrice < 0) {
    return -1.0;
  }
  float priceRange = maxLightPrice - minLightPrice;
  float pricePercentage = (currentLightPrice - minLightPrice) / priceRange * 100;
  return pricePercentage;
}


void setMockLightPrice(float price) {
  mockLightPrice = price;
}


void useMocksLightPrice(bool useMocks) {
  useLightMocks = useMocks;
}


void printLightPrice(float price) {
  if (price >= 0) {
    Serial.print("Current Light Price: ");
    Serial.print(price);
    Serial.println(" €/MWh");
  } else {
    Serial.println("Unable to display light price.");
  }
}