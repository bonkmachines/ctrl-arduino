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

static void test_potentiometer_get_normalized_linear()
{
    CtrlPot potentiometer(POT_PIN, 1000, TEST_SENSITIVITY);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, potentiometer.getNormalized());

    converge([&]{ potentiometer.setRawValue(1023); }, [&]{ return (int)potentiometer.getValue(); }, 1000);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0f, potentiometer.getNormalized());
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0f, potentiometer.getNormalized(CtrlTaper::Linear));

    converge([&]{ potentiometer.setRawValue(512); }, [&]{ return (int)potentiometer.getValue(); }, 500);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.5f, potentiometer.getNormalized());
}

static void test_potentiometer_get_normalized_tapers()
{
    CtrlPot potentiometer(POT_PIN, 1000, TEST_SENSITIVITY);

    // Both curves start at 0 and end at 1.
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, potentiometer.getNormalized(CtrlTaper::Log));
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, potentiometer.getNormalized(CtrlTaper::AntiLog));
    converge([&]{ potentiometer.setRawValue(1023); }, [&]{ return (int)potentiometer.getValue(); }, 1000);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0f, potentiometer.getNormalized(CtrlTaper::Log));
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0f, potentiometer.getNormalized(CtrlTaper::AntiLog));

    // Halfway: Log starts slow, AntiLog starts fast, and they mirror each other.
    converge([&]{ potentiometer.setRawValue(512); }, [&]{ return (int)potentiometer.getValue(); }, 500);
    const float log = potentiometer.getNormalized(CtrlTaper::Log);
    const float antiLog = potentiometer.getNormalized(CtrlTaper::AntiLog);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.091f, log);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.909f, antiLog);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0f, log + antiLog);
}

static void test_potentiometer_get_normalized_is_monotonic()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);
    float previousLog = -1.0f, previousAntiLog = -1.0f;
    for (int raw = 0; raw <= 1023; raw += 31) {
        converge([&]{ potentiometer.setRawValue(raw); }, [&]{ return (int)potentiometer.getValue(); },
                 (int)((raw * 100L + 511) / 1023));
        const float log = potentiometer.getNormalized(CtrlTaper::Log);
        const float antiLog = potentiometer.getNormalized(CtrlTaper::AntiLog);
        TEST_ASSERT_TRUE(log >= previousLog);
        TEST_ASSERT_TRUE(antiLog >= previousAntiLog);
        previousLog = log;
        previousAntiLog = antiLog;
    }
}

static void test_potentiometer_get_normalized_with_zero_max_output_value()
{
    CtrlPot potentiometer(POT_PIN, 0, TEST_SENSITIVITY);
    potentiometer.setRawValue(1023);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, potentiometer.getNormalized(CtrlTaper::Log));
}

static void test_potentiometer_has_changed()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);
    TEST_ASSERT_FALSE(potentiometer.hasChanged());

    converge([&]{ potentiometer.setRawValue(1023); }, [&]{ return (int)potentiometer.getValue(); }, 100);
    TEST_ASSERT_TRUE(potentiometer.hasChanged());
    TEST_ASSERT_FALSE(potentiometer.hasChanged()); // Reported once per change.

    // Same input again: no change to report.
    for (int i = 0; i < 50; ++i) potentiometer.setRawValue(1023);
    TEST_ASSERT_FALSE(potentiometer.hasChanged());

    converge([&]{ potentiometer.setRawValue(0); }, [&]{ return (int)potentiometer.getValue(); }, 0);
    TEST_ASSERT_TRUE(potentiometer.hasChanged());
}

static void test_potentiometer_has_changed_works_next_to_callback()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY, [](int val){ tracker.recordValueChange(val); });
    converge([&]{ potentiometer.setRawValue(1023); }, [&]{ return (int)potentiometer.getValue(); }, 100);
    TEST_ASSERT_TRUE(tracker.valueChangeCount > 0);
    TEST_ASSERT_TRUE(potentiometer.hasChanged());
}

void run_potentiometer_common_tests()
{
    RUN_TEST(test_potentiometer_get_normalized_linear);
    RUN_TEST(test_potentiometer_get_normalized_tapers);
    RUN_TEST(test_potentiometer_get_normalized_is_monotonic);
    RUN_TEST(test_potentiometer_get_normalized_with_zero_max_output_value);
    RUN_TEST(test_potentiometer_has_changed);
    RUN_TEST(test_potentiometer_has_changed_works_next_to_callback);
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
