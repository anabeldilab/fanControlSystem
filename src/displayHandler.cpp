#include <LiquidCrystal_I2C.h>

#include "../include/displayHandler.h"
#include "../include/sensorsHandler.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void initializeLCDdisplay() {
  lcd.init();
  lcd.backlight();
}


void updateLCDdisplay() {
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(int(getTemperature()));
  lcd.print("Cº");
  lcd.print(" Hum:");
  lcd.print(int(getHumidity()));
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("veloc.:");
  lcd.print(getRPM());
  lcd.print(" rpm    ");
}

