#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

// Define an onPress handler
void onPressHandlerAlternative() {
    buttonHandlerResult = "alternative button pressed";
}

// Define an onRelease handler
void onReleasehandlerAlternative() {
    buttonHandlerResult = "alternative button released";
}

void test_button_alternative_can_be_pressed_and_released()
{
    CtrlBtn button(1, 15);

    // Register the handlers
    button.setOnPress(onPressHandlerAlternative);
    button.setOnRelease(onReleasehandlerAlternative);

    buttonHandlerResult = ""; // Reset
    mockButtonInput = HIGH; // Reset

    button.process(); // Process internal state

    mockButtonInput = LOW; // Simulate button press
    button.process(); // Process internal state
    delay(15 + 1); // Wait more than the debounce duration
    button.process(); // Second call to ensure debounce logic has completed

    TEST_ASSERT_EQUAL_STRING("alternative button pressed", buttonHandlerResult.c_str()); // Verify the button's on press handler has been called

    mockButtonInput = HIGH; // Simulate button release
    button.process(); // Process internal state
    delay(15 + 1); // Ensure debounce time has passed
    button.process(); // Second call to complete debounce logic

    TEST_ASSERT_EQUAL_STRING("alternative button released", buttonHandlerResult.c_str()); // Verify the button's on release handler has been called
}