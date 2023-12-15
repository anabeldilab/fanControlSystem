/** Universidad de La Laguna
  * Escuela de Doctorado y Estudios de Postgrado
  * Máster Universitario en Informática Industrial y Robótica
  * Accionamientos industriales
  *
  * @file FanControlSystem.ino
  * 
  * @date 15 Dic 2023
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

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <time.h>

#include "include/networkHandler.h"
#include "include/lightPriceDataHandler.h"
#include "include/timeManagement.h"

void setup() {
  Serial.begin(115200); 
  connectWifi();
  syncTime();
}

void loop() {
  static String lastHourChecked = "";
  static float lastPrice = -1.0;

  String currentHour = getCurrentHour(); 
  Serial.print("Current hour: ");
  Serial.println(currentHour);
  Serial.print("Last hour checked: ");
  Serial.println(lastHourChecked);

  if (lastHourChecked != currentHour) {
    String jsonResponse = httpGETRequest(currentLightPriceUrl);
    //Serial.println(jsonResponse);

    float parsedLightPrice  = fetchLightPrice(jsonResponse);
    if (parsedLightPrice  > 0) {
      lastPrice = parsedLightPrice;
      lastHourChecked = currentHour;
    }
  }
  printLightPrice(lastPrice);
    
  delay(5000);
}
