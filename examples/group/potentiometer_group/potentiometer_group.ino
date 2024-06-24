/*
  Potentiometer group example
*/

#include <Arduino.h>
#include <CtrlGroup.h>
#include <CtrlPot.h>

CtrlGroup potentiometerGroup;

CtrlPot potentiometer1(24, 100, 0.05);
// CtrlPot potentiometer2(25, 100, 0.05);

void onValueChange(Groupable* potentiometer, int value) {
  auto canPrint = potentiometer->getBoolean("canPrint");
  auto id = potentiometer->getInteger("id");
  auto name = potentiometer->getString("name");
  if (canPrint) {
    Serial.print("Turned potentiometer with id: ");
    Serial.print(id);
    Serial.print(" / name: ");
    Serial.print(name);
    Serial.print(" / value: ");
    Serial.println(value);
  }
}

void setup() {
  Serial.begin(9600);

  potentiometerGroup.setOnValueChange(onValueChange);

  potentiometer1.setGroup(&potentiometerGroup);
  potentiometer1.setInteger("id", 0);
  potentiometer1.setString("name", "Potentiometer 1");
  potentiometer1.setBoolean("canPrint", true);

  // potentiometer2.setGroup(&potentiometerGroup);
  // potentiometer2.setInteger("id", 1);
  // potentiometer2.setString("name", "Potentiometer 2");
  // potentiometer2.setBoolean("canPrint", true);
}

void loop() {
  potentiometerGroup.process();
}
