/*
  Basic LED fade example

  Description:
  This sketch demonstrates the basic implementation of how to setup and control a fading LED.
  This example requires a PWM-capable pin for brightness control.
  
  Usage:
  Create an LED with reference to:
  - Signal pin (required) - The pin your LED is hooked up to (must be PWM-capable).

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

// PWM mode example (PWM-capable pin with brightness control):
// This assumes you have connected your LED to a pin with PWM capabilities:
// The maximum brightness (second parameter) can be used to calibrate an LED,
// in case you are using multiple LEDs that have different maximum brightness.
CtrlLed led(LED_BUILTIN, 50);

void setup()
{
  // Turn on the LED and set the brightness to 0%.
  led.turnOn();
  led.setBrightness(0);
}

void loop() {
  // Fade LED brightness from 0 to 100.
  for (uint8_t brightness = 0; brightness < 100; brightness++) {
    led.setBrightness(brightness);
    delay(10); // Adjust the delay time to change the transition speed.
  }

  // Fade LED brightness from 100 to 0.
  for (uint8_t brightness = 100; brightness > 0; brightness--) {
    led.setBrightness(brightness);
    delay(10); // Adjust the delay time to change the transition speed.
  }
}