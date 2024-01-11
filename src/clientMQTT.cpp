#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <Wire.h>
#include <ArduinoJson.h>
#include <Fuzzy.h>
#include <time.h>

#include "../include/clientMQTT.h"
#include "../include/fanControlHandler.h"
#include "../include/sensorsHandler.h"
#include "../include/lightPriceDataHandler.h"

// MQTT Broker
const char *mqtt_broker = "51.20.185.180";
const char *client_id = "alu0101206011-wemos-accionamientos";
const char *mqtt_username = "alu0101206011";
const char *mqtt_password = "";
const int mqtt_port = 1883;

// MQTT Topics
const char *fanSpeedControl_topic = "/wemos/fanSpeedControl";
const char *fanControl_topic = "/wemos/fanControl";
const char *fanModeControl_topic = "/wemos/fanModeControl";
const char *lightPriceData_topic = "/wemos/lightPriceData";
const char *temperatureData_topic = "/wemos/temperatureData";
const char *rpmData_topic = "/wemos/rpmData";

const char *mockTemperature_topic = "/wemos/mockTemperature";
const char *mockLightPrice_topic = "/wemos/mockLightPrice";
const char *useMocks_topic = "/wemos/useMocks";

// Wi-Fi and MQTT Client
WiFiClient wifiClient;
PubSubClient MQTTClient(wifiClient);

void initializeMQTTConnection() {
  MQTTClient.setServer(mqtt_broker, mqtt_port);
  MQTTClient.setCallback(callback);
}


String convertPayloadToString(byte *payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  return message;
}


void callback(char *topic, byte *payload, unsigned int length) {
  //Serial.print("Topic: ");
  //Serial.println(topic);
  String message = convertPayloadToString(payload, length);
  //Serial.print("Message: ");
  //Serial.println(message);
  //Serial.print("Manual mode?: ");
  //Serial.println(isCurrentFanModeManual());

  if (strcmp(topic, fanModeControl_topic) == 0) {
    if (message == "auto") {
      setFanMode(AUTO);
    } else if (message == "manual") {
      setFanMode(MANUAL);
    }
  } else if (strcmp(topic, fanControl_topic) == 0) {
    if (message == "on") {
      turnFanOn();
    } else if (message == "off") {
      turnFanOff();
    } else if (message == "changeDirection") {
      changeFanDirection();
    }
  } else if (strcmp(topic, fanSpeedControl_topic) == 0) {
    setFanSpeedManual(message.toInt());
  } else if (strcmp(topic, mockTemperature_topic) == 0) {
    mockTemperature = message.toFloat();
  } else if (strcmp(topic, mockLightPrice_topic) == 0) {
    setMockLightPrice(message.toFloat());
  } else if (strcmp(topic, useMocks_topic) == 0) {
    if (message == "true") {
      useMocksTemperature(true);
      useMocksLightPrice(true);
    } else if (message == "false") {
      useMocksTemperature(false);
      useMocksLightPrice(false);
    }
  }
}


void publishLightPriceData(float price) {
  if (!MQTTClient.connected()) {
    establishMQTTConnection();
  }
  String priceStr = String(price, 2);  // Convert float to string with 2 decimal places
  MQTTClient.publish(lightPriceData_topic, priceStr.c_str());
}


void publishRPMData(int rpm) {
  if (!MQTTClient.connected()) {
    establishMQTTConnection();
  }
  MQTTClient.publish(rpmData_topic, String(rpm).c_str());
}


void publishTemperatureData(float temperature) {
  if (!MQTTClient.connected()) {
    establishMQTTConnection();
  }
  String temperatureStr = String(temperature, 2);
  MQTTClient.publish(temperatureData_topic, temperatureStr.c_str());
}


void establishMQTTConnection() {
  while (!MQTTClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (MQTTClient.connect(client_id, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      // Subscribe
      MQTTClient.subscribe(fanControl_topic);
      MQTTClient.subscribe(fanModeControl_topic);
      MQTTClient.subscribe(fanSpeedControl_topic);
      MQTTClient.subscribe(lightPriceData_topic);
      MQTTClient.subscribe(temperatureData_topic);

      MQTTClient.subscribe(mockTemperature_topic);
      MQTTClient.subscribe(mockLightPrice_topic);
      MQTTClient.subscribe(useMocks_topic);
    } else {
      Serial.print("failed, reconnect ");
      Serial.print(MQTTClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void checkMQTTConnection() {
  establishMQTTConnection();
}


void handleMQTTLoop() {
  if (MQTTClient.connected()) {
    MQTTClient.loop();
  } else {
    checkMQTTConnection();
  }
}