/*
  Rotary encoder group example

  Description:
  In order to have an alternative approach to handle a large amount of rotary encoders,
  we can use groups. This allows for the usage of one shared event handler. If we then
  provide the rotary encoders with some data, in the form of setters: setInteger(),
  setString() & setBoolean(), we can retrieve this data in the event handler and
  take action based on this data. Getting the data, is done with the following getters:
  getInteger(), getString() & getBoolean().

  CtrlGroup methods:
  - setOnPress(handler)           Set the on press handler (for buttons).
  - setOnRelease(handler)         Set the on release handler (for buttons).
  - setOnDelayedRelease(handler)  Set the on delayed release handler (for buttons).
  - setOnTurnLeft(handler)        Set the on turn left handler (for rotary encoders).
  - setOnTurnRight(handler)       Set the on turn right handler (for rotary encoders).
  - setOnValueChange(handler)     Set the on value change handler (for potentiometers).
  - process()                     Is used to poll all objects registered to the group.
                                  (used in the loop method).

  CtrlEnc methods:
  - setGroup(&group)              Register the rotary encoder to a group.
  - setInteger("id", 0)           Define an integer. First parameter is the name of the variable, second parameter is the value.
  - setString("name", "Button")   Define a string. First parameter is the name of the variable, second parameter is the value.
  - setBoolean("active", true)    Define a boolean. First parameter is the name of the variable, second parameter is the value.
  - getInteger("id")              Get the value of an integer.
  - getString("name")             Get the value of a string.
  - getBoolean("active")          Get the value of a boolean.

  Note: setInteger/setString/setBoolean use fixed-size memory (max 8
  properties per object, 'name' up to 15 chars, 'value' up to 20 chars).
*/

#include <CtrlGroup.h>
#include <CtrlEnc.h>

// Create a rotary encoder group.
CtrlGroup encoderGroup;

// Create 2 rotary encoders with: clk pin number & dt pin number.
CtrlEnc encoder1(1, 2);
CtrlEnc encoder2(3, 4);

// Define an onTurnLeft handler. This will be triggered by all rotary encoders registered to the group.
void onTurnLeft(Groupable& encoder) {
  // Retrieve the variables we need within this handler.
  auto canPrint = encoder.getBoolean("canPrint");
  auto id = encoder.getInteger("id");
  auto name = encoder.getString("name");
  // if the rotary encoder can print, we print to the serial monitor.
  if (canPrint) {
    Serial.print("Turn left encoder with id: ");
    Serial.print(id);
    Serial.print(" / Name: ");
    Serial.println(name);
  }
}

// Define an onTurnRight handler. This will be triggered by all rotary encoders registered to the group.
void onTurnRight(Groupable& encoder) {
  // Retrieve the variables we need within this handler.
  bool canPrint = encoder.getBoolean("canPrint");
  int id = encoder.getInteger("id");
  String name = encoder.getString("name");
  // if the rotary encoder can print, we print to the serial monitor.
  if (canPrint) {
    Serial.print("Turn right encoder with id: ");
    Serial.print(id);
    Serial.print(" / name: ");
    Serial.println(name);
  }
}

void setup() {
  Serial.begin(9600);

  // Register the onTurnLeft & onTurnRight handler with the group.
  encoderGroup.setOnTurnLeft(onTurnLeft);
  encoderGroup.setOnTurnRight(onTurnRight);

  // Register the rotary encoders to the group.
  encoder1.setGroup(&encoderGroup);
  encoder2.setGroup(&encoderGroup);

  // Set all variables needed for rotary encoder 1 & 2.
  encoder1.setInteger("id", 0);
  encoder1.setString("name", "Encoder 1");
  encoder1.setBoolean("canPrint", true);
  encoder2.setInteger("id", 1);
  encoder2.setString("name", "Encoder 2");
  encoder2.setBoolean("canPrint", true);
}

void loop() {
  // Process all rotary encoders registered to the group.
  encoderGroup.process();
}