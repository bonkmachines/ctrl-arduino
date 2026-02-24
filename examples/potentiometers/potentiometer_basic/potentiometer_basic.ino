/*
  Basic potentiometer example

  Description:
  This sketch demonstrates the basic implementation of a potentiometer.

  Usage:
  Create a potentiometer with reference to:
  - Signal pin             (required) The input pin your potentiometer is hooked up to.
  - Max. output value      (required) The maximum output value of the potentiometer (e.g. for a MIDI signal you'd set this to 127).
  - Sensitivity margin     (required) Decrease this for instable (jittery) pots, min: 0.01, max: 100.
  - onValueChange handler  (optional) This will be called as soon as the reading of the potentiometer changes.

  Available methods:
  - process()                    Is used to poll the potentiometer and handle all it's functionality (used in the loop method).
  - getValue()                   Retrieves the current value of the potentiometer.
  - setOnValueChange()           Sets the onValueChange handler. Will be called as soon as the reading of the potentiometer changes.
  - setAnalogMax(1023)           Sets the maximum value returned by analogRead() (default 1023, use 4095 for 12-bit ADCs).
  - getAnalogMax()               Returns the maximum ADC value.
  - setRawValue(raw)             Provide an externally-read raw ADC value (smoothing and change detection still apply).
  - storeRaw(raw)                Store a raw ADC value from an ISR or DMA callback.
  - disable()                    Disables the potentiometer.
  - enable()                     Enables the potentiometer.
  - isEnabled()                  Checks if the potentiometer is enabled.
  - isDisabled()                 Checks if the potentiometer is disabled.
  - setGroup(&group)             Register the potentiometer to a group.
  - isGrouped()                  Checks if the potentiometer is registered to a group.
  - setMultiplexer(&mux)         Sets the multiplexer that the potentiometer subscribes to.
  - isMuxed()                    Checks if the potentiometer is connected to a multiplexer.
  - setInteger("id", 0)          Define an integer. First parameter is the name of the variable, second parameter is the value.
  - setString("name", "Button")  Define a string. First parameter is the name of the variable, second parameter is the value.
  - setBoolean("active", true)   Define a boolean. First parameter is the name of the variable, second parameter is the value.
  - getInteger("id")             Get the value of an integer.
  - getString("name")            Get the value of a string.
  - getBoolean("active")         Get the value of a boolean.
*/

#include <CtrlPot.h>

// Define an onValueChange handler
void onValueChange(int value) {
  Serial.print("Basic pot value: ");
  Serial.println(value);
}

// Create a potentiometer with the pin number, max. output value, sensitivity margin (can be 0.01 to 100) & onValueChange handler (optional).
CtrlPot potentiometer(A0, 100, 0.05, onValueChange);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // The process method will keep polling our potentiometer object and handle all it's functionality.
  potentiometer.process();
}