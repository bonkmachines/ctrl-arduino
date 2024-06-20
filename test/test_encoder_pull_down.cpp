#include <Arduino.h>
#include <unity.h>
#include "CtrlEnc.h"
#include "test_globals.h"

// Define an onTurnLeft handler
void onTurnLeftHandlerPullDown() {
    encoderHandlerResult = "pull down encoder turn left";
}

// Define an onTurnRight handler
void onTurnRighthandlerPullDown() {
    encoderHandlerResult = "pull down encoder turn right";
}

void test_encoder_internal_pull_down_can_be_turned_left()
{
    CtrlEnc encoder(
        1,
        2,
        onTurnLeftHandlerPullDown,
        onTurnRighthandlerPullDown
    );

    encoder.setPinMode(INPUT_PULLDOWN);

    // Reset the state
    encoderHandlerResult = "";
    mockClkInput = HIGH;
    mockDtInput = HIGH;

    encoder.process(); // Process internal state

    // Simulate the sequence for a counterclockwise turn
    mockClkInput = HIGH;
    mockDtInput = LOW;
    encoder.process(); // Process internal state
    mockClkInput = LOW;
    mockDtInput = LOW;
    encoder.process(); // Process internal state

    TEST_ASSERT_EQUAL_STRING("pull down encoder turn left", encoderHandlerResult.c_str()); // Verify the encoder has turned left
}

void test_encoder_internal_pull_down_can_be_turned_right()
{
    CtrlEnc encoder(
        1,
        2,
        onTurnLeftHandlerPullDown,
        onTurnRighthandlerPullDown
    );

    encoder.setPinMode(INPUT_PULLDOWN);

    // Reset the state
    encoderHandlerResult = "";
    mockClkInput = HIGH;
    mockDtInput = HIGH;

    encoder.process(); // Process internal state

    // Simulate the sequence for a clockwise turn
    mockClkInput = LOW;
    mockDtInput = HIGH;
    encoder.process(); // Process internal state
    mockClkInput = LOW;
    mockDtInput = LOW;
    encoder.process(); // Process internal state

    TEST_ASSERT_EQUAL_STRING("pull down encoder turn right", encoderHandlerResult.c_str()); // Verify the encoder has turned right
}

void test_encoder_external_pull_down_can_be_turned_left()
{
    CtrlEnc encoder(
        1,
        2,
        onTurnLeftHandlerPullDown,
        onTurnRighthandlerPullDown
    );

    encoder.setPinMode(INPUT, PULL_DOWN);

    // Reset the state
    encoderHandlerResult = "";
    mockClkInput = HIGH;
    mockDtInput = HIGH;

    encoder.process(); // Process internal state

    // Simulate the sequence for a counterclockwise turn
    mockClkInput = HIGH;
    mockDtInput = LOW;
    encoder.process(); // Process internal state
    mockClkInput = LOW;
    mockDtInput = LOW;
    encoder.process(); // Process internal state

    TEST_ASSERT_EQUAL_STRING("pull down encoder turn left", encoderHandlerResult.c_str()); // Verify the encoder has turned left
}

void test_encoder_external_pull_down_can_be_turned_right()
{
    CtrlEnc encoder(
        1,
        2,
        onTurnLeftHandlerPullDown,
        onTurnRighthandlerPullDown
    );

    encoder.setPinMode(INPUT, PULL_DOWN);

    // Reset the state
    encoderHandlerResult = "";
    mockClkInput = HIGH;
    mockDtInput = HIGH;

    encoder.process(); // Process internal state

    // Simulate the sequence for a clockwise turn
    mockClkInput = LOW;
    mockDtInput = HIGH;
    encoder.process(); // Process internal state
    mockClkInput = LOW;
    mockDtInput = LOW;
    encoder.process(); // Process internal state

    TEST_ASSERT_EQUAL_STRING("pull down encoder turn right", encoderHandlerResult.c_str()); // Verify the encoder has turned right
}