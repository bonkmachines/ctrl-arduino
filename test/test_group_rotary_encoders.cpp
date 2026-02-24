#include <Arduino.h>
#include <unity.h>
#include "CtrlGroup.h"
#include "CtrlEnc.h"
#include "test_globals.h"

static void test_rotary_encoder_can_be_grouped()
{
    CtrlGroup encoderGroup;
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN);

    encoderGroup.setOnTurnLeft([](Groupable& enc) {
        TEST_ASSERT_TRUE(enc.getBoolean("active"));
        TEST_ASSERT_EQUAL_INT(10, enc.getInteger("id"));
        tracker.recordTurnLeft();
    });

    encoderGroup.setOnTurnRight([](Groupable& enc) {
        TEST_ASSERT_TRUE(enc.getBoolean("active"));
        TEST_ASSERT_EQUAL_INT(10, enc.getInteger("id"));
        tracker.recordTurnRight();
    });

    encoder.setGroup(&encoderGroup);
    encoder.setInteger("id", 10);
    encoder.setString("name", "testEnc");
    encoder.setBoolean("active", true);

    encoderGroup.process();

    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoderGroup.process();
    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoderGroup.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedLeft, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnLeftCount);

    _mock_digital_pins()[ENC_CLK_PIN] = LOW;
    _mock_digital_pins()[ENC_DT_PIN] = LOW;
    encoder.process();

    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedRight, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnRightCount);
}

void run_group_encoder_tests()
{
    RUN_TEST(test_rotary_encoder_can_be_grouped);
}
