/*
  Alternative button example

  Description:
  This sketch demonstrates an alternative implementation of a button or switch,
  with debouncing functionality for noisy buttons.

  With this alternative approach you can instantiate all your objects first, while setting
  the handlers at a later point. This is especially handy in larger projects where you have
  to access other objects from the handlers. And you can't access an object if it hasn't 
  been instantiated yet. To illustrate this problem further, in the approach described
  in the basic example you will quickly run into problems as you have to keep track of
  the order of instantiation, which can become messy very quickly.

  Usage:
  Create a button with reference to:
  - Signal pin      (required / the input pin your button is hooked up to)
  - Bounce duration (required / in milliseconds)
  
  The following handler methods can then be (optionally) set for the created button object:
  - setOnPress(onPress)
  - setOnRelease(onRelease);

  Available methods:
  - process()       Is used to poll the button and handle all it's functionality (used in the loop method)
  - setOnPress()    Sets the onPress handler
  - setOnRelease()  Sets the onRelease handler
  - disable()       Disables the button
  - enable()        Enables the button
  - isEnabled()     Checks if the button is enabled
  - isDisabled()    Checks if the button is disabled
  - isPressed()     Checks if the button is currently being pressed
  - isReleased()    Checks if the button is currently not being pressed
*/

#include <CtrlBtn.h>

// Instantiate a button with the signal pin number & bounce duration
CtrlBtn button = CtrlBtn::create(36, 15);

// Define an onPress handler
void onPress() {
  Serial.println("Alternative button pressed");
}

// Define an onRelease handler
void onRelease() {
  Serial.println("Alternative button released");
}

void setup() {
  Serial.begin(9600);

  // Register the handlers with the button object
  button.setOnPress(onPress);
  button.setOnRelease(onRelease);
}

void loop() {
  // The process method will poll the button object and handle all it's functionality
  button.process();
}