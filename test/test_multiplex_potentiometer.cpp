#include <Arduino.h>
#include <unity.h>
#include "CtrlPot.h"
#include "test_globals.h"

// Define an onChange handler
void onChangeHandlerMuxPotentiometer(const int value)
{
    potentiometerHandlerResult = value;
}

void test_potentiometer_can_be_multiplexed()
{
    CtrlMux mux(muxSig, muxS0, muxS1, muxS2, muxS3);

    CtrlPot potentiometer = CtrlPot::create(
        potentiometerSig,
        100,
        10,
        onChangeHandlerMuxPotentiometer,
        &mux
    );

    potentiometerHandlerResult = -1; // Reset

    mockMuxAnalogInput = 1023; // Simulate a maximum position of the pot. Range: 0 - 1023
    potentiometer.process(); // Process internal current state

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue()); // Expected value on maximum turn, considering maxOutPutValue
}