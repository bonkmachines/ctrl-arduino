#include <Arduino.h>
#include <unity.h>
#include "CtrlPot.h"
#include "test_globals.h"

// Define an onChange handler
void onChangeHandlerAlternative(int value)
{
    potentiometerHandlerResult = value;
}

void test_potentiometer_alternative_can_be_turned_to_minimum()
{
    CtrlPot potentiometer = CtrlPot::create(
        1,
        100,
        0.05
    );

    // Register the handler
    potentiometer.setOnValueChange(onChangeHandlerAlternative);

    // Call process multiple times to allow updating
    for (int i = 0; i < 10000; ++i) {
        potentiometer.process();
    }

    potentiometerHandlerResult = -1; // Reset

    mockPotentiometerInput = 0; // Simulate a minimum position of the pot. Range: 0 - 1023

    // Call process multiple times to allow smoothing to converge
    for (int i = 0; i < 20000; ++i) {
        potentiometer.process();
    }

    TEST_ASSERT_EQUAL(0, potentiometerHandlerResult); // Expected value, considering maxOutPutValue
}

void test_potentiometer_alternative_can_be_turned_to_maximum()
{
    CtrlPot potentiometer = CtrlPot::create(
        1,
        100,
        0.05
    );

    // Register the handler
    potentiometer.setOnValueChange(onChangeHandlerAlternative);

    // Call process multiple times to allow updating
    for (int i = 0; i < 10000; ++i) {
        potentiometer.process();
    }

    potentiometerHandlerResult = -1; // Reset

    mockPotentiometerInput = 1023; // Simulate a maximum position of the pot. Range: 0 - 1023

    // Call process multiple times to allow smoothing to converge
    for (int i = 0; i < 20000; ++i) {
        potentiometer.process();
    }

    TEST_ASSERT_EQUAL(100, potentiometerHandlerResult); // Expected value, considering maxOutPutValue
}