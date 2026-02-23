#include <Arduino.h>
#include <unity.h>
#include "CtrlEnc.h"
#include "test_globals.h"

static void test_encoder_common_initial_state()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN);

    encoder.process();

    TEST_ASSERT_FALSE(encoder.isTurningLeft());
    TEST_ASSERT_FALSE(encoder.isTurningRight());
}

static void test_encoder_common_can_be_disabled_and_enabled()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN);

    encoder.disable();
    encoder.process();
    TEST_ASSERT_TRUE(encoder.isDisabled());

    encoder.enable();
    encoder.process();
    TEST_ASSERT_TRUE(encoder.isEnabled());
}

static void test_encoder_disabled_ignores_input()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });

    encoder.process();
    encoder.disable();

    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL_INT(0, tracker.turnLeftCount);
    TEST_ASSERT_EQUAL_INT(0, tracker.eventCount);
}

static void test_encoder_rapid_turn_cycles()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });

    encoder.process();

    for (int cycle = 0; cycle < 100; ++cycle) {
        _mock_digital_pins()[ENC_DT_PIN] = HIGH;
        encoder.process();
        _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
        encoder.process();

        _mock_digital_pins()[ENC_CLK_PIN] = LOW;
        _mock_digital_pins()[ENC_DT_PIN] = LOW;
        encoder.process();
    }

    TEST_ASSERT_EQUAL_INT(100, tracker.turnLeftCount);
}

static void test_encoder_set_pin_mode_invalid_type_ignored()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });

    encoder.setPinMode(99);

    encoder.process();

    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.turnLeftCount);
}

static void test_encoder_set_pin_mode_invalid_resistor_ignored()
{
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });

    encoder.setPinMode(INPUT, 99);

    encoder.process();

    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encoder.process();
    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encoder.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.turnLeftCount);
}

void run_encoder_common_tests()
{
    RUN_TEST(test_encoder_common_initial_state);
    RUN_TEST(test_encoder_common_can_be_disabled_and_enabled);
    RUN_TEST(test_encoder_disabled_ignores_input);
    RUN_TEST(test_encoder_rapid_turn_cycles);
    RUN_TEST(test_encoder_set_pin_mode_invalid_type_ignored);
    RUN_TEST(test_encoder_set_pin_mode_invalid_resistor_ignored);
}
