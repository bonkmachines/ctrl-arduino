#include <Arduino.h>
#include <unity.h>
#include "CtrlPot.h"
#include "test_globals.h"

static void test_potentiometer_common_can_be_disabled_and_enabled()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);

    potentiometer.disable();
    potentiometer.process();
    TEST_ASSERT_TRUE(potentiometer.isDisabled());

    potentiometer.enable();
    TEST_ASSERT_TRUE(potentiometer.isEnabled());
}

static void test_potentiometer_common_can_be_turned()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);

    _mock_analog_pins()[POT_PIN] = 512;

    converge(
        [&]{ potentiometer.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        50
    );

    TEST_ASSERT_EQUAL_INT(50, potentiometer.getValue());
}

static void test_potentiometer_disabled_ignores_input()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY, [](int val){ tracker.recordValueChange(val); });

    converge(
        [&]{ potentiometer.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        0
    );
    tracker.reset();

    potentiometer.disable();
    _mock_analog_pins()[POT_PIN] = 1023;

    for (int i = 0; i < 200; ++i) {
        potentiometer.process();
    }

    TEST_ASSERT_EQUAL_INT(0, tracker.valueChangeCount);
    TEST_ASSERT_EQUAL_INT(0, potentiometer.getValue());
}

static void test_potentiometer_set_raw_value()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY, [](int val){ tracker.recordValueChange(val); });

    for (int i = 0; i < POT_MAX_ITERATIONS; ++i) {
        potentiometer.setRawValue(1023);
        if (potentiometer.getValue() == 100) break;
    }

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue());
    TEST_ASSERT_TRUE(tracker.valueChangeCount > 0);
}

static void test_potentiometer_set_raw_value_disabled_ignored()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY, [](int val){ tracker.recordValueChange(val); });

    potentiometer.setRawValue(0);
    potentiometer.disable();

    for (int i = 0; i < 200; ++i) {
        potentiometer.setRawValue(1023);
    }

    TEST_ASSERT_EQUAL_INT(0, potentiometer.getValue());
    TEST_ASSERT_EQUAL_INT(0, tracker.valueChangeCount);
}

static void test_potentiometer_store_raw_converges()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY, [](int val){ tracker.recordValueChange(val); });

    for (int i = 0; i < POT_MAX_ITERATIONS; ++i) {
        potentiometer.storeRaw(1023);
        potentiometer.process();
        if (potentiometer.getValue() == 100) break;
    }

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue());
    TEST_ASSERT_TRUE(tracker.valueChangeCount > 0);
}

static void test_potentiometer_store_raw_disabled_ignored()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY, [](int val){ tracker.recordValueChange(val); });

    potentiometer.storeRaw(0);
    potentiometer.process();
    potentiometer.disable();

    for (int i = 0; i < 200; ++i) {
        potentiometer.storeRaw(1023);
        potentiometer.process();
    }

    TEST_ASSERT_EQUAL_INT(0, potentiometer.getValue());
    TEST_ASSERT_EQUAL_INT(0, tracker.valueChangeCount);
}

static void test_potentiometer_store_raw_process_uses_isr_branch()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);

    _mock_analog_pins()[POT_PIN] = 0;

    converge(
        [&]{
            potentiometer.storeRaw(1023);
            potentiometer.process();
        },
        [&]{ return (int)potentiometer.getValue(); },
        100
    );

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue());
}

static void test_potentiometer_get_max_output_value()
{
    CtrlPot potentiometer(POT_PIN, 1023, TEST_SENSITIVITY);
    TEST_ASSERT_EQUAL_INT(1023, potentiometer.getMaxOutputValue());
}

static void test_potentiometer_get_percentage()
{
    CtrlPot potentiometer(POT_PIN, 1023, TEST_SENSITIVITY);
    TEST_ASSERT_EQUAL_INT(0, potentiometer.getPercentage());

    // Above 655 a 16-bit `value * 100` would overflow; the percentage must stay correct.
    converge(
        [&]{ potentiometer.setRawValue(1023); },
        [&]{ return (int)potentiometer.getValue(); },
        1023
    );
    TEST_ASSERT_EQUAL_INT(1023, potentiometer.getValue());
    TEST_ASSERT_EQUAL_INT(100, potentiometer.getPercentage());

    converge(
        [&]{ potentiometer.setRawValue(767); },
        [&]{ return (int)potentiometer.getValue(); },
        767
    );
    TEST_ASSERT_EQUAL_INT(74, potentiometer.getPercentage());
}

static void test_potentiometer_get_percentage_with_zero_max_output_value()
{
    CtrlPot potentiometer(POT_PIN, 0, TEST_SENSITIVITY);
    potentiometer.setRawValue(1023);
    TEST_ASSERT_EQUAL_INT(0, potentiometer.getPercentage());
}

void run_potentiometer_common_tests()
{
    RUN_TEST(test_potentiometer_get_max_output_value);
    RUN_TEST(test_potentiometer_get_percentage);
    RUN_TEST(test_potentiometer_get_percentage_with_zero_max_output_value);
    RUN_TEST(test_potentiometer_common_can_be_disabled_and_enabled);
    RUN_TEST(test_potentiometer_common_can_be_turned);
    RUN_TEST(test_potentiometer_disabled_ignores_input);
    RUN_TEST(test_potentiometer_set_raw_value);
    RUN_TEST(test_potentiometer_set_raw_value_disabled_ignored);
    RUN_TEST(test_potentiometer_store_raw_converges);
    RUN_TEST(test_potentiometer_store_raw_disabled_ignored);
    RUN_TEST(test_potentiometer_store_raw_process_uses_isr_branch);
}
