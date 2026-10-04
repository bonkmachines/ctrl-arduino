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
  - set(true)             Turns the LED on (true) or off (false).
  - toggle()              Toggles the LED's off/on status.
  - setMaxBrightness(255) Sets the maximum brightness (PWM mode only).
  - setBrightness(100)    Sets the brightness in percentages (PWM mode only).
  - getMaxBrightness()    Returns the maximum brightness set for the LED.
  - getBrightness()       Returns the brightness of the LED.
  - isOn()                Checks if the LED is turned on.
  - isOff()               Checks if the LED is turned off.
  - isPwmMode()           Checks if the LED is in PWM mode.
  - enable()              Enables the LED.
  - disable()             Disables the LED.
  - isEnabled()           Checks if the LED is enabled.
  - isDisabled()          Checks if the LED is disabled.
*/

#include <CtrlLed.h>

// The pin of the board's built-in LED. Some boards (e.g. the ESP32 Dev Module)
// don't define LED_BUILTIN, so pin 2 is used there. Change it to match your wiring.
#ifdef LED_BUILTIN
const uint8_t LED_PIN = LED_BUILTIN;
#else
const uint8_t LED_PIN = 2;
#endif

// Digital mode example (non-PWM pin).
// This assumes you have connected your LED to a pin without the need for PWM:
CtrlLed led(LED_PIN);

// PWM mode example (connect to a PWM-capable pin with brightness control):
// Uncomment the line below and comment out the line above to use PWM mode
// CtrlLed led(LED_PIN, 255);

void setup()
{
  // Initialize the LED (nothing special needed for digital mode).
}

void loop() {
  // Make the LED blink.
  led.toggle();
  delay(500);
}