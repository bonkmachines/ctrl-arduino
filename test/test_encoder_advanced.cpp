#include <Arduino.h>
#include <unity.h>
#include "CtrlEnc.h"
#include "test_globals.h"

class CustomEncoder final : public CtrlEncBase
{
    public:
        CustomEncoder(const uint8_t clk, const uint8_t dt) : CtrlEncBase(clk, dt) { }

    private:
        void onTurnLeft() override
        {
            encoderHandlerResult = "left";
        }

        void onTurnRight() override
        {
            encoderHandlerResult = "right";
        }
};

void test_encoder_advanced_can_be_turned_left()
{
    CustomEncoder encoder(encoderClkSig, encoderDtSig);

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

void test_encoder_advanced_can_be_turned_right()
{
    CustomEncoder encoder(encoderClkSig, encoderDtSig);

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

    TEST_ASSERT_EQUAL_STRING("right", encoderHandlerResult.c_str()); // Verify the encoder has turned rigt
}