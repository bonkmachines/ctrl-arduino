#include <Arduino.h>
#include <unity.h>
#include "CtrlEnc.h"
#include "test_globals.h"

class CustomEncoder final : public CtrlEnc
{
    public:
        CustomEncoder(
            const uint8_t clk,
            const uint8_t dt
        ) : CtrlEnc(clk, dt) { }

    private:
        void onTurnLeft() override
        {
            encoderHandlerResult = "advanced encoder turn left";
        }

        void onTurnRight() override
        {
            encoderHandlerResult = "advanced encoder turn right";
        }
};

void test_encoder_advanced_can_be_turned_left()
{
    CustomEncoder encoder(1, 2);

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

    TEST_ASSERT_EQUAL_STRING("advanced encoder turn left", encoderHandlerResult.c_str()); // Verify the encoder has turned left
}

void test_encoder_advanced_can_be_turned_right()
{
    CustomEncoder encoder(1, 2);

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

    TEST_ASSERT_EQUAL_STRING("advanced encoder turn right", encoderHandlerResult.c_str()); // Verify the encoder has turned right
}