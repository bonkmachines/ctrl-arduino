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
  - process()            Is used to poll the rotary encoder and handle all it's functionality (used in the loop method).
  - setOnTurnLeft()      Sets the onTurnleft handler. Is called when you turn left.
  - setOnTurnRight()     Sets the onTurnRight handler. Is called when you turn right.
  - setMultiplexer(&mux) Sets the multiplexer that the rotary encoder subscribes to.
  - disable()            Disables the rotary encoder.
  - enable()             Enables the rotary encoder.
  - isEnabled()          Checks if the rotary encoder is enabled.
  - isDisabled()         Checks if the rotary encoder is disabled.
*/

#include <CtrlEnc.h>

// Extend the CtrlEnc class into a CustomEncoder class.
class CustomEncoder : public CtrlEnc
{
  public:
    CustomEncoder(uint8_t sig, uint8_t bounceDuration) : CtrlEnc(sig, bounceDuration) { }

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

// Crete a rotary encoder with the signal pin number & bounce duration.
CustomEncoder encoder(33, 34);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // The process method will poll the rotary encoder object and handle all it's functionality.
  encoder.process();
}