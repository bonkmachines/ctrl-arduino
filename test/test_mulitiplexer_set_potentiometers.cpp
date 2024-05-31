#include <Arduino.h>
#include <CtrlMux.h>
#include <CtrlPot.h>
#include <unity.h>
#include "test_globals.h"

void test_potentiometers_can_be_multiplexed_via_mux_set()
{
    CtrlMuxSet muxSet(2);

    CtrlMux mux1(1, 10, 1, 2, 3, 4, 5, &muxSet);
    CtrlMux mux2(1, 10, 2, 2, 3, 4, 5, &muxSet);

    CtrlPot potentiometer1 = CtrlPot::create(
        0,
        100,
        0.05
    );

    CtrlPot potentiometer2 = CtrlPot::create(
        0,
        100,
        0.05
    );

    potentiometer1.setMultiplexer(mux1);
    potentiometer2.setMultiplexer(mux2);

    potentiometer1.process();
    potentiometer2.process();

    TEST_ASSERT_TRUE(mux1.subscriptionComplete());
    TEST_ASSERT_TRUE(mux2.subscriptionComplete());

    // Test pot 1 on mux 1

    mockMuxPotSigInput = 1023; // Simulate a maximum position of the pot. Range: 0 - 1023

    // Call process multiple times to allow smoothing to converge
    for (int i = 0; i < 20000; ++i) {
        potentiometer1.process();
    }

    TEST_ASSERT_EQUAL_INT(100, potentiometer1.getValue()); // Expected value, considering maxOutPutValue

    // Test pot 2 on mux 3

    mockMuxPotSigInput = 1023; // Simulate a maximum position of the pot. Range: 0 - 1023

    // Call process multiple times to allow smoothing to converge
    for (int i = 0; i < 20000; ++i) {
        potentiometer2.process();
    }

    TEST_ASSERT_EQUAL_INT(100, potentiometer2.getValue()); // Expected value, considering maxOutPutValue
}