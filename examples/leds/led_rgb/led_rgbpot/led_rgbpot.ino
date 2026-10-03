/*
  RGB LED integration with two potentiometers

  Description:
  This sketch demonstrates how to control an RGB LED using two potentiometers and the FastLED library.
  
  Usage:
  Create an LED with reference to:
  - Signal pin (required) - The pin your LED is hooked up to.
  
  Construct with:
  - CtrlLed led(pinR, pinG, pinB, maxBrightness);  // RGB LED's require PWM-capable pins.

  Available methods:
  - turnOn()              Turns on the LED.
  - turnOff()             Turns off the LED.
  - set()                 Set the LED to a specific off/on state.
  - toggle()              Toggles the LED's off/on status.
  - setRGB()              Set the RGB values for the LED.
  - setMaxBrightness()    Sets the maximum brightness.
  - setBrightness()       Sets the brightness in percentages.
  - getMaxBrightness()    Returns the maximum brightness set for the LED.
  - getBrightness()       Returns the brightness of the LED.
  - getRGBRaw()           Returns an array of the raw RGB values pushed to the LED.
  - getRGB()              Returns an array of the RGB values pushed to the LED, scaled by brightness.
  - isOn()                Checks if the LED is turned on.
  - isOff()               Checks if the LED is turned off.
  - enable()              Enables the LED.
  - disable()             Disables the LED.
  - isEnabled()           Checks if the LED is enabled.
  - isDisabled()          Checks if the LED is disabled.
*/

#include <CtrlRGBLed.h>
#include <CtrlPot.h>
#include <FastLED.h>

#define PIN_R 16
#define PIN_G 17
#define PIN_B 18
#define PIN_P1 27
#define PIN_P2 28
#define MAX_BRIGHTNESS 255
#define SMOOTHING 20

CtrlRGBLed rgbLed(PIN_R, PIN_G, PIN_B, MAX_BRIGHTNESS);
CtrlPot brightnessPot(PIN_P1, 100, SMOOTHING);
CtrlPot colourPot(PIN_P2, 100, SMOOTHING);

void setup() {
  Serial.begin(9600);
}

void loop() {
  brightnessPot.process();
  colourPot.process();

  // Use HSV to map the potentiometer readings over the colour spectrum.
  rgbLed.setRGB(hsv2rgb_rainbow(CHSV({colourPot.getValue(), 255, 255})).raw);
  
  // Set the LED's brightness to the potentiometers percentage to maximum
  rgbLed.setBrightness(brightnessPot.getPercentage());

  // Retrieve the RGB values as an array.
  std::array<uint8_t, 3> rgb = rgbLed.getRGB();
}