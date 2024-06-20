#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

// Define an onPress handler
void onPressHandlerPullDown() {
    buttonHandlerResult = "pull down button pressed";
}

// Define an onRelease handler
void onReleasehandlerPullDown() {
    buttonHandlerResult = "pull down button released";
}

void test_button_internal_pull_down_can_be_pressed_and_released()
{
    CtrlBtn button(
        1,
        15,
        onPressHandlerPullDown,
        onReleasehandlerPullDown
    );

    button.setPinMode(INPUT_PULLDOWN);

    buttonHandlerResult = ""; // Reset
    mockButtonInput = LOW; // Reset
    button.process(); // Process internal state

    mockButtonInput = HIGH; // Simulate button press
    button.process(); // Process internal state
    delay(15 + 1); // Wait more than the debounce duration
    button.process(); // Second call to ensure debounce logic has completed

    TEST_ASSERT_EQUAL_STRING("pull down button pressed", buttonHandlerResult.c_str()); // Verify the button's on press handler has been called

    mockButtonInput = LOW; // Simulate button release
    button.process(); // Process internal state
    delay(15 + 1); // Ensure debounce time has passed
    button.process(); // Second call to complete debounce logic

    TEST_ASSERT_EQUAL_STRING("pull down button released", buttonHandlerResult.c_str()); // Verify the button's on release handler has been called
}

void test_button_external_pull_down_can_be_pressed_and_released()
{
    CtrlBtn button(
        1,
        15,
        onPressHandlerPullDown,
        onReleasehandlerPullDown
    );

    button.setPinMode(INPUT, PULL_DOWN);

    buttonHandlerResult = ""; // Reset
    mockButtonInput = LOW; // Reset
    button.process(); // Process internal state

    mockButtonInput = HIGH; // Simulate button press
    button.process(); // Process internal state
    delay(15 + 1); // Wait more than the debounce duration
    button.process(); // Second call to ensure debounce logic has completed

    TEST_ASSERT_EQUAL_STRING("pull down button pressed", buttonHandlerResult.c_str()); // Verify the button's on press handler has been called

    mockButtonInput = LOW; // Simulate button release
    button.process(); // Process internal state
    delay(15 + 1); // Ensure debounce time has passed
    button.process(); // Second call to complete debounce logic

    TEST_ASSERT_EQUAL_STRING("pull down button released", buttonHandlerResult.c_str()); // Verify the button's on release handler has been called
}