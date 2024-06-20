#include <Arduino.h>
#include <CtrlMux.h>
#include <CtrlPot.h>
#include <unity.h>
#include "test_globals.h"

void test_potentiometers_can_be_multiplexed()
{
    CtrlMux mux(1, 2, 3, 4, 5);

    CtrlPot potentiometer(
        0,
        100,
        0.05
    );

    potentiometer.setMultiplexer(mux);

    mockMuxPotSigInput = 1023; // Simulate a maximum position of the pot. Range: 0 - 1023

    // Call process multiple times to allow smoothing to converge
    for (int i = 0; i < 20000; ++i) {
        potentiometer.process();
    }

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue()); // Expected value, considering maxOutPutValue
}