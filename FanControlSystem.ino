/** Universidad de La Laguna
  * Escuela de Doctorado y Estudios de Postgrado
  * Máster Universitario en Informática Industrial y Robótica
  * Accionamientos industriales
  *
  * @file FanControlSystem.ino
  * 
  * @date 11 Jan 2023
 *  @brief Energy-Efficient Fan Controller with IoT Integration
 *
 *  This code is part of a system designed to optimize the use of a fan for energy savings 
 *  in various settings. It involves controlling a reversible motor and a speed regulator 
 *  (ATV320), integrating these components into the Internet of Things (IoT) framework. 
 *  The system dynamically adjusts the fan's operation based on real-time data inputs, such as 
 *  ambient temperature and current light price, aiming to provide optimal environmental comfort 
 *  while minimizing energy consumption. 
 * 
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <time.h>
#include <DHT.h>
#include <PubSubClient.h>
#include <Fuzzy.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "include/networkHandler.h"
#include "include/lightPriceDataHandler.h"
#include "include/timeManagement.h"
#include "include/sensorsHandler.h"
#include "include/clientMQTT.h"
#include "include/fuzzyLogic.h"
#include "include/fanControlHandler.h"
#include "include/relayHandler.h"
#include "include/displayHandler.h"


void setup() {
  Serial.begin(115200);
  initializeWifiConnection();
  initializeMQTTConnection();
  syncTime();

  initializeRelays();
  
  initializePWM();
  initializeDHTSensor();
  initializeSpeedSensor();

  initializeFuzzyLogic();
  initializeLCDdisplay();
}

void loop() {
  static int serialNumber = 0;
  unsigned long now = millis();
  static unsigned long lastMsg = 0;
  static unsigned long lastFrame = 0;
  static unsigned long lastControl = 0;

  checkWifiConnection();
  handleMQTTLoop();

  if (now - lastMsg > 10000) {
    lastMsg = now;
    Serial.println("Publicando datos...");
    publishLightPriceData(getCurrentLightPrice());
    publishTemperatureData(getTemperature());
    publishRPMData(getRPM());
  }
    
  if (now - lastFrame > 1000) {
    lastFrame = now;
    calculateRPM();
    updateLCDdisplay();
  }


  if (now - lastControl > 10000) {
    lastControl = now;
    Serial.print("¿Modo Auto?: ");
    Serial.println(isCurrentFanModeAuto());

    handleFanControl();
  }
  delay(200);
}