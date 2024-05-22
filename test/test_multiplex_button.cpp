#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

// Define an onPress handler
void onPressHandlerMuxButton() {
    buttonHandlerResult = "pressed";
}

// Define an onRelease handler
void onReleasehandlerMuxButton() {
    buttonHandlerResult = "released";
}

void test_button_can_be_multiplexed()
{
    CtrlMux mux(muxSig, muxS0, muxS1, muxS2, muxS3);

    CtrlBtn button = CtrlBtn::create(
        buttonSig,
        buttonBounceDuration,
        onPressHandlerMuxButton,
        onReleasehandlerMuxButton,
        &mux
    );

    buttonHandlerResult = ""; // Reset

    mockMuxDigitalInput = LOW; // Simulate button press
    button.process(); // Process internal state
    delay(buttonBounceDuration + 1); // Wait more than the debounce duration
    button.process(); // Second call to ensure debounce logic has completed

    TEST_ASSERT_EQUAL_STRING("pressed", buttonHandlerResult.c_str()); // Verify the button's on press handler has been called

    mockMuxDigitalInput = HIGH; // Simulate button release
    button.process(); // Process internal state
    delay(buttonBounceDuration + 1); // Ensure debounce time has passed
    button.process(); // Second call to complete debounce logic

    TEST_ASSERT_EQUAL_STRING("released", buttonHandlerResult.c_str()); // Verify the button's on release handler has been called
}