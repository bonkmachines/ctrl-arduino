/*
  Basic button example

  Description:
  This sketch demonstrates the basic implementation of a button or switch,
  with debouncing functionality for noisy buttons.
  
  Usage:
  Create a button with reference to:
  - Signal pin        (required) The input pin your button is hooked up to.
  - Bonuce duration   (required) In milliseconds.
  - onPress handler   (optional)
  - onRelease handler (optional)

  Available methods:
  - process()         Is used to poll the button and handle all it's functionality (used in the loop method).
  - setOnPress()      Sets the onPress handler. Is called when the button is pressed.
  - setOnRelease()    Sets the onRelease handler. Is called when the button is released.
  - setMultiplexer()  Sets the multiplexer that the button subscribes to.
  - disable()         Disables the button.
  - enable()          Enables the button.
  - isEnabled()       Checks if the button is enabled.
  - isDisabled()      Checks if the button is disabled.
  - isPressed()       Checks if the button is currently being pressed.
  - isReleased()      Checks if the button is currently not being pressed.
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

// Create a button with the signal pin number, bounce duration, onPress (optional) & onRelease (optional) handler.
CtrlBtn button = CtrlBtn::create(36, 15, onPress, onRelease);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // The process method will poll the button object and handle all it's functionality.
  button.process();
}