#include <Arduino.h>
#include <unity.h>
#include "CtrlGroup.h"
#include "CtrlBtn.h"
#include "test_globals.h"

static void test_button_can_be_grouped()
{
    CtrlGroup buttonGroup;
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE);

    buttonGroup.setOnPress([](Groupable& btn) {
        TEST_ASSERT_TRUE(btn.getBoolean("active"));
        TEST_ASSERT_EQUAL_INT(10, btn.getInteger("id"));
        tracker.recordPress();
    });

    buttonGroup.setOnRelease([](Groupable& btn) {
        TEST_ASSERT_TRUE(btn.getBoolean("active"));
        TEST_ASSERT_EQUAL_INT(10, btn.getInteger("id"));
        tracker.recordRelease();
    });

    button.setGroup(&buttonGroup);
    button.setInteger("id", 10);
    button.setString("name", "testBtn");
    button.setBoolean("active", true);

    buttonGroup.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    buttonGroup.process();
    delay(TEST_DEBOUNCE + 1);
    buttonGroup.process();

    TEST_ASSERT_EQUAL(TestEvent::ButtonPressed, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);

    _mock_digital_pins()[BTN_PIN] = HIGH;
    buttonGroup.process();
    delay(TEST_DEBOUNCE + 1);
    buttonGroup.process();

    TEST_ASSERT_EQUAL(TestEvent::ButtonReleased, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.releaseCount);
}

static void test_group_disabled_ignores_process()
{
    CtrlGroup buttonGroup;
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); }, []{ tracker.recordRelease(); });

    button.setGroup(&buttonGroup);

    buttonGroup.process();

    buttonGroup.disable();
    TEST_ASSERT_TRUE(buttonGroup.isDisabled());

    _mock_digital_pins()[BTN_PIN] = LOW;
    buttonGroup.process();
    delay(TEST_DEBOUNCE + 1);
    buttonGroup.process();

    TEST_ASSERT_EQUAL_INT(0, tracker.pressCount);

    buttonGroup.enable();
    TEST_ASSERT_TRUE(buttonGroup.isEnabled());

    buttonGroup.process();
    delay(TEST_DEBOUNCE + 1);
    buttonGroup.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

void run_group_button_tests()
{
    RUN_TEST(test_button_can_be_grouped);
    RUN_TEST(test_group_disabled_ignores_process);
}
