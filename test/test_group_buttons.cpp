#include <Arduino.h>
#include <unity.h>
#include "CtrlGroup.h"
#include "CtrlBtn.h"
#include "test_globals.h"

void onButtonGroupPress(Groupable& button) {
    const int integer = button.getInteger("integer");
    const String string = button.getString("string");
    const bool boolean = button.getBoolean("boolean");
    if (boolean) {
        buttonHandlerResult = "Pressed: " + std::to_string(integer) + " " + string.c_str();
    }
}

void onButtonGroupRelease(Groupable& button) {
    const int integer = button.getInteger("integer");
    const String string = button.getString("string");
    const bool boolean = button.getBoolean("boolean");
    if (boolean) {
        buttonHandlerResult = "Released: " + std::to_string(integer) + " " + string.c_str();
    }
}

void test_button_can_be_grouped()
{
    CtrlGroup buttonGroup;

    CtrlBtn button(1, 15);

    buttonGroup.setOnPress(onButtonGroupPress);
    buttonGroup.setOnRelease(onButtonGroupRelease);

    button.setGroup(&buttonGroup);

    button.setInteger("integer", 10);
    button.setString("string", "Four");
    button.setBoolean("boolean", true);

    buttonHandlerResult = ""; // Reset
    mockButtonInput = HIGH; // Reset

    buttonGroup.process(); // Process internal state

    mockButtonInput = LOW; // Simulate button press
    buttonGroup.process(); // Process internal state
    delay(15 + 1); // Wait more than the debounce duration
    buttonGroup.process(); // Second call to ensure debounce logic has completed

    TEST_ASSERT_EQUAL_STRING("Pressed: 10 Four", buttonHandlerResult.c_str()); // Verify the button's on press handler has been called

    mockButtonInput = HIGH; // Simulate button release
    buttonGroup.process(); // Process internal state
    delay(15 + 1); // Ensure debounce time has passed
    buttonGroup.process(); // Second call to complete debounce logic

    TEST_ASSERT_EQUAL_STRING("Released: 10 Four", buttonHandlerResult.c_str()); // Verify the button's on release handler has been called
}