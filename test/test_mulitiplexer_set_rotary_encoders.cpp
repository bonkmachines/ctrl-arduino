#include <Arduino.h>
#include <CtrlEnc.h>
#include <CtrlMux.h>
#include <unity.h>
#include "test_globals.h"

// Define an onTurnLeft handler for encoder 1
void onTurnLeftHandlerMuxEncoder1() {
    encoderHandlerResult = "mux encoder 1 turn left";
}

// Define an onTurnRight handler for encoder 1
void onTurnRighthandlerMuxEncoder1() {
    encoderHandlerResult = "mux encoder 1 turn right";
}

// Define an onTurnLeft handler for encoder 2
void onTurnLeftHandlerMuxEncoder2() {
    encoderHandlerResult = "mux encoder 2 turn left";
}

// Define an onTurnRight handler for encoder 2
void onTurnRighthandlerMuxEncoder2() {
    encoderHandlerResult = "mux encoder 2 turn right";
}

void test_rotary_encoders_can_be_multiplexed_via_mux_set()
{
    CtrlMuxSet muxSet(2);

    CtrlMux mux1(2, 10, 1, 2, 3, 4, 5, &muxSet);
    CtrlMux mux2(2, 10, 2, 2, 3, 4, 5, &muxSet);

    CtrlEnc encoder1 = CtrlEnc::create(
        0,
        1,
        onTurnLeftHandlerMuxEncoder1,
        onTurnRighthandlerMuxEncoder1
    );

    CtrlEnc encoder2 = CtrlEnc::create(
        0,
        1,
        onTurnLeftHandlerMuxEncoder2,
        onTurnRighthandlerMuxEncoder2
    );

    encoder1.setMultiplexer(mux1);
    encoder2.setMultiplexer(mux2);

    // Test encoder 1 on mux 1

    // Reset the state
    encoderHandlerResult = "";

    mockMuxEncClkInput = LOW;
    mockMuxEncDtInput = LOW;

    // Call process multiple times to allow for processing
    for (int i = 0; i < 10000; ++i) {
        encoder1.process();
    }

    // Simulate the sequence for a counterclockwise turn
    mockMuxEncClkInput = LOW;
    mockMuxEncDtInput = HIGH;

    // Call process multiple times to allow for processing
    for (int i = 0; i < 10000; ++i) {
        encoder1.process();
    }

    mockMuxEncClkInput = HIGH;
    mockMuxEncDtInput = HIGH;

    // Call process multiple times to allow for processing
    for (int i = 0; i < 10000; ++i) {
        encoder1.process();
    }

    TEST_ASSERT_EQUAL_STRING("mux encoder 1 turn left", encoderHandlerResult.c_str()); // Verify the encoder has turned left

    // Test encoder 2 on mux 2

    // Reset the state
    encoderHandlerResult = "";

    mockMuxEncClkInput = LOW;
    mockMuxEncDtInput = LOW;

    // Call process multiple times to allow for processing
    for (int i = 0; i < 10000; ++i) {
        encoder2.process();
    }

    // Simulate the sequence for a counterclockwise turn
    mockMuxEncClkInput = LOW;
    mockMuxEncDtInput = HIGH;

    // Call process multiple times to allow for processing
    for (int i = 0; i < 10000; ++i) {
        encoder2.process();
    }

    mockMuxEncClkInput = HIGH;
    mockMuxEncDtInput = HIGH;

    // Call process multiple times to allow for processing
    for (int i = 0; i < 10000; ++i) {
        encoder2.process();
    }

    TEST_ASSERT_EQUAL_STRING("mux encoder 2 turn left", encoderHandlerResult.c_str()); // Verify the encoder has turned left
}