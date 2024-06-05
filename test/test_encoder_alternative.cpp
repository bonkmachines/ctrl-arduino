#include <Arduino.h>
#include <unity.h>
#include "CtrlEnc.h"
#include "test_globals.h"

// Define an onTurnLeft handler
void onTurnLeftHandlerAlternative() {
    encoderHandlerResult = "alternative encoder turn left";
}

// Define an onTurnRight handler
void onTurnRighthandlerAlternative() {
    encoderHandlerResult = "alternative encoder turn right";
}

void test_encoder_alternative_can_be_turned_left()
{
    CtrlEnc encoder(1, 2);

    encoder.setOnTurnLeft(onTurnLeftHandlerAlternative);
    encoder.setOnTurnRight(onTurnRighthandlerAlternative);

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

    TEST_ASSERT_EQUAL_STRING("alternative encoder turn left", encoderHandlerResult.c_str()); // Verify the encoder has turned left
}

void test_encoder_alternative_can_be_turned_right()
{
    CtrlEnc encoder(1, 2);

    encoder.setOnTurnLeft(onTurnLeftHandlerAlternative);
    encoder.setOnTurnRight(onTurnRighthandlerAlternative);

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

    TEST_ASSERT_EQUAL_STRING("alternative encoder turn right", encoderHandlerResult.c_str()); // Verify the encoder has turned right
}