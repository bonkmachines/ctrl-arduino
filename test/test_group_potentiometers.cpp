#include <Arduino.h>
#include <unity.h>
#include "CtrlGroup.h"
#include "CtrlPot.h"
#include "test_globals.h"

void onValueChange(Groupable& potentiometer, int value) {
    const int integer = potentiometer.getInteger("integer");
    const String string = potentiometer.getString("string");
    const bool boolean = potentiometer.getBoolean("boolean");
    if (boolean) {
        potentiometerHandlerResult = value;
        groupedPotentiometerHandlerResult = "Rotated: " + std::to_string(integer) + " " + string.c_str();
    }
}

void test_potentiometer_can_be_grouped()
{
    CtrlGroup potentiometerGroup;

    CtrlPot potentiometer(1, 100, 0.05);

    potentiometerGroup.setOnValueChange(onValueChange);

    potentiometer.setGroup(&potentiometerGroup);

    potentiometer.setInteger("integer", 10);
    potentiometer.setString("string", "Four");
    potentiometer.setBoolean("boolean", true);

    potentiometerHandlerResult = -1; // Reset
    groupedPotentiometerHandlerResult = ""; // Reset
    mockPotentiometerInput = 1023;

    // Call process multiple times to allow smoothing to converge
    for (int i = 0; i < 20000; ++i) {
        potentiometerGroup.process();
    }

    TEST_ASSERT_EQUAL_INT(100, potentiometerHandlerResult); // Expected value, considering maxOutPutValue
    TEST_ASSERT_EQUAL_STRING("Rotated: 10 Four", groupedPotentiometerHandlerResult.c_str()); // Verify the potentiometer's on press handler has been called
}