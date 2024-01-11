#include <Arduino.h>
#include <Fuzzy.h>

#include "../include/fuzzyLogic.h"

Fuzzy* fuzzy = new Fuzzy();

// Fuzzy sets
FuzzySet* coldTemp = new FuzzySet(0, 5, 10, 15);
FuzzySet* mildTemp = new FuzzySet(10, 20, 25, 28);
FuzzySet* hotTemp = new FuzzySet(25, 30, 35, 40);

FuzzySet* cheapPrice = new FuzzySet(0, 10, 25, 30);
FuzzySet* normalPrice = new FuzzySet(20, 30, 50, 70);
FuzzySet* expensivePrice = new FuzzySet(60, 75, 90, 100);

FuzzySet* lowFanSpeed = new FuzzySet(0, 10, 25, 35);
FuzzySet* mediumFanSpeed = new FuzzySet(25, 40, 55, 70);
FuzzySet* highFanSpeed = new FuzzySet(60, 75, 90, 100);

void initializeFuzzyLogic() {
  // In out variables
  FuzzyInput* temperature = new FuzzyInput(1);
  temperature->addFuzzySet(coldTemp);
  temperature->addFuzzySet(mildTemp);
  temperature->addFuzzySet(hotTemp);
  fuzzy->addFuzzyInput(temperature);

  FuzzyInput* price = new FuzzyInput(2);
  price->addFuzzySet(cheapPrice);
  price->addFuzzySet(normalPrice);
  price->addFuzzySet(expensivePrice);
  fuzzy->addFuzzyInput(price);

  FuzzyOutput* fanSpeed = new FuzzyOutput(1);
  fanSpeed->addFuzzySet(lowFanSpeed);
  fanSpeed->addFuzzySet(mediumFanSpeed);
  fanSpeed->addFuzzySet(highFanSpeed);
  fuzzy->addFuzzyOutput(fanSpeed);

  // Rules
  FuzzyRuleAntecedent* ifHotTempAndCheapPrice = new FuzzyRuleAntecedent();
  ifHotTempAndCheapPrice->joinWithAND(hotTemp, cheapPrice);
  FuzzyRuleConsequent* thenHighFanSpeedCheap = new FuzzyRuleConsequent();
  thenHighFanSpeedCheap->addOutput(highFanSpeed);
  FuzzyRule* rule1 = new FuzzyRule(1, ifHotTempAndCheapPrice, thenHighFanSpeedCheap);
  fuzzy->addFuzzyRule(rule1);
  

  FuzzyRuleAntecedent* ifHotTempAndNormalPrice = new FuzzyRuleAntecedent();
  ifHotTempAndNormalPrice->joinWithAND(hotTemp, normalPrice);
  FuzzyRuleConsequent* thenMediumFanSpeedNormal = new FuzzyRuleConsequent();
  thenMediumFanSpeedNormal->addOutput(mediumFanSpeed);
  FuzzyRule* rule2 = new FuzzyRule(2, ifHotTempAndNormalPrice, thenMediumFanSpeedNormal);
  fuzzy->addFuzzyRule(rule2);

  FuzzyRuleAntecedent* ifHotTempAndExpensivePrice = new FuzzyRuleAntecedent();
  ifHotTempAndExpensivePrice->joinWithAND(hotTemp, expensivePrice);
  FuzzyRuleConsequent* thenLowFanSpeedExpensive = new FuzzyRuleConsequent();
  thenLowFanSpeedExpensive->addOutput(lowFanSpeed);
  FuzzyRule* rule3 = new FuzzyRule(3, ifHotTempAndExpensivePrice, thenLowFanSpeedExpensive);
  fuzzy->addFuzzyRule(rule3);

  FuzzyRuleAntecedent* ifMildTempAndCheapPrice = new FuzzyRuleAntecedent();
  ifMildTempAndCheapPrice->joinWithAND(mildTemp, cheapPrice);
  FuzzyRuleConsequent* thenMediumFanSpeedCheap = new FuzzyRuleConsequent();
  thenMediumFanSpeedCheap->addOutput(mediumFanSpeed);
  FuzzyRule* rule4 = new FuzzyRule(4, ifMildTempAndCheapPrice, thenMediumFanSpeedCheap);
  fuzzy->addFuzzyRule(rule4);

  FuzzyRuleAntecedent* ifMildTempAndNormalPrice = new FuzzyRuleAntecedent();
  ifMildTempAndNormalPrice->joinWithAND(mildTemp, normalPrice);
  FuzzyRule* rule5 = new FuzzyRule(5, ifMildTempAndNormalPrice, thenMediumFanSpeedNormal);
  fuzzy->addFuzzyRule(rule5);

  FuzzyRuleAntecedent* ifMildTempAndExpensivePrice = new FuzzyRuleAntecedent();
  ifMildTempAndExpensivePrice->joinWithAND(mildTemp, expensivePrice);
  FuzzyRuleConsequent* thenLowFanSpeedExpensiveTemp = new FuzzyRuleConsequent();
  thenLowFanSpeedExpensiveTemp->addOutput(lowFanSpeed);
  FuzzyRule* rule6 = new FuzzyRule(6, ifMildTempAndExpensivePrice, thenLowFanSpeedExpensiveTemp);
  fuzzy->addFuzzyRule(rule6);

  FuzzyRuleAntecedent* ifColdTempAndCheapPrice = new FuzzyRuleAntecedent();
  ifColdTempAndCheapPrice->joinWithAND(coldTemp, cheapPrice);
  FuzzyRuleConsequent* thenLowFanSpeedColdCheap = new FuzzyRuleConsequent();
  thenLowFanSpeedColdCheap->addOutput(lowFanSpeed);
  FuzzyRule* rule7 = new FuzzyRule(7, ifColdTempAndCheapPrice, thenLowFanSpeedColdCheap);
  fuzzy->addFuzzyRule(rule7);

  FuzzyRuleAntecedent* ifColdTempAndNormalPrice = new FuzzyRuleAntecedent();
  ifColdTempAndNormalPrice->joinWithAND(coldTemp, normalPrice);
  FuzzyRuleConsequent* thenLowFanSpeedColdNormal = new FuzzyRuleConsequent();
  thenLowFanSpeedColdNormal->addOutput(lowFanSpeed);
  FuzzyRule* rule8 = new FuzzyRule(8, ifColdTempAndNormalPrice, thenLowFanSpeedColdNormal);
  fuzzy->addFuzzyRule(rule8);

  FuzzyRuleAntecedent* ifColdTempAndExpensivePrice = new FuzzyRuleAntecedent();
  ifColdTempAndExpensivePrice->joinWithAND(coldTemp, expensivePrice);
  FuzzyRuleConsequent* thenLowFanSpeedColdExpensive = new FuzzyRuleConsequent();
  thenLowFanSpeedColdExpensive->addOutput(lowFanSpeed);
  FuzzyRule* rule9 = new FuzzyRule(9, ifColdTempAndExpensivePrice, thenLowFanSpeedColdExpensive);
  fuzzy->addFuzzyRule(rule9);
}


float fuzzyLogic(float currentTemperature, float currentLightPricePercentage) {
  fuzzy->setInput(1, currentTemperature);
  fuzzy->setInput(2, currentLightPricePercentage);
  fuzzy->fuzzify();

  float speedFan = fuzzy->defuzzify(1);
  return speedFan;
}

float meanLogic(float currentTemperaturePercentage, float currentLightPricePercentage) {
  float speedFan = (currentTemperaturePercentage + currentLightPricePercentage) / 2;
  return speedFan;
}
