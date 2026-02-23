#include <Arduino.h>
#include <CtrlBtn.h>
#include <CtrlMux.h>
#include <unity.h>
#include "test_globals.h"

static void test_buttons_can_be_multiplexed()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);
    CtrlBtn button = CtrlBtn(0, TEST_DEBOUNCE);

    button.setMultiplexer(&mux);

    _mock_digital_pins()[MUX_SIG_PIN] = HIGH;
    mux.process();

    _mock_digital_pins()[MUX_SIG_PIN] = LOW;

    mux.process();
    delay(TEST_DEBOUNCE + 1);
    mux.process();

    TEST_ASSERT_TRUE(button.isPressed());

    _mock_digital_pins()[MUX_SIG_PIN] = HIGH;

    mux.process();
    delay(TEST_DEBOUNCE + 1);
    mux.process();

    TEST_ASSERT_TRUE(button.isReleased());
}

void run_multiplexer_button_tests()
{
    RUN_TEST(test_buttons_can_be_multiplexed);
}
