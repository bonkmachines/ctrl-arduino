#include <Arduino.h>
#include <CtrlBtn.h>
#include <CtrlMux.h>
#include <unity.h>
#include "test_globals.h"

void test_buttons_can_be_multiplexed()
{
    CtrlMux mux(1, 2, 3, 4, 5);

    CtrlBtn button = CtrlBtn(0, 15);

    button.setMultiplexer(mux);

    button.process();

    mockMuxBtnSigInput = LOW; // Simulate button press

    // Call process multiple times
    for (int i = 0; i < 20000; ++i) {
        button.process();
    }

    TEST_ASSERT_TRUE(button.isPressed());

    mockMuxBtnSigInput = HIGH; // Simulate button release

    // Call process multiple times
    for (int i = 0; i < 20000; ++i) {
        button.process();
    }

    TEST_ASSERT_TRUE(button.isReleased());
}