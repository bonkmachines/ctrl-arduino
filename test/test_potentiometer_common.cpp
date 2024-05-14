#include <Arduino.h>
#include <unity.h>
#include "CtrlPot.h"
#include "test_globals.h"

void test_potentiometer_common_can_be_disabled_and_enabled()
{
    CtrlPot potentiometer = CtrlPot::create(potentiometerSig, 100, 10);

    potentiometer.disable(); // Disable the potentiometer
    potentiometer.process(); // Process internal state

    TEST_ASSERT_TRUE(potentiometer.isDisabled()); // Potentiometer should be disabled

    potentiometer.enable(); // Enable the potentiometer
    potentiometer.process(); // Process internal state

    TEST_ASSERT_TRUE(potentiometer.isEnabled()); // Potentiometer should be enabled
}

void test_potentiometer_common_can_be_turned()
{
    CtrlPot potentiometer = CtrlPot::create(potentiometerSig, 100, 10);

    mockPotentiometerInput = 512; // Simulate a halfway position of the pot. Range:0 - 1023
    potentiometer.process(); // Process internal current state

    TEST_ASSERT_EQUAL_INT(50, potentiometer.getValue()); // Expected value on halfway turn, considering maxOutPutValue
}