#include <Arduino.h>
#include <unity.h>
#include "CtrlRGBLed.h"
#include "test_globals.h"

#define PIN_R 8
#define PIN_G 9
#define PIN_B 10



static void test_led_can_be_turned_on_and_off()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    TEST_ASSERT_TRUE(led.isOff());

    led.turnOn();
    TEST_ASSERT_TRUE(led.isOn());

    led.turnOff();
    TEST_ASSERT_TRUE(led.isOff());

    led.set(true);
    TEST_ASSERT_TRUE(led.isOn());

    led.set(false);
    TEST_ASSERT_TRUE(led.isOff());
}

static void test_led_can_toggle()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    TEST_ASSERT_TRUE(led.isOff());

    led.toggle();
    TEST_ASSERT_TRUE(led.isOn());

    led.toggle();
    TEST_ASSERT_TRUE(led.isOff());
}

static void test_led_can_change_brightness()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.setBrightness(0);
    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());

    led.setBrightness(100);
    TEST_ASSERT_EQUAL_INT(100, led.getBrightness());

    led.setBrightness(0);
    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());
}

static void test_led_cant_change_brightness_beyond_maximum()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.setBrightness(101);
    TEST_ASSERT_EQUAL_INT(100, led.getBrightness());
}

static void test_led_cant_change_brightness_beyond_minimum()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.setBrightness(-1);
    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());
}

static void test_led_can_change_colour() {
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    uint8_t colour[] = {127, 109, 80};
    led.setRGB(colour);
    TEST_ASSERT_EQUAL_INT(127, led.getRGBRaw()[0]);
    TEST_ASSERT_EQUAL_INT(109, led.getRGBRaw()[1]);
    TEST_ASSERT_EQUAL_INT(80, led.getRGBRaw()[2]);
}

static void test_led_can_be_calibrated()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.setMaxBrightness(50);
    TEST_ASSERT_EQUAL_INT(50, led.getMaxBrightness());
}

static void test_led_cant_be_calibrated_beyond_maximum()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.setMaxBrightness(256);
    TEST_ASSERT_EQUAL_INT(255, led.getMaxBrightness());
}

static void test_led_cant_be_calibrated_beyond_minimum()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.setMaxBrightness(-1);
    TEST_ASSERT_EQUAL_INT(0, led.getMaxBrightness());
}

static void test_led_disabled_ignores_toggle()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    TEST_ASSERT_TRUE(led.isOff());
    led.disable();

    led.toggle();
    TEST_ASSERT_TRUE(led.isOff());

    led.turnOn();
    TEST_ASSERT_TRUE(led.isOff());

    led.set(true);
    TEST_ASSERT_TRUE(led.isOff());

    led.setBrightness(50);
    TEST_ASSERT_EQUAL_INT(100, led.getBrightness());
}

static void test_led_re_enable_allows_control()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.disable();
    led.toggle();
    TEST_ASSERT_TRUE(led.isOff());

    led.enable();
    led.toggle();
    TEST_ASSERT_TRUE(led.isOn());
}

static void test_led_disabled_ignores_turn_on()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.disable();
    led.turnOn();
    TEST_ASSERT_TRUE(led.isOff());
}

static void test_led_disabled_ignores_turn_off()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.enable();
    led.turnOn();
    TEST_ASSERT_TRUE(led.isOn());

    led.disable();
    led.turnOff();
    TEST_ASSERT_TRUE(led.isOn());
}

static void test_led_brightness_zero_max_returns_zero()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());
}

static void test_led_set_max_brightness_clamps_brightness()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

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
    RUN_TEST(test_led_can_change_colour);
    RUN_TEST(test_led_can_be_calibrated);
    RUN_TEST(test_led_cant_be_calibrated_beyond_maximum);
    RUN_TEST(test_led_cant_be_calibrated_beyond_minimum);
    RUN_TEST(test_led_disabled_ignores_toggle);
    RUN_TEST(test_led_re_enable_allows_control);
    RUN_TEST(test_led_disabled_ignores_turn_on);
    RUN_TEST(test_led_disabled_ignores_turn_off);
    RUN_TEST(test_led_brightness_zero_max_returns_zero);
    RUN_TEST(test_led_set_max_brightness_clamps_brightness);
}
