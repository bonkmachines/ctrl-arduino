#include <Arduino.h>
#include <CtrlBtn.h>
#include <CtrlMux.h>
#include <unity.h>
#include "test_globals.h"

void test_buttons_can_be_multiplexed_via_mux_set()
{
    CtrlMuxSet muxSet(2);

    CtrlMux mux1(1, 10, 1, 2, 3, 4, 5, &muxSet);
    CtrlMux mux2(1, 10, 2, 2, 3, 4, 5, &muxSet);

    CtrlBtn button1 = CtrlBtn::create(0, 15);
    CtrlBtn button2 = CtrlBtn::create(0, 15);

    button1.setMultiplexer(mux1);
    button2.setMultiplexer(mux2);

    button1.process();
    button2.process();

    TEST_ASSERT_TRUE(mux1.subscriptionComplete());
    TEST_ASSERT_TRUE(mux2.subscriptionComplete());

    // Test button 1 on mux 1

    mockMuxBtnSigInput = LOW; // Simulate button press

    // Call process multiple times
    for (int i = 0; i < 10000; ++i) {
        button1.process();
    }

    TEST_ASSERT_TRUE(button1.isPressed());

    mockMuxBtnSigInput = HIGH; // Simulate button release

    // Call process multiple times
    for (int i = 0; i < 10000; ++i) {
        button1.process();
    }

    TEST_ASSERT_TRUE(button1.isReleased());

    // Test button 2 on mux 2

    mockMuxBtnSigInput = LOW; // Simulate button press

    // Call process multiple times
    for (int i = 0; i < 10000; ++i) {
        button2.process();
    }

    TEST_ASSERT_TRUE(button2.isPressed());

    mockMuxBtnSigInput = HIGH; // Simulate button release

    // Call process multiple times
    for (int i = 0; i < 10000; ++i) {
        button2.process();
    }

    TEST_ASSERT_TRUE(button2.isReleased());
}