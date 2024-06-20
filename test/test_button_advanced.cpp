#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

class CustomButton final : public CtrlBtn
{
    public:
        CustomButton(
            const uint8_t sig,
            const uint8_t bounceDuration
        ) : CtrlBtn(sig, bounceDuration) { }

    private:
        void onPress() override
        {
            buttonHandlerResult = "advanced button pressed";
        }

        void onRelease() override
        {
            buttonHandlerResult = "advanced button released";
        }
};

void test_button_advanced_can_be_pressed_and_released()
{
    CustomButton button(1, 15);

    buttonHandlerResult = ""; // Reset
    mockButtonInput = HIGH; // Reset

    button.process(); // Process internal state

    mockButtonInput = LOW; // Simulate button press
    button.process(); // Process internal state
    delay(15 + 1); // Wait more than the debounce duration
    button.process(); // Second call to ensure debounce logic has completed

    TEST_ASSERT_EQUAL_STRING("advanced button pressed", buttonHandlerResult.c_str()); // Verify the button's on press handler has been called

    mockButtonInput = HIGH; // Simulate button release
    button.process(); // Process internal state
    delay(15 + 1); // Ensure debounce time has passed
    button.process(); // Second call to complete debounce logic

    TEST_ASSERT_EQUAL_STRING("advanced button released", buttonHandlerResult.c_str()); // Verify the button's on release handler has been called
}