#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

void test_button_common_initial_state()
{
    CtrlBtn button = CtrlBtn::create(buttonSig, buttonBounceDuration);

    mockButtonInput = HIGH; // Ensure the button is not pressed
    button.process(); // Process the current state

    TEST_ASSERT_FALSE(button.isPressed()); // Button should not be pressed
    TEST_ASSERT_TRUE(button.isReleased()); // Button should be released
}

void test_button_common_can_be_disabled_and_enabled()
{
    CtrlBtn button = CtrlBtn::create(buttonSig, buttonBounceDuration);

    button.disable(); // Disable the button
    button.process(); // Process internal state

    TEST_ASSERT_TRUE(button.isDisabled()); // Button should be disabled

    button.enable(); // Enable the button
    button.process(); // Process internal state

    TEST_ASSERT_TRUE(button.isEnabled()); // Button should be enabled
}

void test_button_common_can_be_pressed_and_released()
{
    CtrlBtn button = CtrlBtn::create(buttonSig, buttonBounceDuration);

    mockButtonInput = LOW; // Simulate button press
    button.process(); // Process internal state
    delay(buttonBounceDuration + 1); // Wait more than the debounce duration
    button.process(); // Second call to ensure debounce logic has completed

    TEST_ASSERT_TRUE(button.isPressed()); // Verify the button is currently pressed

    mockButtonInput = HIGH; // Simulate button release
    button.process(); // Process internal state
    delay(buttonBounceDuration + 1); // Ensure debounce time has passed
    button.process(); // Second call to complete debounce logic

    TEST_ASSERT_TRUE(button.isReleased()); // Verify the button is no longer currently pressed
}