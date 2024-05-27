#include <Arduino.h>
#include <unity.h>
#include "CtrlLed.h"
#include "test_globals.h"


void test_led_can_be_turned_on_and_off()
{
    CtrlLed led(1, 15);

    TEST_ASSERT_TRUE(led.isOff());

    led.turnOn();

    TEST_ASSERT_TRUE(led.isOn());

    led.turnOff();

    TEST_ASSERT_TRUE(led.isOff());
}

void test_led_can_toggle()
{
    CtrlLed led(1, 15);

    TEST_ASSERT_TRUE(led.isOff());

    led.toggle();

    TEST_ASSERT_TRUE(led.isOn());

    led.toggle();

    TEST_ASSERT_TRUE(led.isOff());
}

void test_led_can_change_brightness()
{
    CtrlLed led(1, 15);

    led.setBrightness(0);

    TEST_ASSERT_EQUAL_INT(0, led.getBrightness());

    led.setBrightness(100);

    TEST_ASSERT_EQUAL_INT(100, led.getBrightness());
}

void test_led_can_be_calibrated()
{
    CtrlLed led(1);

    led.setMaxBrightness(50);

    TEST_ASSERT_EQUAL_INT(50, led.getMaxBrightness());
}