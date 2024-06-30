#include <Arduino.h>
#include <unity.h>
#include "CtrlGroup.h"
#include "CtrlEnc.h"
#include "test_globals.h"

void onEncoderGroupTurnLeft(Groupable& encoder) {
    const int integer = encoder.getInteger("integer");
    const String string = encoder.getString("string");
    const bool boolean = encoder.getBoolean("boolean");
    if (boolean) {
        encoderHandlerResult = "Turn left: " + std::to_string(integer) + " " + string.c_str();
    }
}

void onEncoderGroupTurnRight(Groupable& encoder) {
    const int integer = encoder.getInteger("integer");
    const String string = encoder.getString("string");
    const bool boolean = encoder.getBoolean("boolean");
    if (boolean) {
        encoderHandlerResult = "Turn right: " + std::to_string(integer) + " " + string.c_str();
    }
}

void test_rotary_encoder_can_be_grouped()
{
    CtrlGroup encoderGroup;

    CtrlEnc encoder(1, 2);

    encoderGroup.setOnTurnLeft(onEncoderGroupTurnLeft);
    encoderGroup.setOnTurnRight(onEncoderGroupTurnRight);

    encoder.setGroup(&encoderGroup);

    encoder.setInteger("integer", 10);
    encoder.setString("string", "Four");
    encoder.setBoolean("boolean", true);

    // Reset the state
    encoderHandlerResult = "";
    mockClkInput = LOW;
    mockDtInput = LOW;

    encoderGroup.process(); // Process internal state

    // Simulate the sequence for a counterclockwise turn
    mockClkInput = LOW;
    mockDtInput = HIGH;
    encoderGroup.process(); // Process internal state
    mockClkInput = HIGH;
    mockDtInput = HIGH;
    encoderGroup.process(); // Process internal state

    TEST_ASSERT_EQUAL_STRING("Turn left: 10 Four", encoderHandlerResult.c_str()); // Verify the button's on press handler has been called

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

    TEST_ASSERT_EQUAL_STRING("Turn right: 10 Four", encoderHandlerResult.c_str()); // Verify the encoder has turned right
}