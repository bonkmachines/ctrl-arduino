/*
  Basic rotary encoder example

  Description:
  This sketch demonstrates the basic implementation of a rotary encoder.
  
  Usage:
  Create a rotary encoder with reference to:
  - CLK signal pin    (required) The clk input pin your rotary encoder is hooked up to.
  - DT signal pin     (required) The dt input pin your rotary encoder is hooked up to.
  - onPress handler   (optional)
  - onRelease handler (optional)

  Available methods:
  - process()         Is used to poll the rotary encoder and handle all it's functionality (used in the loop method).
  - setOnTurnLeft()   Sets the onTurnleft handler. Is called when you turn left.
  - setOnTurnRight()  Sets the onTurnRight handler. Is called when you turn right.
  - disable()         Disables the rotary encoder.
  - enable()          Enables the rotary encoder.
  - isEnabled()       Checks if the rotary encoder is enabled.
  - isDisabled()      Checks if the rotary encoder is disabled.
*/

#include <CtrlEnc.h>

// Define an onTurnleft handler.
void onTurnleft() {
  Serial.println("Basic rotary encoder turn left");
}

// Define an onTurnRight handler.
void onTurnRight() {
  Serial.println("Basic rotary encoder turn right");
}

// Create a rotary encoder with the clk signal pin number, dt signal pin, onTurnleft (optional) & onTurnRight (optional) handler.
CtrlEnc encoder = CtrlEnc::create(33, 34, onTurnleft, onTurnRight);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // The process method will poll the rotary encoder object and handle all it's functionality.
  encoder.process();
}