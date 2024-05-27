/*
  Advanced potentiometer example

  Description:
  This sketch demonstrates the advanced implementation of a potentiometer.

  With this approach you can extend the base class (CtrlPotBase) into your own class,
  and expand on the base functionality as you please. The sky is the limit here.
  The inheriting class overrides the onValueChange method. Within this method
  you can add your desired actions.

  Usage:
  Extend the CtrlPotBase class into your own custom class. Override the
  onValueChange() method and add any additional functionality that you need.

  Available methods:
  - process()           Is used to poll the potentiometer and handle all it's functionality (used in the loop method).
  - getValue()          Retrieves the current value of the potentiometer.
  - setOnValueChange()  Sets the onValueChange handler. Will be called as soon as the reading of the potentiometer changes.
  - setMultiplexer()    Sets the multiplexer that the potentiometer subscribes to.
  - disable()           Disables the potentiometer.
  - enable()            Enables the potentiometer.
  - isEnabled()         Checks if the potentiometer is enabled.
  - isDisabled()        Checks if the potentiometer is disabled.
*/

#include <CtrlPot.h>

class CustomPot : public CtrlPotBase
{
  public:
    CustomPot(uint8_t sig, int maxOutputValue, float sensitivity) : CtrlPotBase(sig, maxOutputValue, sensitivity) { }

  private:
    void onValueChange(int value) override
    {
      Serial.print("Advanced pot value: ");
      Serial.println(value);
    }
};

// Instantiate a potentiometer with the pin number, max. output value & sensitivity margin (can be 0.01 to 100).
CustomPot potentiometer(24, 100, 0.05);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // The process method will keep polling our potentiometer object and handle all it's functionality.
  potentiometer.process();
}