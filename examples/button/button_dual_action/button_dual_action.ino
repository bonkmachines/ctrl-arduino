/*
  Dual action button example

  Description:
  This sketch demonstrates the basic implementation of a dual action button or switch,
  that differentiates between a short and long press.
  
  Usage:
  Create a button with reference to:
  - Signal pin               (required) The input pin your button is hooked up to.
  - Bonuce duration          (required) In milliseconds.
  - onPress handler          (optional).
  - onRelease handler        (optional).
  - onDelayedRelease handler (optional).

  Available methods:
  - process()                   Is used to poll the button and handle all it's functionality  (used in the loop method).
  - setOnPress()                Sets the onPress handler. Is called when the button is pressed.
  - setOnRelease()              Sets the onRelease handler. Is called when the button is released.
  - setOnDelayedRelease()       Sets the onDelayedRelease handler. Is called when the button is
                                released after a certain amount of time (The default is 500ms).
  - setDelayedReleaseDuration() Sets the amount of time for a delayed release.
  - setMultiplexer()            Sets the multiplexer that the button subscribes to.
  - disable()                   Disables the button.
  - enable()                    Enables the button.
  - isEnabled()                 Checks if the button is enabled.
  - isDisabled()                Checks if the button is disabled.
  - isPressed()                 Checks if the button is currently being pressed.
  - isReleased()                Checks if the button is currently not being pressed.
*/

#include <CtrlBtn.h>

// Define an onRelease handler.
void onRelease() {
  Serial.println("Short press");
}

// Define an onDelayedRelease handler.
void onDelayedRelease() {
  Serial.println("Long press");
}

/*
  Create a button with:
  - signal pin.
  - bounce duration.
  - empty onPress handler (nullptr).
  - onRelease handler.
  - onDelayedRelease handler.
 */
CtrlBtn button(36, 15, nullptr, onRelease, onDelayedRelease);

void setup() {
  Serial.begin(9600);
  button.setDelayedReleaseDuration(1000); // This is optional (default is 500ms).
}

void loop() {
  // The process method will poll the button object and handle all it's functionality.
  button.process();
}