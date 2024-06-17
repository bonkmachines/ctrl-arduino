#include <Arduino.h>
#include <unity.h>
#include "CtrlEnc.h"
#include "test_globals.h"

void test_encoder_common_initial_state()
{
    CtrlEnc encoder(1, 2);

    // Reset the state
    mockClkInput = LOW;
    mockDtInput = LOW;

    encoder.process(); // Process internal state

    TEST_ASSERT_FALSE(encoder.isTurningLeft()); // Encoder should not be turning left
    TEST_ASSERT_FALSE(encoder.isTurningRight()); // Encoder should not be turning right
}

void test_encoder_common_can_be_disabled_and_enabled()
{
    CtrlEnc encoder(1, 2);

    encoder.disable(); // Disable the encoder
    encoder.process(); // Process internal state

    TEST_ASSERT_TRUE(encoder.isDisabled()); // Encoder should be disabled

    encoder.enable(); // Enable the encoder
    encoder.process(); // Process internal state

    TEST_ASSERT_TRUE(encoder.isEnabled()); // Encoder should be enabled
}