/*
  Button group example

  Description:
  In order to have an alternative approach to handle a large amount of buttons, we
  can use groups. This allows for the usage of one shared event handler. If we then
  provide the buttons with some data, in the form of setters: setInteger(),
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

  CtrlBtn methods:
  - setGroup(&group)              Register the button to a group.
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
#include <CtrlBtn.h>

// Create a button group.
CtrlGroup buttonGroup;

// Create 2 buttons with: pin number & bounce duration.
CtrlBtn button1(1, 15);
CtrlBtn button2(2, 15);

// Define an onPress handler. This will be triggered by all buttons registered to the group.
void onPress(Groupable& button) {
  // Retrieve the variables we need within this handler.
  bool canPrint = button.getBoolean("canPrint");
  int id = button.getInteger("id");
  String name = button.getString("name");
  // if the button can print, we print to the serial monitor.
  if (canPrint) {
    Serial.print("Pressed button with id: ");
    Serial.print(id);
    Serial.print(" / Name: ");
    Serial.println(name);
  }
}

void setup() {
  Serial.begin(9600);

  // Register the onPress handler with the group.
  buttonGroup.setOnPress(onPress);

  // Register the buttons to the group.
  button1.setGroup(&buttonGroup);
  button2.setGroup(&buttonGroup);

  // Set all variables needed for button 1 & 2.
  button1.setInteger("id", 0);
  button1.setString("name", "Button 1");
  button1.setBoolean("canPrint", true);
  button2.setInteger("id", 1);
  button2.setString("name", "Button 2");
  button2.setBoolean("canPrint", true);
}

void loop() {
  // Process all buttons registered to the group.
  buttonGroup.process();
}