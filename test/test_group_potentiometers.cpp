#include <Arduino.h>
#include <unity.h>
#include "CtrlGroup.h"
#include "CtrlPot.h"
#include "test_globals.h"

static void test_potentiometer_can_be_grouped()
{
    CtrlGroup potGroup;
    CtrlPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);

    potGroup.setOnValueChange([](Groupable& pot, int value) {
        TEST_ASSERT_TRUE(pot.getBoolean("active"));
        TEST_ASSERT_EQUAL_INT(10, pot.getInteger("id"));
        tracker.recordValueChange(value);
    });

    potentiometer.setGroup(&potGroup);
    potentiometer.setInteger("id", 10);
    potentiometer.setString("name", "testPot");
    potentiometer.setBoolean("active", true);

    _mock_analog_pins()[POT_PIN] = 1023;

    converge(
        [&]{ potGroup.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        100
    );

    TEST_ASSERT_EQUAL_INT(100, tracker.lastValue);
    TEST_ASSERT_TRUE(tracker.valueChangeCount > 0);
}

void run_group_potentiometer_tests()
{
    RUN_TEST(test_potentiometer_can_be_grouped);
}
