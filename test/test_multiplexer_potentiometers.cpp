#include <Arduino.h>
#include <CtrlMux.h>
#include <CtrlPot.h>
#include <unity.h>
#include "test_globals.h"

static void test_potentiometers_can_be_multiplexed()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);

    CtrlPot potentiometer(0, 100, TEST_SENSITIVITY);

    potentiometer.setMultiplexer(&mux);

    _mock_analog_pins()[MUX_SIG_PIN] = 1023;

    converge(
        [&]{ mux.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        100
    );

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue());
}

void run_multiplexer_potentiometer_tests()
{
    RUN_TEST(test_potentiometers_can_be_multiplexed);
}
