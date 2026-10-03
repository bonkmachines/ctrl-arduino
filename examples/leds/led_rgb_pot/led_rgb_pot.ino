/*
  RGB LED with potentiometers example

  Description:
  This sketch demonstrates how to control an RGB LED with two potentiometers:
  one picks the colour (turning it sweeps through the colour wheel) and the
  other sets the brightness.

  Usage:
  - Hook up a common cathode RGB LED to PWM pins 9 (red), 10 (green) & 11 (blue).
  - Hook up two potentiometers to A0 (colour) & A1 (brightness).
  See the led_rgb example for all available RGB LED methods, and the
  potentiometer examples for all available potentiometer methods.
*/

#include <CtrlRGBLed.h>
#include <CtrlPot.h>

CtrlRGBLed led(9, 10, 11, 255);

// The colour pot outputs a position on the colour wheel (0 - 255).
CtrlPot colorPot(A0, 255, 0.05);

// The brightness pot outputs 0 - 100.
CtrlPot brightnessPot(A1, 100, 0.05);

// Turns a position on the colour wheel (0 - 255) into a colour,
// going from red, through green and blue, back to red.
CtrlRGB colorWheel(uint8_t position)
{
  if (position < 85) {
    return CtrlRGB{ static_cast<uint8_t>(255 - position * 3), static_cast<uint8_t>(position * 3), 0 };
  }
  if (position < 170) {
    position -= 85;
    return CtrlRGB{ 0, static_cast<uint8_t>(255 - position * 3), static_cast<uint8_t>(position * 3) };
  }
  position -= 170;
  return CtrlRGB{ static_cast<uint8_t>(position * 3), 0, static_cast<uint8_t>(255 - position * 3) };
}

void setup()
{
  led.turnOn();
}

void loop() {
  colorPot.process();
  brightnessPot.process();

  led.setColor(colorWheel(colorPot.getValue()));
  led.setBrightness(brightnessPot.getValue());
}
