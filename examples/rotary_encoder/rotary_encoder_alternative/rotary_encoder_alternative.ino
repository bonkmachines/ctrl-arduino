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
  - setPinMode(INPUT, PULL_UP) The first parameter can be set to 'INPUT', 'INPUT_PULLUP' or 'INPUT_PULLDOWN'.
                               If this method is not used, the default mode is: 'INPUT_PULLUP' and the
                               internal pull-up resistor of the pin will be used. If the first parameter is
                               set to 'INPUT', you will have to implement an external pull-down or pull-up
                               resistor. You should then set the second parameter to 'PULL_DOWN' or 'PULL_UP'.
  - process()                  Is used to poll the rotary encoder and handle all it's functionality (used in the loop method).
  - setOnTurnLeft()            Sets the onTurnleft handler. Is called when you turn left.
  - setOnTurnRight()           Sets the onTurnRight handler. Is called when you turn right.
  - setMultiplexer(&mux)       Sets the multiplexer that the rotary encoder subscribes to.
  - disable()                  Disables the rotary encoder.
  - enable()                   Enables the rotary encoder.
  - isEnabled()                Checks if the rotary encoder is enabled.
  - isDisabled()               Checks if the rotary encoder is disabled.
*/

#include <CtrlEnc.h>

// Create a rotary encoder with the signal pin number & bounce duration.
CtrlEnc encoder(33, 34);

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
  
  // If you use external pull-up resistors, uncomment the following line:
  // encoder.setPinMode(INPUT, PULL_UP);

  // If you use external pull-down resistors, uncomment the following line:
  // encoder.setPinMode(INPUT, PULL_DOWN);

  // If you have a board that has internal pull-down resistors, and want to 
  // use those instead, you can uncomment the following line:
  // encoder.setPinMode(INPUT_PULLDOWN);

  // If you have a board that has internal pull-up resistors, and want to use those instead, you 
  // don't need to call the setPinMode() method, as the encoder is set to 'INPUT_PULLUP' by default.
}

void loop() {
  // The process method will poll the rotary encoder object and handle all it's functionality.
  encoder.process();
}