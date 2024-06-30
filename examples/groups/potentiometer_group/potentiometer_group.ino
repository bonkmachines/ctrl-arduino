/*
  Potentiometer group example

  Description:
  In order to have an alternative approach to handle a large amount of potentiometers,
  we can use groups. This allows for the usage of one shared event handler. If we then
  provide the potentiometers with some data, in the form of setters: setInteger(),
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

  CtrlPot methods:
  - setGroup(&group)              Register the potentiometer to a group.
  - setInteger("id", 0)           Define an integer. First parameter is the name of the variable, second parameter is the value.
  - setString("name", "Button")   Define a string. First parameter is the name of the variable, second parameter is the value.
  - setBoolean("active", true)    Define a boolean. First parameter is the name of the variable, second parameter is the value.
  - getInteger("id")              Get the value of an integer.
  - getString("name")             Get the value of a string.
  - getBoolean("active")          Get the value of a boolean.
*/

#include <CtrlGroup.h>
#include <CtrlPot.h>

// Create a potentiometer group.
CtrlGroup potentiometerGroup;

// Create 2 potentiometers with: pin number, max output value & sensitivity margin.
CtrlPot potentiometer1(A0, 100, 0.05);
CtrlPot potentiometer2(A1, 100, 0.05);

// Define an onValueChange handler. This will be triggered by all potentiometers registered to the group.
void onValueChange(Groupable& potentiometer, int value) {
  // Retrieve the variables we need within this handler.
  bool canPrint = potentiometer.getBoolean("canPrint");
  int id = potentiometer.getInteger("id");
  String name = potentiometer.getString("name");
  // if the potentiometer can print, we print to the serial monitor.
  if (canPrint) {
    Serial.print("Turned potentiometer with id: ");
    Serial.print(id);
    Serial.print(" / Name: ");
    Serial.print(name);
    Serial.print(" / Value: ");
    Serial.println(value);
  }
}

void setup() {
  Serial.begin(9600);

  // Register the onPress handler with the group.
  potentiometerGroup.setOnValueChange(onValueChange);

  // Register the potentiometers to the group.
  potentiometer1.setGroup(&potentiometerGroup);
  potentiometer2.setGroup(&potentiometerGroup);

  // Set all variables needed for potentiometer 1 & 2.
  potentiometer1.setInteger("id", 0);
  potentiometer1.setString("name", "Potentiometer 1");
  potentiometer1.setBoolean("canPrint", true);
  potentiometer2.setInteger("id", 1);
  potentiometer2.setString("name", "Potentiometer 2");
  potentiometer2.setBoolean("canPrint", true);
}

void loop() {
  // Process all potentiometers registered to the group.
  potentiometerGroup.process();
}