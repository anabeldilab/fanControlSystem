#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#include "../include/networkHandler.h"

const char* wifiSSID = "Redmi Note 12 Pro 5G";
const char* wifiPassword = "sonawifi";

unsigned long wifiConnectStartMillis = 0;
const unsigned long wifiConnectTimeout = 10000;


void initializeWifiConnection() {
  static long last_millis = 0;
  bool connected = false;
  while (!connected) {
    unsigned long now = millis();
    WiFi.begin(wifiSSID, wifiPassword);
    while (WiFi.status() != WL_CONNECTED && now - last_millis < 5000) {
      now = millis();
      delay(500);
      Serial.print(".");
    }
    last_millis = now;
    if (WiFi.status() == WL_CONNECTED) {
      connected = true;
    } else {
      Serial.println("\nConnection failed");
      Serial.println("Trying to reconnect");
    }
  }
  Serial.println("");
  Serial.print("Conectado a la red WiFi. IP: ");
  Serial.println(WiFi.localIP());
}


void checkWifiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    initializeWifiConnection();
  }
}


bool isConnectedToWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    return false;
  }
  return true;
}


String httpGETRequest(const String& serverName) {
  WiFiClientSecure client;
  HTTPClient http;
  int retries = 5;
  int retryDelay = 3000;

  // Because we are using a https connection
  client.setInsecure(); // Not verifying SSL/TLS certificate (not recommended)
  http.begin(client, serverName.c_str());

  while (retries > 0) {
    int httpResponseCode = http.GET();
    String payload = "{}";
    if (httpResponseCode > 0) {
      payload = http.getString();
      return payload;
    } else {
      retries--;
      Serial.println("Solicitud fallida. Reintentando...");
      delay(retryDelay);
    }
  }
  http.end();
  Serial.println("Se agotaron los reintentos. No se pudo obtener el precio.");
  return "{}";
}


void sendHttpGetRequest(const String& serverName, String& response) {
  if (isConnectedToWiFi()) {
    response = httpGETRequest(serverName);
  } else {
    Serial.println("WiFi Disconnected");
  }
}