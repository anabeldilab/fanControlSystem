#include <Arduino.h>
#include <time.h>


void syncTime() {
  // GMT+1 (Madrid)
  configTime(3600, 0, "pool.ntp.org", "time.nist.gov");
  Serial.print("Sincronizando hora");
  while (time(nullptr) < 100000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nHora sincronizada");
  time_t now = time(nullptr);
  Serial.println(ctime(&now));
}


String getCurrentHour() {
  time_t now = time(nullptr);
  struct tm *timeinfo = localtime(&now);
  char hourStr[3];
  strftime(hourStr, 3, "%H", timeinfo); // "HH" Format // "HH-MM" "%H-%M"
  return String(hourStr);
}