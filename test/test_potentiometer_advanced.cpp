#include <Arduino.h>
#include <unity.h>
#include "CtrlPot.h"
#include "test_globals.h"

class TestPot final : public CtrlPot
{
    public:
        TestPot(uint8_t sig, uint16_t maxOutputValue, float sensitivity)
            : CtrlPot(sig, maxOutputValue, sensitivity) {}

    private:
        void onValueChange(int value) override { tracker.recordValueChange(value); }
};

static void test_potentiometer_advanced_can_be_turned_to_minimum()
{
    TestPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);

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

static void test_potentiometer_advanced_can_be_turned_to_maximum()
{
    TestPot potentiometer(POT_PIN, 100, TEST_SENSITIVITY);

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

void run_potentiometer_advanced_tests()
{
    RUN_TEST(test_potentiometer_advanced_can_be_turned_to_minimum);
    RUN_TEST(test_potentiometer_advanced_can_be_turned_to_maximum);
}
