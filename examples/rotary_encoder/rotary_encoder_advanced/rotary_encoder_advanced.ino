/*
  Advanced rotary encoder example

  Description:
  This sketch demonstrates an more advanced implementation of a rotary encoder.

  With this approach you can extend the base class (CtrlEnc) into your own class,
  and expand on the base functionality as you please. The sky is the limit here.
  The inheriting class overrides the onPress & onRelease methods. Within these
  methods you can add your desired actions.

  Usage:
  Extend the CtrlEnc class into your own custom class. Override the onTurnLeft() &
  onTurnRight() methods and add any additional functionality that you need.

  Available methods:
  - setPinMode(INPUT, PULL_UP) The first parameter can be set to 'INPUT', 'INPUT_PULLUP' or 'INPUT_PULLDOWN'.
                               If this method is not used, the default mode is: 'INPUT_PULLUP' and (if available)
                               the internal pull-up resistor of the pin will be used. If the first parameter is
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

// Extend the CtrlEnc class into a CustomEncoder class.
class CustomEncoder : public CtrlEnc
{
  public:
    CustomEncoder(uint8_t clk, uint8_t dt) : CtrlEnc(clk, dt) { }

  protected:
    void onTurnLeft() override
    {
      Serial.println("Advanced rotary encoder turn left");
    }

    void onTurnRight() override
    {
      Serial.println("Advanced rotary encoder turn right");
    }
};

// Create a rotary encoder with the clk pin number & dt pin number.
CustomEncoder encoder(33, 34);

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