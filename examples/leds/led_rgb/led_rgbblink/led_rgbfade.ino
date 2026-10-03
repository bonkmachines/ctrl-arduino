/*
  RGB LED basic integration and control

  Description:
  This sketch demonstrates how to fade an RGB LED through different colours.
  
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
#define MAX_BRIGHTNESS 255
#define DELAY 5

CtrlRGBLed rgbLed(PIN_R, PIN_G, PIN_B, MAX_BRIGHTNESS);

void setup() {}

void loop() {  
  uint8_t colour[] = {0, 0, 0};

  // Pick which channel to increase and which to decrease.
  for (int decColour = 0; decColour < 3; decColour += 1) {
    int incColour = decColour == 2 ? 0 : decColour + 1;

    // Cross-fade between the two channels
    for(int i = 0; i < 255; i += 1) {
      colour[decColour] -= 1;
      colour[incColour] += 1;
      
      // Display
      rgbLed.setRGB(colour);
      delay(DELAY);
    }
  }
}