#include <Arduino.h>
#include <CtrlEnc.h>
#include <CtrlMux.h>
#include <unity.h>
#include "test_globals.h"

// Define an onTurnLeft handler
void onTurnLeftHandlerMuxEncoder() {
    encoderHandlerResult = "mux encoder turn left";
}

// Define an onTurnRight handler
void onTurnRighthandlerMuxEncoder() {
    encoderHandlerResult = "mux encoder turn right";
}

void test_rotary_encoders_can_be_multiplexed()
{
    CtrlMux mux(1, 2, 3, 4, 5);

    CtrlEnc encoder(
        0,
        1,
        onTurnLeftHandlerMuxEncoder,
        onTurnRighthandlerMuxEncoder
    );

    encoder.setMultiplexer(&mux);

    // Reset the state
    encoderHandlerResult = "";
    mockMuxEncClkInput = LOW;
    mockMuxEncDtInput = LOW;

    // Call process multiple times to allow for processing
    for (int i = 0; i < 10000; ++i) {
        mux.process();
    }

    // Simulate the sequence for a counterclockwise turn
    mockMuxEncClkInput = LOW;
    mockMuxEncDtInput = HIGH;

    // Call process multiple times to allow for processing
    for (int i = 0; i < 10000; ++i) {
        mux.process();
    }

    mockMuxEncClkInput = HIGH;
    mockMuxEncDtInput = HIGH;

    // Call process multiple times to allow for processing
    for (int i = 0; i < 10000; ++i) {
        mux.process();
    }

    TEST_ASSERT_EQUAL_STRING("mux encoder turn left", encoderHandlerResult.c_str()); // Verify the encoder has turned left
}