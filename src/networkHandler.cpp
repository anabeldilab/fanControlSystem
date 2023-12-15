#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include "../include/networkHandler.h"

const char* ssid = "Redmi Note 12 Pro 5G";
const char* password = "sonawifi"; 

void connectWifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.print("IP: ");
  Serial.println(WiFi.localIP().toString());
}


bool isConnectedToWiFi() {
  return WiFi.status() == WL_CONNECTED;
}


String httpGETRequest(const String& serverName) {
  WiFiClientSecure client;
  HTTPClient http;
  int retries = 3;
  int retryDelay = 2000;

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