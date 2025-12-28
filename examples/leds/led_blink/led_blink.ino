/*
  Basic LED blink example

  Description:
  This sketch demonstrates the basic implementation of how to setup and control a blinking LED.
  
  Usage:
  Create an LED with reference to:
  - Signal pin (required) - The pin your LED is hooked up to.

  For PWM-capable pins (brightness control):
  - CtrlLed led(pin, maxBrightness);  // Enable PWM mode with brightness control

  For non-PWM pins (simple on/off):
  - CtrlLed led(pin);                 // Enable digital mode, on/off only

  Available methods:
  - turnOn()              Turns on the LED.
  - turnOff()             Turns off the LED.
  - toggle()              Toggles the LED's off/on status.
  - setMaxBrightness(255) Sets the maximum brightness (PWM mode only).
  - setBrightness(100)    Sets the brightness in percentages (PWM mode only).
  - getMaxBrightness()    Returns the maximum brightness set for the LED.
  - getBrightness()       Returns the brightness of the LED.
  - isOn()                Checks if the LED is turned on.
  - isOff()               Checks if the LED is turned off.
  - isPwmMode()           Checks if the LED is in PWM mode.
*/

#include <CtrlLed.h>

// Digital mode example (non-PWM pin).
// This assumes you have connected your LED to a pin without the need for PWM:
CtrlLed led(LED_BUILTIN);

// PWM mode example (connect to a PWM-capable pin with brightness control):
// Uncomment the line below and comment out the line above to use PWM mode
// CtrlLed led(LED_BUILTIN, 255);

void setup()
{
  // Initialize the LED (nothing special needed for digital mode).
}

void loop() {
  // Make the LED blink.
  led.toggle();
  delay(500);
}