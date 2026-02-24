#include <Arduino.h>
#include <unity.h>
#include "CtrlEnc.h"
#include "test_globals.h"

static void test_encoder_internal_pull_up_can_be_turned_left()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });
    encoder.setPinMode(INPUT_PULLUP);

    encoder.process();

    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedLeft, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnLeftCount);
}

static void test_encoder_internal_pull_up_can_be_turned_right()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });
    encoder.setPinMode(INPUT_PULLUP);

    encoder.process();

    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedRight, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnRightCount);
}

static void test_encoder_external_pull_up_can_be_turned_left()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });
    encoder.setPinMode(INPUT, PULL_UP);

    encoder.process();

    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedLeft, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnLeftCount);
}

static void test_encoder_external_pull_up_can_be_turned_right()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });
    encoder.setPinMode(INPUT, PULL_UP);

    encoder.process();

    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedRight, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnRightCount);
}

void run_encoder_pull_up_tests()
{
    RUN_TEST(test_encoder_internal_pull_up_can_be_turned_left);
    RUN_TEST(test_encoder_internal_pull_up_can_be_turned_right);
    RUN_TEST(test_encoder_external_pull_up_can_be_turned_left);
    RUN_TEST(test_encoder_external_pull_up_can_be_turned_right);
}
