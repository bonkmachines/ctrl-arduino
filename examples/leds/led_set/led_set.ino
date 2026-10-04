/*
  LED set example

  Description:
  This sketch demonstrates how to drive an LED directly from a boolean state,
  using the set() method. Here the LED mirrors a button: it lights up while
  the button is held down and goes out when it is released.

  Without set() you would write something like:
    button.isPressed() ? led.turnOn() : led.turnOff();
  With set() this becomes:
    led.set(button.isPressed());

  Usage:
  Create an LED with reference to:
  - Signal pin (required) - The pin your LED is hooked up to.
  Create a button with reference to:
  - Signal pin (required) - The pin your button is hooked up to.
  - Bounce duration (required) - In milliseconds.

  Available methods:
  - set(true)             Turns the LED on (true) or off (false).
  See the led_blink & led_fade examples for all other LED methods.
*/

#include <CtrlLed.h>
#include <CtrlBtn.h>

// The pin of the board's built-in LED. Some boards (e.g. the ESP32 Dev Module)
// don't define LED_BUILTIN, so pin 2 is used there. Change it to match your wiring.
#ifdef LED_BUILTIN
const uint8_t LED_PIN = LED_BUILTIN;
#else
const uint8_t LED_PIN = 2;
#endif

// An LED on the built-in LED pin (digital mode, on/off only).
CtrlLed led(LED_PIN);

// A button on pin 4, with 15ms debouncing, using the internal pull-up resistor.
// (Not pin 2: that is where the LED goes on boards without LED_BUILTIN.)
CtrlBtn button(4, 15);

void setup()
{
  // Nothing to set up.
}

void loop() {
  // Poll the button.
  button.process();

  // Let the LED follow the button's state.
  led.set(button.isPressed());
}
