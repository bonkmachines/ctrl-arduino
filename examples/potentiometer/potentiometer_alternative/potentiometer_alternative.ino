/*
  Alternative potentiometer example

  Description:
  This sketch demonstrates the basic implementation of a potentiometer.

  With this alternative approach you can instantiate all your objects first, while setting
  the handlers at a later point. This is especially handy in larger projects where you have
  to access other objects from the handlers. And you can't access an object if it hasn't
  been instantiated yet. To illustrate this problem further, in the approach described
  in the basic example you will quickly run into problems as you have to keep track of
  the order of instantiation, which can become messy very quickly.

  Usage:
  Create a potentiometer with reference to:
  - Signal pin          (required) The input pin your potentiometer is hooked up to.
  - Max. output value   (required) The maximum output value of the potentiometer (e.g. for a MIDI signal you'd set this to 127).
  - Sensitivity margin  (required) Decrease this for instable (jittery) pots, min: 0.01, max: 100.

  The following handler method can then be (optionally) set for the created potentiometer object:
  - setOnValueChange(onPress)

  Available methods:
  - process()            Is used to poll the potentiometer and handle all it's functionality (used in the loop method).
  - getValue()           Retrieves the current value of the potentiometer.
  - setOnValueChange()   Sets the onValueChange handler. Will be called as soon as the reading of the potentiometer changes.
  - setMultiplexer(&mux) Sets the multiplexer that the potentiometer subscribes to.
  - disable()            Disables the potentiometer.
  - enable()             Enables the potentiometer.
  - isEnabled()          Checks if the potentiometer is enabled.
  - isDisabled()         Checks if the potentiometer is disabled.
*/

#include <CtrlPot.h>

// Create a potentiometer with the pin number, max. output value & sensitivity margin (can be 0.01 to 100).
CtrlPot potentiometer(24, 100, 0.05);

// Define an onValueChange handler
void onValueChange(int value) {
  Serial.print("Alternative pot value: ");
  Serial.println(value);
}

void setup() {
  Serial.begin(9600);
  // Register the handler with the potentiometer object.
  potentiometer.setOnValueChange(onValueChange);
}

void loop() {
  // The process method will keep polling our potentiometer object and handle all it's functionality.
  potentiometer.process();
}