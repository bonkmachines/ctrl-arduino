#include <Arduino.h>
#include <unity.h>
#include "CtrlEnc.h"
#include "test_globals.h"

// Define an onTurnLeft handler
void onTurnLeftHandlerAlternative() {
    encoderHandlerResult = "left";
}

// Define an onTurnRight handler
void onTurnRighthandlerAlternative() {
    encoderHandlerResult = "right";
}

void test_encoder_alternative_can_be_turned_left()
{
    CtrlEnc encoder = CtrlEnc::create(
        encoderClkSig,
        encoderDtSig
    );

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

    TEST_ASSERT_EQUAL_STRING("left", encoderHandlerResult.c_str()); // Verify the encoder has turned left
}

void test_encoder_alternative_can_be_turned_right()
{
    CtrlEnc encoder = CtrlEnc::create(
        encoderClkSig,
        encoderDtSig
    );

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

    TEST_ASSERT_EQUAL_STRING("right", encoderHandlerResult.c_str()); // Verify the encoder has turned right
}