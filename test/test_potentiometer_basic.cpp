#include <Arduino.h>
#include <unity.h>
#include "CtrlPot.h"
#include "test_globals.h"

static void test_potentiometer_basic_can_be_turned_to_minimum()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);

    converge(
        [&]{ potentiometer.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        0
    );

    TEST_ASSERT_EQUAL_INT(0, potentiometer.getValue());
}

static void test_potentiometer_basic_can_be_turned_to_maximum()
{
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);

    _mock_analog_pins()[POT_PIN] = 1023;

    converge(
        [&]{ potentiometer.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        100
    );

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue());
}

void run_potentiometer_basic_tests()
{
    RUN_TEST(test_potentiometer_basic_can_be_turned_to_minimum);
    RUN_TEST(test_potentiometer_basic_can_be_turned_to_maximum);
}
