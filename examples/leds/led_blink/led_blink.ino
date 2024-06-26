/*
  Basic LED blink example

  Description:
  This sketch demonstrates the basic implementation of how to setup and control a blinking LED.
  
  Usage:
  Create a button with reference to:
  - Signal pin         (required) The pin your LED is hooked up to.

  Available methods:
  - turnOn()              Turns on the LED.
  - turnOff()             Turns off the LED.
  - toggle()              Toggles the LED's off/on status.
  - setMaxBrightness(255) Sets the maximum brightness of the LED, for calibration purposes (0 - 255).
  - setBrightness(100)    Sets the brightness of the LED in percentages (0 - 100).
  - getMaxBrightness()    Returns the maximum brightness set for the LED.
  - getBrightness()       Returns the brightness of the LED.
  - isOn()                Checks if the LED is turned on.
  - isOff()               Checks if the LED is turned off.
*/

#include <CtrlLed.h>

/* Create an LED with the pin number, and maximum brightness.
   The maximum brightness can be used to calibrate an LED in case
   you are using LED's that have a different maximum brightness (optional).
*/
CtrlLed led(LED_BUILTIN, 50);

void setup()
{
  // Turn on the LED and set the brightness to 100%.
  led.turnOn();
  led.setBrightness(100);
}

void loop() {
  // Make the LED blink.
  led.toggle();
  delay(500);
}