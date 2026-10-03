#include <Arduino.h>
#include <unity.h>
#include "CtrlRGBLed.h"
#include "test_globals.h"

static constexpr uint8_t PIN_R = 3;
static constexpr uint8_t PIN_G = 5;
static constexpr uint8_t PIN_B = 6;

static void assert_pins(const int r, const int g, const int b)
{
    TEST_ASSERT_EQUAL_INT(r, analogRead(PIN_R));
    TEST_ASSERT_EQUAL_INT(g, analogRead(PIN_G));
    TEST_ASSERT_EQUAL_INT(b, analogRead(PIN_B));
}

static void assert_color(const CtrlRGB expected, const CtrlRGB actual)
{
    TEST_ASSERT_EQUAL_INT(expected.r, actual.r);
    TEST_ASSERT_EQUAL_INT(expected.g, actual.g);
    TEST_ASSERT_EQUAL_INT(expected.b, actual.b);
}

static void test_ledrgb_starts_off_and_white()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    TEST_ASSERT_TRUE(led.isOff());
    TEST_ASSERT_FALSE(led.isCommonAnode());
    assert_color(CtrlColor::White, led.getColor());
    assert_color(CtrlColor::Off, led.getOutputColor());
    TEST_ASSERT_EQUAL_INT(100, led.getBrightness());
    TEST_ASSERT_EQUAL_INT(255, led.getMaxBrightness());
}

static void test_ledrgb_can_be_turned_on_and_off()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.turnOn();
    TEST_ASSERT_TRUE(led.isOn());
    assert_pins(255, 255, 255);

    led.turnOff();
    TEST_ASSERT_TRUE(led.isOff());
    assert_pins(0, 0, 0);
}

static void test_ledrgb_can_toggle()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.toggle();
    TEST_ASSERT_TRUE(led.isOn());
    assert_pins(255, 255, 255);

    led.toggle();
    TEST_ASSERT_TRUE(led.isOff());
    assert_pins(0, 0, 0);
}

static void test_ledrgb_can_be_set()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.set(true);
    TEST_ASSERT_TRUE(led.isOn());
    assert_pins(255, 255, 255);

    led.set(false);
    TEST_ASSERT_TRUE(led.isOff());
    assert_pins(0, 0, 0);
}

static void test_ledrgb_set_color_while_on_updates_output()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.turnOn();
    led.setColor(173, 51, 98);
    assert_color({173, 51, 98}, led.getColor());
    assert_color({173, 51, 98}, led.getOutputColor());
    assert_pins(173, 51, 98);

    led.setColor(CtrlColor::Red);
    assert_pins(255, 0, 0);
}

static void test_ledrgb_set_color_while_off_does_not_turn_on()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.turnOff();
    led.setColor(CtrlColor::Blue);
    TEST_ASSERT_TRUE(led.isOff());
    assert_color(CtrlColor::Blue, led.getColor());
    assert_pins(0, 0, 0);

    // The colour is applied once the LED is turned on.
    led.turnOn();
    assert_pins(0, 0, 255);
}

static void test_ledrgb_color_persists_through_off_and_on()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.turnOn();
    led.setColor(CtrlColor::Magenta);
    led.turnOff();
    assert_pins(0, 0, 0);
    led.toggle();
    assert_pins(255, 0, 255);
    assert_color(CtrlColor::Magenta, led.getColor());
}

static void test_ledrgb_brightness_scales_output()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.turnOn();
    led.setColor(173, 51, 98);
    led.setBrightness(50);

    TEST_ASSERT_EQUAL_INT(50, led.getBrightness());
    assert_color({173, 51, 98}, led.getColor());
    assert_color({86, 25, 48}, led.getOutputColor());
    assert_pins(86, 25, 48);
}

static void test_ledrgb_brightness_is_clamped()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.setBrightness(150);
    TEST_ASSERT_EQUAL_INT(100, led.getBrightness());

    led.setBrightness(-10);
    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());
}

static void test_ledrgb_brightness_round_trips()
{
    const uint8_t maxBrightnesses[] = {255, 200};
    for (const uint8_t maxBrightness : maxBrightnesses) {
        CtrlRGBLed led(PIN_R, PIN_G, PIN_B, maxBrightness);
        for (int percentage = 0; percentage <= 100; ++percentage) {
            led.setBrightness(percentage);
            TEST_ASSERT_EQUAL_INT(percentage, led.getBrightness());
        }
    }
}

static void test_ledrgb_max_brightness_calibrates_output()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 100);

    led.turnOn();
    assert_pins(100, 100, 100);

    led.setMaxBrightness(300);
    TEST_ASSERT_EQUAL_INT(255, led.getMaxBrightness());

    led.setMaxBrightness(50);
    TEST_ASSERT_EQUAL_INT(50, led.getMaxBrightness());
    TEST_ASSERT_EQUAL_INT(100, led.getBrightness());
    assert_pins(50, 50, 50);

    led.setMaxBrightness(-1);
    TEST_ASSERT_EQUAL_INT(0, led.getMaxBrightness());
    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());
    assert_pins(0, 0, 0);
}

static void test_ledrgb_common_anode_inverts_output()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255, COMMON_ANODE);

    TEST_ASSERT_TRUE(led.isCommonAnode());

    led.turnOff();
    assert_pins(255, 255, 255);

    led.setColor(CtrlColor::Red);
    led.turnOn();
    assert_pins(0, 255, 255);
    assert_color(CtrlColor::Red, led.getOutputColor());

    led.setBrightness(50);
    assert_pins(128, 255, 255);
}

static void test_ledrgb_disabled_ignores_input()
{
    CtrlRGBLed led(PIN_R, PIN_G, PIN_B, 255);

    led.disable();
    led.turnOn();
    led.toggle();
    led.set(true);
    led.setColor(CtrlColor::Green);
    led.setBrightness(10);

    TEST_ASSERT_TRUE(led.isOff());
    assert_color(CtrlColor::White, led.getColor());
    TEST_ASSERT_EQUAL_INT(100, led.getBrightness());
    assert_pins(0, 0, 0);

    led.enable();
    led.turnOn();
    TEST_ASSERT_TRUE(led.isOn());
    assert_pins(255, 255, 255);
}

void run_ledrgb_tests()
{
    RUN_TEST(test_ledrgb_starts_off_and_white);
    RUN_TEST(test_ledrgb_can_be_turned_on_and_off);
    RUN_TEST(test_ledrgb_can_toggle);
    RUN_TEST(test_ledrgb_can_be_set);
    RUN_TEST(test_ledrgb_set_color_while_on_updates_output);
    RUN_TEST(test_ledrgb_set_color_while_off_does_not_turn_on);
    RUN_TEST(test_ledrgb_color_persists_through_off_and_on);
    RUN_TEST(test_ledrgb_brightness_scales_output);
    RUN_TEST(test_ledrgb_brightness_is_clamped);
    RUN_TEST(test_ledrgb_brightness_round_trips);
    RUN_TEST(test_ledrgb_max_brightness_calibrates_output);
    RUN_TEST(test_ledrgb_common_anode_inverts_output);
    RUN_TEST(test_ledrgb_disabled_ignores_input);
}
