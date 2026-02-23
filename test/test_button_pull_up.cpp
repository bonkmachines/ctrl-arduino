#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

static void test_button_internal_pull_up_can_be_pressed_and_released()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); }, []{ tracker.recordRelease(); });
    button.setPinMode(INPUT_PULLUP);

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

static void test_button_external_pull_up_can_be_pressed_and_released()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); }, []{ tracker.recordRelease(); });
    button.setPinMode(INPUT, PULL_UP);

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

void run_button_pull_up_tests()
{
    RUN_TEST(test_button_internal_pull_up_can_be_pressed_and_released);
    RUN_TEST(test_button_external_pull_up_can_be_pressed_and_released);
}
