/*
  Basic button example

  Description:
  This sketch demonstrates the basic implementation of a button or switch,
  with debouncing functionality for noisy buttons.
  
  Usage:
  Create a button with reference to:
  - Signal pin               (required) The input pin your button is hooked up to.
  - Bounce duration          (required) In milliseconds.
  - onPress handler          (optional).
  - onRelease handler        (optional).
  - onDelayedRelease handler (optional).

  Available methods:
  - setPinMode(INPUT, DOWN)        The first parameter can be set to 'INPUT', 'INPUT_PULLUP' or 'INPUT_PULLDOWN'.
                                   If this method is not used, the default mode is: 'INPUT_PULLUP' and the
                                   internal pull-up resistor of the pin will be used. If the first parameter is
                                   set to 'INPUT', you will have to implement an external pull-down or pull-up
                                   resistor. You can then optionally set the second parameter to 'PULL_DOWN' or 'PULL_UP'.
  - process()                      Is used to poll the button and handle all it's functionality  (used in the loop method).
  - setOnPress()                   Sets the onPress handler. Is called when the button is pressed.
  - setOnRelease()                 Sets the onRelease handler. Is called when the button is released.
  - setOnDelayedRelease()          Sets the onDelayedRelease handler. Is called when the button is
                                   released after a certain amount of time (The default is 500ms).
  - setDelayedReleaseDuration(500) Sets the amount of time for a delayed release (in milliseconds).
  - setMultiplexer(&mux)           Sets the multiplexer that the button subscribes to.
  - disable()                      Disables the button.
  - enable()                       Enables the button.
  - isEnabled()                    Checks if the button is enabled.
  - isDisabled()                   Checks if the button is disabled.
  - isPressed()                    Checks if the button is currently being pressed.
  - isReleased()                   Checks if the button is currently not being pressed.
*/

#include <CtrlBtn.h>

// Define an onPress handler.
void onPress() {
  Serial.println("Basic button pressed");
}

// Define an onRelease handler.
void onRelease() {
  Serial.println("Basic button released");
}

/*
  Create a button with:
  - signal pin.
  - bounce duration.
  - onPress handler (optional).
  - onRelease handler (optional).
 */
CtrlBtn button(36, 15, onPress, onRelease);

void setup() {
  Serial.begin(9600);
  // If you use an external pull-up resistor, uncomment this:
  // button.setPinMode(INPUT, PULL_UP);
  // If you use an external pull-down resistor, uncomment this:
  // button.setPinMode(INPUT, PULL_DOWN);
}

void loop() {
  // The process method will poll the button object and handle all it's functionality.
  button.process();
}