/*
  RGB LED example

  Description:
  This sketch demonstrates how to control a 4-pin RGB LED: it cycles through
  a few colours, then fades the brightness of a custom colour up and down.

  Usage:
  Create an RGB LED with reference to:
  - Red signal pin (required)   - The pin the red leg of your LED is hooked up to.
  - Green signal pin (required) - The pin the green leg of your LED is hooked up to.
  - Blue signal pin (required)  - The pin the blue leg of your LED is hooked up to.
  - Maximum brightness (required) - For calibration purposes (0 - 255).
  - Type (optional) - COMMON_CATHODE (default) or COMMON_ANODE, depending on your LED.
  All three signal pins need to be PWM-capable (on an Arduino Uno: 3, 5, 6, 9, 10 or 11).

  For a common cathode LED (the long leg goes to GND):
  - CtrlRGBLed led(pinR, pinG, pinB, 255);
  For a common anode LED (the long leg goes to 5V / 3.3V):
  - CtrlRGBLed led(pinR, pinG, pinB, 255, COMMON_ANODE);

  Available methods:
  - turnOn()                    Turns on the LED.
  - turnOff()                   Turns off the LED.
  - set(true)                   Turns the LED on (true) or off (false).
  - toggle()                    Toggles the LED's off/on status.
  - setColor(255, 0, 0)         Sets the colour as red, green & blue values (0 - 255). Does not turn the LED on.
  - setColor(CtrlColor::Red)    Sets one of the ready-made colours: Off, White, Red, Green, Blue, Yellow, Cyan & Magenta.
  - getColor()                  Returns the colour (CtrlRGB, with .r, .g & .b), regardless of brightness.
  - getOutputColor()            Returns the colour the LED actually outputs (scaled by brightness, off when the LED is off).
  - setMaxBrightness(255)       Sets the maximum brightness.
  - setBrightness(100)          Sets the brightness in percentages.
  - getMaxBrightness()          Returns the maximum brightness set for the LED.
  - getBrightness()             Returns the brightness of the LED.
  - isOn()                      Checks if the LED is turned on.
  - isOff()                     Checks if the LED is turned off.
  - isCommonAnode()             Checks if the LED is a common anode LED.
  - enable()                    Enables the LED.
  - disable()                   Disables the LED.
  - isEnabled()                 Checks if the LED is enabled.
  - isDisabled()                Checks if the LED is disabled.
*/

#include <CtrlRGBLed.h>

// A common cathode RGB LED on pins 9 (red), 10 (green) & 11 (blue), at full brightness.
CtrlRGBLed led(9, 10, 11, 255);

// A colour of your own, as red, green & blue values.
const CtrlRGB pink = {255, 51, 153};

void setup()
{
  Serial.begin(9600);
  led.turnOn();
}

void loop() {
  // Cycle through some of the ready-made colours.
  const CtrlRGB colors[] = { CtrlColor::Red, CtrlColor::Green, CtrlColor::Blue, CtrlColor::White };
  for (const CtrlRGB color : colors) {
    led.setColor(color);
    delay(500);
  }

  // Fade a custom colour in and out.
  led.setColor(pink);
  for (int brightness = 0; brightness <= 100; brightness++) {
    led.setBrightness(brightness);
    delay(10);
  }
  for (int brightness = 100; brightness >= 0; brightness--) {
    led.setBrightness(brightness);
    delay(10);
  }

  // The colour the LED actually outputs is the colour scaled by its brightness.
  const CtrlRGB output = led.getOutputColor();
  Serial.print("Output: ");
  Serial.print(output.r);
  Serial.print(", ");
  Serial.print(output.g);
  Serial.print(", ");
  Serial.println(output.b);

  led.setBrightness(100);
}
