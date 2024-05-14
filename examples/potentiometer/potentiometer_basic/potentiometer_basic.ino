/*
  Basic potentiometer example

  Description:
  This sketch demonstrates the basic implementation of a potentiometer.

  Usage:
  Create a potentiometer with reference to:
  - Signal pin             (required / the input pin your potentiometer is hooked up to)
  - Max. output value      (required) The maximum output value of the potentiometer (e.g. for a MIDI signal you'd set this to 127)
  - Sensitivity margin     (required) If you have a pot with jitter (instable readings), increase this value till it becomes stable
  - onValueChange handler  (optional)

  Available methods:
  - process()           Is used to poll the potentiometer and handle all it's functionality (used in the loop method)
  - getValue()          Retrieves the current value of the potentiometer
  - setOnValueChange()  Sets the onValueChange handler
  - disable()           Disables the potentiometer
  - enable()            Enables the potentiometer
  - isEnabled()         Checks if the potentiometer is enabled
  - isDisabled()        Checks if the potentiometer is disabled
*/

#include <CtrlPot.h>

// Define an onValueChange handler (optional)
void onValueChange(int value) {
  Serial.print("Basic pot value: ");
  Serial.println(value);
}

// Instantiate a potentiometer with the pin number, max. output value, sensitivity margin & onValueChange handler (optional)
CtrlPot potentiometer = CtrlPot::create(24, 100, 10, onValueChange);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // The process method will keep polling our potentiometer object and handle all it's functionality
  potentiometer.process();
}