/*
  Rotary encoder group example
*/

#include <Arduino.h>
#include <CtrlGroup.h>
#include <CtrlEnc.h>

CtrlGroup encoderGroup;

CtrlEnc encoder1(33, 34);

void onTurnLeft(Groupable* encoder) {
  auto canPrint = encoder->getBoolean("canPrint");
  auto id = encoder->getInteger("id");
  auto name = encoder->getString("name");
  if (canPrint) {
    Serial.print("Turn left enocder with id: ");
    Serial.print(id);
    Serial.print(" / name: ");
    Serial.println(name);
  }
}

void onTurnRight(Groupable* encoder) {
  auto canPrint = encoder->getBoolean("canPrint");
  auto id = encoder->getInteger("id");
  auto name = encoder->getString("name");
  if (canPrint) {
    Serial.print("Turn right enocder with id: ");
    Serial.print(id);
    Serial.print(" / name: ");
    Serial.println(name);
  }
}

void setup() {
  Serial.begin(9600);

  encoderGroup.setOnTurnLeft(onTurnLeft);
  encoderGroup.setOnTurnRight(onTurnRight);

  encoder1.setPinMode(INPUT, PULL_UP);

  encoder1.setGroup(&encoderGroup);
  encoder1.setInteger("id", 0);
  encoder1.setString("name", "Encoder 1");
  encoder1.setBoolean("canPrint", true);
}

void loop() {
  encoderGroup.process();
}
