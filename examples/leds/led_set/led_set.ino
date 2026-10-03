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

// An LED on the built-in LED pin (digital mode, on/off only).
CtrlLed led(LED_BUILTIN);

// A button on pin 2, with 15ms debouncing, using the internal pull-up resistor.
CtrlBtn button(2, 15);

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
