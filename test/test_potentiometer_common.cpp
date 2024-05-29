#include <Arduino.h>
#include <unity.h>
#include "CtrlPot.h"
#include "test_globals.h"

void test_potentiometer_common_can_be_disabled_and_enabled()
{
    CtrlPot potentiometer = CtrlPot::create(1, 100, 0.05);

    potentiometer.disable(); // Disable the potentiometer
    potentiometer.process(); // Process internal state

    TEST_ASSERT_TRUE(potentiometer.isDisabled()); // Potentiometer should be disabled

    potentiometer.enable(); // Enable the potentiometer
    potentiometer.process(); // Process internal state

    TEST_ASSERT_TRUE(potentiometer.isEnabled()); // Potentiometer should be enabled
}

void test_potentiometer_common_can_be_turned()
{
    CtrlPot potentiometer = CtrlPot::create(1, 100, 0.05);

    mockPotentiometerInput = 512; // Simulate a halfway position of the pot. Range:0 - 1023

    // Call process multiple times to allow smoothing to converge
    for (int i = 0; i < 10000; ++i) {
        potentiometer.process();
    }

    TEST_ASSERT_EQUAL_INT(50, potentiometer.getValue()); // Expected value on halfway turn, considering maxOutPutValue
}