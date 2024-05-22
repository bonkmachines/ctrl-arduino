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
        const uint8_t margin
    ) : CtrlPotBase(sig, maxOutputValue, margin) { }

private:
    void onValueChange(const int value) override
    {
        potentiometerHandlerResult = value;
    }
};

void test_potentiometer_advanced_can_be_turned_to_minimum()
{
    CustomPot potentiometer(potentiometerSig, 100, 10);

    potentiometerHandlerResult = -1; // Reset

    mockPotentiometerInput = 0; // Simulate a minimum position of the pot. Range:0 - 1023
    potentiometer.process(); // Process internal current state

    TEST_ASSERT_EQUAL_INT(0, potentiometer.getValue()); // Expected value, considering maxOutPutValue
}

void test_potentiometer_advanced_can_be_turned_to_maximum()
{
    CustomPot potentiometer(potentiometerSig, 100, 10);

    potentiometerHandlerResult = -1; // Reset

    mockPotentiometerInput = 1023; // Simulate a maximum position of the pot. Range:0 - 1023
    potentiometer.process(); // Process internal current state

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue()); // Expected value, considering maxOutPutValue
}