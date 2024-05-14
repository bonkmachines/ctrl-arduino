/*
  Advanced button example

  Description:
  This sketch demonstrates an more advanced implementation of a button or switch,
  with debouncing functionality for noisy buttons.

  With this approach you can extend the base class (CtrlBtnBase) into your own class,
  and expand on the base functionality as you please. The sky is the limit here.
  The inheriting class overrides the onPress & onRelease methods. Within these
  methods you can add your desired actions.

  Usage:
  Extend the CtrlBtnBase class into your own custom class. Override the onPress() & 
  onRelease() methods and add any additional functionality that you need.

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

// Extend the CtrlBtnBase class into a CustomButton class
class CustomButton : public CtrlBtnBase
{
  public:
    CustomButton(uint8_t sig, uint8_t bounceDuration) : CtrlBtnBase(sig, bounceDuration) { }

  private:
    void onPress() override
    {
      Serial.println("Advanced button pressed");
    }

    void onRelease() override
    {
      Serial.println("Advanced button released");
    }
};

// Instantiate a button with the signal pin number & bounce duration
CustomButton button(36, 15);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // The process method will poll the button object and handle all it's functionality
  button.process();
}
