#include <Arduino.h>
#include <unity.h>
#include "CtrlPot.h"
#include "test_globals.h"

class CustomPot final : public CtrlPotBase
{
public:
    CustomPot(
        const uint8_t sig,
        const uint16_t maxOutputValue,
        const float sensitivity
    ) : CtrlPotBase(sig, maxOutputValue, sensitivity) { }

private:
    void onValueChange(const int value) override
    {
        potentiometerHandlerResult = value;
    }
};

void test_potentiometer_advanced_can_be_turned_to_minimum()
{
    CustomPot potentiometer(potentiometerSig, 100, 0.05);

    potentiometerHandlerResult = -1; // Reset

    mockPotentiometerInput = 0; // Simulate a minimum position of the pot. Range:0 - 1023

    // Call process multiple times to allow smoothing to converge
    for (int i = 0; i < 10000; ++i) {
        potentiometer.process();
    }

    TEST_ASSERT_EQUAL_INT(0, potentiometer.getValue()); // Expected value, considering maxOutPutValue
}

void test_potentiometer_advanced_can_be_turned_to_maximum()
{
    CustomPot potentiometer(potentiometerSig, 100, 0.05);

    potentiometerHandlerResult = -1; // Reset

    mockPotentiometerInput = 1023; // Simulate a maximum position of the pot. Range:0 - 1023

    // Call process multiple times to allow smoothing to converge
    for (int i = 0; i < 12000; ++i) {
        potentiometer.process();
    }

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue()); // Expected value, considering maxOutPutValue
}