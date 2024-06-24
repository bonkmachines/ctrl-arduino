/*
  Button group example
*/

#include <Arduino.h>
#include <CtrlGroup.h>
#include <CtrlBtn.h>

CtrlGroup buttonGroup;

CtrlBtn button1(16, 15);
CtrlBtn button2(36, 15);

void onPress(Groupable* button) {
  auto canPrint = button->getBoolean("canPrint");
  auto id = button->getInteger("id");
  auto name = button->getString("name");
  if (canPrint) {
    Serial.print("Pressed button with id: ");
    Serial.print(id);
    Serial.print(" / name: ");
    Serial.println(name);
  }
}

void setup() {
  Serial.begin(9600);

  buttonGroup.setOnPress(onPress);

  button1.setGroup(&buttonGroup);
  button1.setInteger("id", 0);
  button1.setString("name", "Button 1");
  button1.setBoolean("canPrint", true);

  button2.setGroup(&buttonGroup);
  button2.setInteger("id", 1);
  button2.setString("name", "Button 2");
  button2.setBoolean("canPrint", true);
}

void loop() {
  buttonGroup.process();
}
