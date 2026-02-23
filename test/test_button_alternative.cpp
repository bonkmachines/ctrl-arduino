#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

static void test_button_alternative_can_be_pressed_and_released()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE);

    button.setOnPress([]{ tracker.recordPress(); });
    button.setOnRelease([]{ tracker.recordRelease(); });

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL(TestEvent::ButtonPressed, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);

    _mock_digital_pins()[BTN_PIN] = HIGH;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL(TestEvent::ButtonReleased, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.releaseCount);
}

void run_button_alternative_tests()
{
    RUN_TEST(test_button_alternative_can_be_pressed_and_released);
}
