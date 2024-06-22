/*
  Advanced button example

  Description:
  This sketch demonstrates a more advanced implementation of a button or switch,
  with debouncing functionality for noisy buttons.

  With this approach you can extend the button class (CtrlBtn) into your own class,
  and expand on the base functionality as you please. The sky is the limit here.
  The inheriting class overrides the onPress & onRelease methods. Within these
  methods you can add your desired actions.

  Usage:
  Extend the CtrlBtn class into your own custom class. Override the onPress() &
  onRelease() methods and add any additional functionality that you need.

  Available methods:
  - setPinMode(INPUT, PULL_UP)      The first parameter can be set to 'INPUT', 'INPUT_PULLUP' or 'INPUT_PULLDOWN'.
                                    If this method is not used, the default mode is: 'INPUT_PULLUP' and the
                                    internal pull-up resistor of the pin will be used. If the first parameter is
                                    set to 'INPUT', you will have to implement an external pull-down or pull-up
                                    resistor. You should then set the second parameter to 'PULL_DOWN' or 'PULL_UP'.
  - process()                       Is used to poll the button and handle all it's functionality  (used in the loop method).
  - setOnPress()                    Sets the onPress handler. Is called when the button is pressed.
  - setOnRelease()                  Sets the onRelease handler. Is called when the button is released.
  - setOnDelayedRelease()           Sets the onDelayedRelease handler. Is called when the button is
                                    released after a certain amount of time (The default is 500ms).
  - setDelayedReleaseDuration(500)  Sets the amount of time for a delayed release (in milliseconds).
  - setMultiplexer(&mux)            Sets the multiplexer that the button subscribes to.
  - disable()                       Disables the button.
  - enable()                        Enables the button.
  - isEnabled()                     Checks if the button is enabled.
  - isDisabled()                    Checks if the button is disabled.
  - isPressed()                     Checks if the button is currently being pressed.
  - isReleased()                    Checks if the button is currently not being pressed.
*/

#include <CtrlBtn.h>

// Extend the CtrlBtn class into a CustomButton class.
class CustomButton : public CtrlBtn
{
  public:
    CustomButton(uint8_t sig, uint8_t bounceDuration) : CtrlBtn(sig, bounceDuration) { }

  protected:
    void onPress() override
    {
      Serial.println("Advanced button pressed");
    }

    void onRelease() override
    {
      Serial.println("Advanced button released");
    }
};

// Create a button with the signal pin number & bounce duration.
CustomButton button(36, 15);

void setup() {
  Serial.begin(9600);
  // If you use an external pull-up resistor, uncomment this:
  // button.setPinMode(INPUT, PULL_UP);
  // If you use an external pull-down resistor, uncomment this:
  // button.setPinMode(INPUT, PULL_DOWN);
}

void loop() {
  // The process method will poll the button object and handle all it's functionality.
  button.process();
}