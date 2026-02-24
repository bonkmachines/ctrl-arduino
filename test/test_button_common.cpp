#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "test_globals.h"

static void test_button_common_initial_state()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE);

    button.process();

    TEST_ASSERT_FALSE(button.isPressed());
    TEST_ASSERT_TRUE(button.isReleased());
}

static void test_button_common_can_be_disabled_and_enabled()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE);

    button.disable();
    button.process();
    TEST_ASSERT_TRUE(button.isDisabled());

    button.enable();
    button.process();
    TEST_ASSERT_TRUE(button.isEnabled());
}

static void test_button_common_can_be_pressed_and_released()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE);

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_TRUE(button.isPressed());

    _mock_digital_pins()[BTN_PIN] = HIGH;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_TRUE(button.isReleased());
}

static void test_button_disabled_ignores_input()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE);

    button.process();
    button.disable();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_TRUE(button.isReleased());
}

static void test_button_double_press_without_release()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); }, []{ tracker.recordRelease(); });

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
    TEST_ASSERT_TRUE(button.isPressed());

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
    TEST_ASSERT_EQUAL_INT(0, tracker.releaseCount);
}

static void test_button_bounce_within_debounce_window()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); });

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(5);
    _mock_digital_pins()[BTN_PIN] = HIGH;
    button.process();
    delay(5);
    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

static void test_button_re_enable_preserves_state()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE);

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();
    TEST_ASSERT_TRUE(button.isPressed());

    button.disable();
    button.enable();

    TEST_ASSERT_TRUE(button.isPressed());
}

static void test_button_zero_debounce()
{
    CtrlBtn button(BTN_PIN, 0, []{ tracker.recordPress(); }, []{ tracker.recordRelease(); });

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(1);
    button.process();

    TEST_ASSERT_EQUAL(TestEvent::ButtonPressed, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

static void test_button_rapid_press_release_cycles()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); }, []{ tracker.recordRelease(); });

    button.process();

    for (int cycle = 0; cycle < 100; ++cycle) {
        _mock_digital_pins()[BTN_PIN] = LOW;
        button.process();
        delay(TEST_DEBOUNCE + 1);
        button.process();

        _mock_digital_pins()[BTN_PIN] = HIGH;
        button.process();
        delay(TEST_DEBOUNCE + 1);
        button.process();
    }

    TEST_ASSERT_EQUAL_INT(100, tracker.pressCount);
    TEST_ASSERT_EQUAL_INT(100, tracker.releaseCount);
    TEST_ASSERT_EQUAL_INT(200, tracker.eventCount);
}

static void test_button_set_pin_mode_invalid_type_ignored()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); }, []{ tracker.recordRelease(); });

    button.setPinMode(99);

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

static void test_button_set_pin_mode_invalid_resistor_ignored()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); }, []{ tracker.recordRelease(); });

    button.setPinMode(INPUT, 99);

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

void run_button_common_tests()
{
    RUN_TEST(test_button_common_initial_state);
    RUN_TEST(test_button_common_can_be_disabled_and_enabled);
    RUN_TEST(test_button_common_can_be_pressed_and_released);
    RUN_TEST(test_button_disabled_ignores_input);
    RUN_TEST(test_button_double_press_without_release);
    RUN_TEST(test_button_bounce_within_debounce_window);
    RUN_TEST(test_button_re_enable_preserves_state);
    RUN_TEST(test_button_zero_debounce);
    RUN_TEST(test_button_rapid_press_release_cycles);
    RUN_TEST(test_button_set_pin_mode_invalid_type_ignored);
    RUN_TEST(test_button_set_pin_mode_invalid_resistor_ignored);
}
