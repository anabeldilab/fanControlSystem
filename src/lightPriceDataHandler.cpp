#include <Arduino.h>
#include <ArduinoJson.h>

#include "../include/lightPriceDataHandler.h"

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


void printLightPrice(float price) {
  if (price >= 0) {
    Serial.print("Current Light Price: ");
    Serial.print(price);
    Serial.println(" €/MWh");
  } else {
    Serial.println("Unable to display light price.");
  }
}