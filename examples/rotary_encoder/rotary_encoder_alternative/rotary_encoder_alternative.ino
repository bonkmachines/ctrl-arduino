/*
  Alternative rotary encoder example

  Description:
  This sketch demonstrates an alternative implementation of a rotary encoder.

  With this alternative approach you can instantiate all your objects first, while setting
  the handlers at a later point. This is especially handy in larger projects where you have
  to access other objects from the handlers. And you can't access an object if it hasn't 
  been instantiated yet. To illustrate this problem further, in the approach described
  in the basic example you will quickly run into problems as you have to keep track of
  the order of instantiation, which can become messy very quickly.

  Usage:
  Create a rotary encoder with reference to:
  - CLK signal pin    (required) The clk input pin your rotary encoder is hooked up to.
  - DT signal pint    (required) The dt input pin your rotary encoder is hooked up to.
  
  The following handler methods can then be (optionally) set for the created rotary encoder object:
  - setOnTurnLeft(onTurnLeft)
  - setOnTurnRight(onTurnRight)

  Available methods:
  - process()         Is used to poll the rotary encoder and handle all it's functionality (used in the loop method).
  - setOnTurnLeft()   Sets the onTurnleft handler. Is called when you turn left.
  - setOnTurnRight()  Sets the onTurnRight handler. Is called when you turn right.
  - setMultiplexer()  Sets the multiplexer that the rotary encoder subscribes to.
  - disable()         Disables the rotary encoder.
  - enable()          Enables the rotary encoder.
  - isEnabled()       Checks if the rotary encoder is enabled.
  - isDisabled()      Checks if the rotary encoder is disabled.
*/

#include <CtrlEnc.h>

// Instantiate a rotary encoder with the signal pin number & bounce duration.
CtrlEnc encoder = CtrlEnc::create(33, 34);

// Define an onTurnLeft handler.
void onTurnLeft() {
  Serial.println("Alternative rotary encoder turn left");
}

// Define an onTurnRight handler.
void onTurnRight() {
  Serial.println("Alternative rotary encoder turn right");
}

void setup() {
  Serial.begin(9600);

  // Register the handlers with the rotary encoder object.
  encoder.setOnTurnLeft(onTurnLeft);
  encoder.setOnTurnRight(onTurnRight);
}

void loop() {
  // The process method will poll the rotary encoder object and handle all it's functionality.
  encoder.process();
}