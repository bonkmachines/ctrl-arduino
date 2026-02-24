#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

static void test_button_delayed_release_fires_after_hold()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE,
        []{ tracker.recordPress(); },
        []{ tracker.recordRelease(); },
        []{ tracker.recordDelayedRelease(); }
    );
    button.setDelayedReleaseDuration(100);

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL(TestEvent::ButtonPressed, tracker.lastEvent);

    delay(100 + 1);

    _mock_digital_pins()[BTN_PIN] = HIGH;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL(TestEvent::ButtonDelayedRelease, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.delayedReleaseCount);
    TEST_ASSERT_EQUAL_INT(0, tracker.releaseCount);
}

static void test_button_normal_release_fires_before_hold_duration()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE,
        []{ tracker.recordPress(); },
        []{ tracker.recordRelease(); },
        []{ tracker.recordDelayedRelease(); }
    );
    button.setDelayedReleaseDuration(500);

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    _mock_digital_pins()[BTN_PIN] = HIGH;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL(TestEvent::ButtonReleased, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.releaseCount);
    TEST_ASSERT_EQUAL_INT(0, tracker.delayedReleaseCount);
}

static void test_button_delayed_release_exact_boundary()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE,
        []{ tracker.recordPress(); },
        []{ tracker.recordRelease(); },
        []{ tracker.recordDelayedRelease(); }
    );
    button.setDelayedReleaseDuration(100);

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    delay(50);

    _mock_digital_pins()[BTN_PIN] = HIGH;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL(TestEvent::ButtonReleased, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(0, tracker.delayedReleaseCount);
}

static void test_button_delayed_release_duration_zero()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE,
        []{ tracker.recordPress(); },
        []{ tracker.recordRelease(); },
        []{ tracker.recordDelayedRelease(); }
    );
    button.setDelayedReleaseDuration(0);

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

    TEST_ASSERT_EQUAL(TestEvent::ButtonDelayedRelease, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.delayedReleaseCount);
    TEST_ASSERT_EQUAL_INT(0, tracker.releaseCount);
}

void run_button_delayed_release_tests()
{
    RUN_TEST(test_button_delayed_release_fires_after_hold);
    RUN_TEST(test_button_normal_release_fires_before_hold_duration);
    RUN_TEST(test_button_delayed_release_exact_boundary);
    RUN_TEST(test_button_delayed_release_duration_zero);
}
