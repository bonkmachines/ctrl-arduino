#include <Arduino.h>
#include <CtrlMux.h>
#include <CtrlPot.h>
#include <unity.h>
#include "test_globals.h"

static void test_potentiometers_can_be_multiplexed()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);

    CtrlPot potentiometer(0, 100, TEST_SENSITIVITY);

    potentiometer.setMultiplexer(&mux);

    _mock_analog_pins()[MUX_SIG_PIN] = 1023;

    converge(
        [&]{ mux.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        100
    );

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue());
}

static void test_multiplexed_potentiometer_selects_its_channel()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);
    CtrlPot potentiometer(5, 100, TEST_SENSITIVITY); // Channel 5 = 0b0101
    potentiometer.setMultiplexer(&mux);

    mux.process();

    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(MUX_S0_PIN));
    TEST_ASSERT_EQUAL_INT(LOW, digitalRead(MUX_S1_PIN));
    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(MUX_S2_PIN));
    TEST_ASSERT_EQUAL_INT(LOW, digitalRead(MUX_S3_PIN));
}

static void test_multiplexed_potentiometer_selects_highest_channel()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);
    CtrlPot potentiometer(15, 100, TEST_SENSITIVITY); // Channel 15 = 0b1111
    potentiometer.setMultiplexer(&mux);

    mux.process();

    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(MUX_S0_PIN));
    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(MUX_S1_PIN));
    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(MUX_S2_PIN));
    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(MUX_S3_PIN));
}

static void test_three_select_pin_mux_leaves_s3_untouched()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN); // 8-channel mux, no S3
    CtrlPot potentiometer(7, 100, TEST_SENSITIVITY); // Channel 7 = 0b111
    potentiometer.setMultiplexer(&mux);

    _mock_digital_pins()[MUX_S3_PIN] = 42; // Sentinel: must not be written

    mux.process();

    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(MUX_S0_PIN));
    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(MUX_S1_PIN));
    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(MUX_S2_PIN));
    TEST_ASSERT_EQUAL_INT(42, digitalRead(MUX_S3_PIN));
}

void run_multiplexer_potentiometer_tests()
{
    RUN_TEST(test_potentiometers_can_be_multiplexed);
    RUN_TEST(test_multiplexed_potentiometer_selects_its_channel);
    RUN_TEST(test_multiplexed_potentiometer_selects_highest_channel);
    RUN_TEST(test_three_select_pin_mux_leaves_s3_untouched);
}
