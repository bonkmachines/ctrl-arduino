#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

class CustomButton final : public CtrlBtnBase
{
    public:
        CustomButton(const uint8_t sig, const uint8_t bounceDuration) : CtrlBtnBase(sig, bounceDuration) { }

    private:
        void onPress() override
        {
            buttonHandlerResult = "pressed";
        }

        void onRelease() override
        {
            buttonHandlerResult = "released";
        }
};

void test_button_advanced_can_be_pressed_and_released()
{
    CustomButton button(buttonSig, buttonBounceDuration);

    buttonHandlerResult = ""; // Reset

    mockButtonInput = LOW; // Simulate button press
    button.process(); // Process internal state
    delay(buttonBounceDuration + 1); // Wait more than the debounce duration
    button.process(); // Second call to ensure debounce logic has completed

    TEST_ASSERT_EQUAL_STRING("pressed", buttonHandlerResult.c_str()); // Verify the button's on press handler has been called

    mockButtonInput = HIGH; // Simulate button release
    button.process(); // Process internal state
    delay(buttonBounceDuration + 1); // Ensure debounce time has passed
    button.process(); // Second call to complete debounce logic

    TEST_ASSERT_EQUAL_STRING("released", buttonHandlerResult.c_str()); // Verify the button's on release handler has been called
}