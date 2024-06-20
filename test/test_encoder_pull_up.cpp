#include <Arduino.h>
#include <unity.h>
#include "CtrlEnc.h"
#include "test_globals.h"

// Define an onTurnLeft handler
void onTurnLeftHandlerPullUp() {
    encoderHandlerResult = "pull up encoder turn left";
}

// Define an onTurnRight handler
void onTurnRighthandlerPullUp() {
    encoderHandlerResult = "pull up encoder turn right";
}

void test_encoder_internal_pull_up_can_be_turned_left()
{
    CtrlEnc encoder(
        1,
        2,
        onTurnLeftHandlerPullUp,
        onTurnRighthandlerPullUp
    );

    encoder.setPinMode(INPUT_PULLUP);

    // Reset the state
    encoderHandlerResult = "";
    mockClkInput = LOW;
    mockDtInput = LOW;

    encoder.process(); // Process internal state

    // Simulate the sequence for a counterclockwise turn
    mockClkInput = LOW;
    mockDtInput = HIGH;
    encoder.process(); // Process internal state
    mockClkInput = HIGH;
    mockDtInput = HIGH;
    encoder.process(); // Process internal state

    TEST_ASSERT_EQUAL_STRING("pull up encoder turn left", encoderHandlerResult.c_str()); // Verify the encoder has turned left
}

void test_encoder_internal_pull_up_can_be_turned_right()
{
    CtrlEnc encoder(
        1,
        2,
        onTurnLeftHandlerPullUp,
        onTurnRighthandlerPullUp
    );

    encoder.setPinMode(INPUT_PULLUP);

    // Reset the state
    encoderHandlerResult = "";
    mockClkInput = LOW;
    mockDtInput = LOW;

    encoder.process(); // Process internal state

    // Simulate the sequence for a clockwise turn
    mockClkInput = HIGH;
    mockDtInput = LOW;
    encoder.process(); // Process internal state
    mockClkInput = HIGH;
    mockDtInput = HIGH;
    encoder.process(); // Process internal state

    TEST_ASSERT_EQUAL_STRING("pull up encoder turn right", encoderHandlerResult.c_str()); // Verify the encoder has turned right
}

void test_encoder_external_pull_up_can_be_turned_left()
{
    CtrlEnc encoder(
        1,
        2,
        onTurnLeftHandlerPullUp,
        onTurnRighthandlerPullUp
    );

    encoder.setPinMode(INPUT, PULL_UP);

    // Reset the state
    encoderHandlerResult = "";
    mockClkInput = LOW;
    mockDtInput = LOW;

    encoder.process(); // Process internal state

    // Simulate the sequence for a counterclockwise turn
    mockClkInput = LOW;
    mockDtInput = HIGH;
    encoder.process(); // Process internal state
    mockClkInput = HIGH;
    mockDtInput = HIGH;
    encoder.process(); // Process internal state

    TEST_ASSERT_EQUAL_STRING("pull up encoder turn left", encoderHandlerResult.c_str()); // Verify the encoder has turned left
}

void test_encoder_external_pull_up_can_be_turned_right()
{
    CtrlEnc encoder(
        1,
        2,
        onTurnLeftHandlerPullUp,
        onTurnRighthandlerPullUp
    );

    encoder.setPinMode(INPUT, PULL_UP);

    // Reset the state
    encoderHandlerResult = "";
    mockClkInput = LOW;
    mockDtInput = LOW;

    encoder.process(); // Process internal state

    // Simulate the sequence for a clockwise turn
    mockClkInput = HIGH;
    mockDtInput = LOW;
    encoder.process(); // Process internal state
    mockClkInput = HIGH;
    mockDtInput = HIGH;
    encoder.process(); // Process internal state

    TEST_ASSERT_EQUAL_STRING("pull up encoder turn right", encoderHandlerResult.c_str()); // Verify the encoder has turned right
}