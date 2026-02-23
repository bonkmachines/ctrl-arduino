#include <Arduino.h>
#include <unity.h>
#include "CtrlEnc.h"
#include "test_globals.h"

static void test_encoder_basic_can_be_turned_left()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });

    encoder.process();

    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedLeft, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnLeftCount);
}

static void test_encoder_basic_can_be_turned_right()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });

    encoder.process();

    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedRight, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnRightCount);
}

void run_encoder_basic_tests()
{
    RUN_TEST(test_encoder_basic_can_be_turned_left);
    RUN_TEST(test_encoder_basic_can_be_turned_right);
}
