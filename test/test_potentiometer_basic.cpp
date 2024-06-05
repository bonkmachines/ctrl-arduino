#include <Arduino.h>
#include <unity.h>
#include "CtrlPot.h"
#include "test_globals.h"

void test_potentiometer_basic_can_be_turned_to_minimum()
{
    CtrlPot potentiometer(
        1,
        100,
        0.05
    );

    potentiometerHandlerResult = -1; // Reset

    mockPotentiometerInput = 0; // Simulate a minimum position of the pot. Range: 0 - 1023

    // Call process multiple times to allow smoothing to converge
    for (int i = 0; i < 10000; ++i) {
        potentiometer.process();
    }

    TEST_ASSERT_EQUAL_INT(0, potentiometer.getValue()); // Expected value, considering maxOutPutValue
}

void test_potentiometer_basic_can_be_turned_to_maximum()
{
    CtrlPot potentiometer(
        1,
        100,
        0.05
    );

    mockPotentiometerInput = 1023; // Simulate a maximum position of the pot. Range: 0 - 1023

    // Call process multiple times to allow smoothing to converge
    for (int i = 0; i < 20000; ++i) {
        potentiometer.process();
    }

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue()); // Expected value, considering maxOutPutValue
}