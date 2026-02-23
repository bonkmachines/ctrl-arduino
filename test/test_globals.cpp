#include "test_globals.h"

TestTracker tracker;

void resetAllMocks()
{
    tracker.reset();
    _mock_millis_ref() = 0;
    _mock_micros_ref() = 0;
    _mock_reset_pins();
    _mock_digital_pins()[BTN_PIN] = HIGH;
    _mock_digital_pins()[ENC_CLK_PIN] = LOW;
    _mock_digital_pins()[ENC_DT_PIN] = LOW;
}
