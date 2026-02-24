#include <Arduino.h>
#include <unity.h>
#include "CtrlLed.h"
#include "test_globals.h"

static void test_led_can_be_turned_on_and_off()
{
    CtrlLed led(1, 15);

    TEST_ASSERT_TRUE(led.isOff());

    led.turnOn();
    TEST_ASSERT_TRUE(led.isOn());

    led.turnOff();
    TEST_ASSERT_TRUE(led.isOff());
}

static void test_led_can_toggle()
{
    CtrlLed led(1, 15);

    TEST_ASSERT_TRUE(led.isOff());

    led.toggle();
    TEST_ASSERT_TRUE(led.isOn());

    led.toggle();
    TEST_ASSERT_TRUE(led.isOff());
}

static void test_led_can_change_brightness()
{
    CtrlLed led(1, 15);

    led.setBrightness(0);
    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());

    led.setBrightness(100);
    TEST_ASSERT_EQUAL_INT(100, led.getBrightness());

    led.setBrightness(0);
    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());
}

static void test_led_cant_change_brightness_beyond_maximum()
{
    CtrlLed led(1, 15);

    led.setBrightness(101);
    TEST_ASSERT_EQUAL_INT(100, led.getBrightness());
}

static void test_led_cant_change_brightness_beyond_minimum()
{
    CtrlLed led(1, 15);

    led.setBrightness(-1);
    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());
}

static void test_led_can_be_calibrated()
{
    CtrlLed led(1, 255);

    led.setMaxBrightness(50);
    TEST_ASSERT_EQUAL_INT(50, led.getMaxBrightness());
}

static void test_led_cant_be_calibrated_beyond_maximum()
{
    CtrlLed led(1, 255);

    led.setMaxBrightness(256);
    TEST_ASSERT_EQUAL_INT(255, led.getMaxBrightness());
}

static void test_led_cant_be_calibrated_beyond_minimum()
{
    CtrlLed led(1);

    led.setMaxBrightness(-1);
    TEST_ASSERT_EQUAL_INT(0, led.getMaxBrightness());
}

static void test_led_digital_mode_on_off()
{
    CtrlLed led(1);

    TEST_ASSERT_FALSE(led.isPwmMode());
    TEST_ASSERT_TRUE(led.isOff());

    led.turnOn();
    TEST_ASSERT_TRUE(led.isOn());

    led.turnOff();
    TEST_ASSERT_TRUE(led.isOff());

    led.toggle();
    TEST_ASSERT_TRUE(led.isOn());

    led.toggle();
    TEST_ASSERT_TRUE(led.isOff());
}

static void test_led_digital_mode_ignores_brightness()
{
    CtrlLed led(1);

    TEST_ASSERT_FALSE(led.isPwmMode());

    led.setBrightness(50);
    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());

    led.setMaxBrightness(100);
    TEST_ASSERT_EQUAL_INT(0, led.getMaxBrightness());
}

static void test_led_disabled_ignores_toggle()
{
    CtrlLed led(1, 255);

    TEST_ASSERT_TRUE(led.isOff());
    led.disable();

    led.toggle();
    TEST_ASSERT_TRUE(led.isOff());

    led.turnOn();
    TEST_ASSERT_TRUE(led.isOff());

    led.setBrightness(50);
    TEST_ASSERT_EQUAL_INT(100, led.getBrightness());
}

static void test_led_re_enable_allows_control()
{
    CtrlLed led(1, 255);

    led.disable();
    led.toggle();
    TEST_ASSERT_TRUE(led.isOff());

    led.enable();
    led.toggle();
    TEST_ASSERT_TRUE(led.isOn());
}

static void test_led_disabled_ignores_turn_on()
{
    CtrlLed led(1, 255);

    led.disable();
    led.turnOn();
    TEST_ASSERT_TRUE(led.isOff());
}

static void test_led_disabled_ignores_turn_off()
{
    CtrlLed led(1, 255);

    led.enable();
    led.turnOn();
    TEST_ASSERT_TRUE(led.isOn());

    led.disable();
    led.turnOff();
    TEST_ASSERT_TRUE(led.isOn());
}

static void test_led_brightness_zero_max_returns_zero()
{
    CtrlLed led(1, 0);

    TEST_ASSERT_TRUE(led.isPwmMode());
    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());
}

static void test_led_set_max_brightness_clamps_brightness()
{
    CtrlLed led(1, 255);

    led.setBrightness(80);
    TEST_ASSERT_EQUAL_INT(80, led.getBrightness());

    led.setMaxBrightness(50);
    TEST_ASSERT_TRUE(led.getBrightness() <= 100);
    TEST_ASSERT_TRUE(led.getMaxBrightness() == 50);
}

void run_led_tests()
{
    RUN_TEST(test_led_can_be_turned_on_and_off);
    RUN_TEST(test_led_can_toggle);
    RUN_TEST(test_led_can_change_brightness);
    RUN_TEST(test_led_cant_change_brightness_beyond_maximum);
    RUN_TEST(test_led_cant_change_brightness_beyond_minimum);
    RUN_TEST(test_led_can_be_calibrated);
    RUN_TEST(test_led_cant_be_calibrated_beyond_maximum);
    RUN_TEST(test_led_cant_be_calibrated_beyond_minimum);
    RUN_TEST(test_led_digital_mode_on_off);
    RUN_TEST(test_led_digital_mode_ignores_brightness);
    RUN_TEST(test_led_disabled_ignores_toggle);
    RUN_TEST(test_led_re_enable_allows_control);
    RUN_TEST(test_led_disabled_ignores_turn_on);
    RUN_TEST(test_led_disabled_ignores_turn_off);
    RUN_TEST(test_led_brightness_zero_max_returns_zero);
    RUN_TEST(test_led_set_max_brightness_clamps_brightness);
}
