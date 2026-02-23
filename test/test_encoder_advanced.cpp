#include <Arduino.h>
#include <unity.h>
#include "CtrlEnc.h"
#include "test_globals.h"

class TestEncoder final : public CtrlEnc
{
    public:
        TestEncoder(uint8_t clk, uint8_t dt) : CtrlEnc(clk, dt) {}

    private:
        void onTurnLeft() override { tracker.recordTurnLeft(); }
        void onTurnRight() override { tracker.recordTurnRight(); }
};

static void test_encoder_advanced_can_be_turned_left()
{
    TestEncoder encoder(ENC_CLK_PIN, ENC_DT_PIN);

    encoder.process();

    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedLeft, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnLeftCount);
}

static void test_encoder_advanced_can_be_turned_right()
{
    TestEncoder encoder(ENC_CLK_PIN, ENC_DT_PIN);

    encoder.process();

    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedRight, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnRightCount);
}

void run_encoder_advanced_tests()
{
    RUN_TEST(test_encoder_advanced_can_be_turned_left);
    RUN_TEST(test_encoder_advanced_can_be_turned_right);
}
