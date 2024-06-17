/*
  Alternative button example

  Description:
  This sketch demonstrates an alternative implementation of a button or switch,
  with debouncing functionality for noisy buttons.

  With this alternative approach you can instantiate all your objects first, while setting
  the handlers at a later point. This is especially handy in larger projects where you have
  to access other objects from the handlers. And you can't access an object if it hasn't 
  been instantiated yet (and you might not want to use 'forward declaration'). To illustrate
  this problem further, in the approach described in the basic example you will quickly run
  into problems as you have to keep track of the order of instantiation, which can become
  messy very quickly.

  Usage:
  Create a button with reference to:
  - Signal pin      (required) The input pin your button is hooked up to.
  - Bounce duration (required) In milliseconds.
  
  The following handler methods can then be (optionally) set for the created button object:
  - setOnPress()
  - setOnRelease()
  - setOnDelayedRelease()

  Available methods:
  - setPinMode(INPUT, PULL_UP)      The first parameter can be set to 'INPUT', 'INPUT_PULLUP' or 'INPUT_PULLDOWN'.
                                    If this method is not used, the default mode is: 'INPUT_PULLUP' and the
                                    internal pull-up resistor of the pin will be used. If the first parameter is
                                    set to 'INPUT', you will have to implement an external pull-down or pull-up
                                    resistor. You should then set the second parameter to 'PULL_DOWN' or 'PULL_UP'.
  - process()                       Is used to poll the button and handle all it's functionality  (used in the loop method).
  - setOnPress()                    Sets the onPress handler. Is called when the button is pressed.
  - setOnRelease()                  Sets the onRelease handler. Is called when the button is released.
  - setOnDelayedRelease()           Sets the onDelayedRelease handler. Is called when the button is
                                    released after a certain amount of time (The default is 500ms).
  - setDelayedReleaseDuration(500)  Sets the amount of time for a delayed release (in milliseconds).
  - setMultiplexer(&mux)            Sets the multiplexer that the button subscribes to.
  - disable()                       Disables the button.
  - enable()                        Enables the button.
  - isEnabled()                     Checks if the button is enabled.
  - isDisabled()                    Checks if the button is disabled.
  - isPressed()                     Checks if the button is currently being pressed.
  - isReleased()                    Checks if the button is currently not being pressed.
*/

#include <CtrlBtn.h>

// Create a button with the signal pin number & bounce duration.
CtrlBtn button(36, 15);

// Define an onPress handler.
void onPress() {
  Serial.println("Alternative button pressed");
}

// Define an onRelease handler.
void onRelease() {
  Serial.println("Alternative button released");
}

void setup() {
  Serial.begin(9600);
  // Register the handlers with the button object.
  button.setOnPress(onPress);
  button.setOnRelease(onRelease);
  // If you use an external pull-up resistor, uncomment this:
  // button.setPinMode(INPUT, PULL_UP);
  // If you use an external pull-down resistor, uncomment this:
  // button.setPinMode(INPUT, PULL_DOWN);
}

void loop() {
  // The process method will poll the button object and handle all it's functionality.
  button.process();
}