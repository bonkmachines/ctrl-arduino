#include <Arduino.h>
#include <unity.h>
#include "CtrlPot.h"
#include "test_globals.h"

static void test_potentiometer_alternative_can_be_turned_to_minimum()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);
    potentiometer.setOnValueChange([](int val){ tracker.recordValueChange(val); });

    _mock_analog_pins()[POT_PIN] = 1023;
    converge(
        [&]{ potentiometer.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        100
    );
    tracker.reset();

    _mock_analog_pins()[POT_PIN] = 0;

    converge(
        [&]{ potentiometer.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        0
    );

    TEST_ASSERT_EQUAL_INT(0, tracker.lastValue);
}

static void test_potentiometer_alternative_can_be_turned_to_maximum()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);
    potentiometer.setOnValueChange([](int val){ tracker.recordValueChange(val); });

    converge(
        [&]{ potentiometer.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        0
    );
    tracker.reset();

    _mock_analog_pins()[POT_PIN] = 1023;

    converge(
        [&]{ potentiometer.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        100
    );

    TEST_ASSERT_EQUAL_INT(100, tracker.lastValue);
}

void run_potentiometer_alternative_tests()
{
    RUN_TEST(test_potentiometer_alternative_can_be_turned_to_minimum);
    RUN_TEST(test_potentiometer_alternative_can_be_turned_to_maximum);
}
