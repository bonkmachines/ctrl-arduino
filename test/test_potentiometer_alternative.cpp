#include <Arduino.h>
#include <unity.h>
#include "CtrlPot.h"
#include "test_globals.h"

// Define an onChange handler
void onChangeHandlerAlternative(const int value)
{
    potentiometerHandlerResult = value;
}

void test_potentiometer_alternative_can_be_turned_to_minimum()
{
    CtrlPot potentiometer = CtrlPot::create(
        potentiometerSig,
        100,
        10
    );

    // Register the handler
    potentiometer.setOnValueChange(onChangeHandlerAlternative);

    potentiometerHandlerResult = -1; // Reset

    mockPotentiometerInput = 0; // Simulate a minimum position of the pot. Range:0 - 1023
    potentiometer.process(); // Process internal current state

    TEST_ASSERT_EQUAL_INT(0, potentiometer.getValue()); // Expected value on halfway turn, considering maxOutPutValue
}

void test_potentiometer_alternative_can_be_turned_to_maximum()
{
    CtrlPot potentiometer = CtrlPot::create(
        potentiometerSig,
        100,
        10
    );

    // Register the handler
    potentiometer.setOnValueChange(onChangeHandlerAlternative);

    potentiometerHandlerResult = -1; // Reset

    mockPotentiometerInput = 1023; // Simulate a maximum position of the pot. Range:0 - 1023
    potentiometer.process(); // Process internal current state

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue()); // Expected value on halfway turn, considering maxOutPutValue
}