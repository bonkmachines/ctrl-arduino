/*
  Basic LED fade example

  Description:
  This sketch demonstrates the basic implementation of how to setup and control a fading LED.
  
  Usage:
  Create a button with reference to:
  - Signal pin      (required / the input pin your LED is hooked up to)

  Available methods:
  - turnOn()           Turns on the LED
  - turnOff()          Turns off the LED
  - toggle()           Switches the LED's off/on status
  - setMaxBrightness() Sets the maximum brightness of the LED, for calibration purposes (0 - 255)
  - setBrightness()    Sets the brightness of the LED in percentages (0 - 100)
  - getMaxBrightness() Returns the maximum brightness set for the LED
  - getBrightness()    Returns the brightness of the LED
  - isOn()             Checks if the LED is turned on
  - isOff()            Checks if the LED is turned off
*/

#include <CtrlLed.h>

/* Create an LED with the signal pin number, and maximum brightness
   The maximum brightness can be used to calibrate an LED in case
   you are using LED's that have a different maximum brightness.
*/
CtrlLed led(23, 15);

void setup()
{
  // Turn on the LED and set the brightness to 0%
  led.turnOn();
  led.setBrightness(0);
}

void loop() {
  // Fade LED brightness from 0 to 100
  for (uint8_t brightness = 0; brightness < 100; brightness++) {
    led.setBrightness(brightness);
    delay(10); // Adjust the delay time to change the transition speed
  }

  // Fade LED brightness from 100 to 0
  for (uint8_t brightness = 100; brightness > 0; brightness--) {
    led.setBrightness(brightness);
    delay(10); // Adjust the delay time to change the transition speed
  }
}