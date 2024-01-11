#include <Arduino.h>
#include <time.h>

#include "../include/timeManagement.h"

String lastHourChecked = "";
String lastDayChecked = "";

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


String getCurrentDay() {
  time_t now = time(nullptr);
  struct tm *timeinfo = localtime(&now);
  char dayStr[3];
  strftime(dayStr, 3, "%d", timeinfo); // "dd" Format
  return String(dayStr);
}


bool hasHourChanged() {
  String currentHour = getCurrentHour();
  //printCurrentHour(currentHour);
  //printLastHourChecked(lastHourChecked);

  if (lastHourChecked != currentHour) {
    lastHourChecked = currentHour;
    return true;
  }
  return false;
}


bool hasDayChanged() {
  String currentDay = getCurrentDay();
  //printCurrentDay(currentDay);
  //printLastDayChecked(lastDayChecked);

  if (lastDayChecked != currentDay) {
    lastDayChecked = currentDay;
    return true;
  }
  return false;
}


void updateLastHourChecked() {
  String currentHour = getCurrentHour();
  if (lastHourChecked != currentHour) {
    lastHourChecked = currentHour;
  }
}


void updateLastDayChecked() {
  String currentDay = getCurrentDay();
  if (lastDayChecked != currentDay) {
    lastDayChecked = currentDay;
  }
}


void printCurrentHour(String currentHour) {
  Serial.print("Current hour: ");
  Serial.println(currentHour);
}


void printLastHourChecked(String lastHourChecked) {
  Serial.print("Last hour checked: ");
  Serial.println(lastHourChecked);
}


void printCurrentDay(String currentDay) {
  Serial.print("Current day: ");
  Serial.println(currentDay);
}


void printLastDayChecked(String lastDayChecked) {
  Serial.print("Last day checked: ");
  Serial.println(lastDayChecked);
}