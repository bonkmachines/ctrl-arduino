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
  - setPinMode(INPUT, PULL_UP)   The first parameter can be set to 'INPUT', 'INPUT_PULLUP' or 'INPUT_PULLDOWN'.
                                 If this method is not used, the default mode is: 'INPUT_PULLUP' and (if available)
                                 the internal pull-up resistor of the pin will be used. If the first parameter is
                                 set to 'INPUT', you will have to implement an external pull-down or pull-up
                                 resistor. You should then set the second parameter to 'PULL_DOWN' or 'PULL_UP'.
  - process()                    Is used to poll the rotary encoder and handle all it's functionality (used in the loop method).
  - setOnTurnLeft()              Sets the onTurnleft handler. Is called when you turn left.
  - setOnTurnRight()             Sets the onTurnRight handler. Is called when you turn right.
  - setMultiplexer(&mux)         Sets the multiplexer that the rotary encoder subscribes to.
  - disable()                    Disables the rotary encoder.
  - enable()                     Enables the rotary encoder.
  - isEnabled()                  Checks if the rotary encoder is enabled.
  - isDisabled()                 Checks if the rotary encoder is disabled.
  - setGroup(&group)             Register the potentiometer to a group.
  - setInteger("id", 0)          Define an integer. First parameter is the name of the variable, second parameter is the value.
  - setString("name", "Button")  Define a string. First parameter is the name of the variable, second parameter is the value.
  - setBoolean("active", true)   Define a boolean. First parameter is the name of the variable, second parameter is the value.
  - getInteger("id")             Get the value of an integer.
  - getString("name")            Get the value of a string.
  - getBoolean("active")         Get the value of a boolean.
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

// Create a rotary encoder with the clk signal pin number, dt signal pin number,
// onTurnleft & onTurnRight handler.
CtrlEnc encoder(1, 2, onTurnleft, onTurnRight);

void setup() {
  Serial.begin(9600);
  
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