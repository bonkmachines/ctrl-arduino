#include <Arduino.h>
#include <unity.h>

// Button test methods
extern void test_button_common_initial_state();
extern void test_button_common_can_be_disabled_and_enabled();
extern void test_button_common_can_be_pressed_and_released();
extern void test_button_basic_can_be_pressed_and_released();
extern void test_button_alternative_can_be_pressed_and_released();
extern void test_button_advanced_can_be_pressed_and_released();

// Encoder test methods
extern void test_encoder_common_initial_state();
extern void test_encoder_common_can_be_disabled_and_enabled();
extern void test_encoder_basic_can_be_turned_left();
extern void test_encoder_basic_can_be_turned_right();
extern void test_encoder_alternative_can_be_turned_left();
extern void test_encoder_alternative_can_be_turned_right();
extern void test_encoder_advanced_can_be_turned_left();
extern void test_encoder_advanced_can_be_turned_right();
extern void test_encoder_pull_down_can_be_turned_left();
extern void test_encoder_pull_down_can_be_turned_right();

// Potentiometer test methods
extern void test_potentiometer_common_can_be_disabled_and_enabled();
extern void test_potentiometer_common_can_be_turned();
extern void test_potentiometer_basic_can_be_turned_to_minimum();
extern void test_potentiometer_basic_can_be_turned_to_maximum();
extern void test_potentiometer_alternative_can_be_turned_to_minimum();
extern void test_potentiometer_alternative_can_be_turned_to_maximum();
extern void test_potentiometer_advanced_can_be_turned_to_minimum();
extern void test_potentiometer_advanced_can_be_turned_to_maximum();

// LED test methods
extern void test_led_can_be_turned_on_and_off();
extern void test_led_can_toggle();
extern void test_led_can_change_brightness();
extern void test_led_cant_change_brightness_beyond_maximum();
extern void test_led_cant_change_brightness_beyond_minimum();
extern void test_led_can_be_calibrated();
extern void test_led_cant_be_calibrated_beyond_maximum();
extern void test_led_cant_be_calibrated_beyond_minimum();

// Multiplexer test methods
extern void test_buttons_can_be_multiplexed();
extern void test_potentiometers_can_be_multiplexed();
extern void test_rotary_encoders_can_be_multiplexed();


void setUp(void) {
    // Empty setup function
}

void tearDown(void) {
    // Empty teardown function
}

void setup()
{
    delay(2000);

    UNITY_BEGIN(); // Start Unity Testing Framework

    // Button tests
    RUN_TEST(test_button_common_initial_state);
    RUN_TEST(test_button_common_can_be_disabled_and_enabled);
    RUN_TEST(test_button_common_can_be_pressed_and_released);
    RUN_TEST(test_button_basic_can_be_pressed_and_released);
    RUN_TEST(test_button_alternative_can_be_pressed_and_released);
    RUN_TEST(test_button_advanced_can_be_pressed_and_released);

    // Encoder tests
    RUN_TEST(test_encoder_common_initial_state);
    RUN_TEST(test_encoder_common_can_be_disabled_and_enabled);
    RUN_TEST(test_encoder_basic_can_be_turned_left);
    RUN_TEST(test_encoder_basic_can_be_turned_right);
    RUN_TEST(test_encoder_alternative_can_be_turned_left);
    RUN_TEST(test_encoder_alternative_can_be_turned_right);
    RUN_TEST(test_encoder_advanced_can_be_turned_left);
    RUN_TEST(test_encoder_advanced_can_be_turned_right);
    RUN_TEST(test_encoder_pull_down_can_be_turned_left);
    RUN_TEST(test_encoder_pull_down_can_be_turned_right);

    // Potentiometer tests
    RUN_TEST(test_potentiometer_common_can_be_disabled_and_enabled);
    RUN_TEST(test_potentiometer_common_can_be_turned);
    RUN_TEST(test_potentiometer_basic_can_be_turned_to_minimum);
    RUN_TEST(test_potentiometer_basic_can_be_turned_to_maximum);
    RUN_TEST(test_potentiometer_alternative_can_be_turned_to_minimum);
    RUN_TEST(test_potentiometer_alternative_can_be_turned_to_maximum);
    RUN_TEST(test_potentiometer_advanced_can_be_turned_to_minimum);
    RUN_TEST(test_potentiometer_advanced_can_be_turned_to_maximum);

    // LED tests
    RUN_TEST(test_led_can_be_turned_on_and_off);
    RUN_TEST(test_led_can_toggle);
    RUN_TEST(test_led_can_change_brightness);
    RUN_TEST(test_led_cant_change_brightness_beyond_maximum);
    RUN_TEST(test_led_cant_change_brightness_beyond_minimum);
    RUN_TEST(test_led_can_be_calibrated);
    RUN_TEST(test_led_cant_be_calibrated_beyond_maximum);
    RUN_TEST(test_led_cant_be_calibrated_beyond_minimum);

    // Multiplexer tests
    RUN_TEST(test_buttons_can_be_multiplexed);
    RUN_TEST(test_rotary_encoders_can_be_multiplexed);
    RUN_TEST(test_potentiometers_can_be_multiplexed);

    UNITY_END(); // Finish Unity Testing
}

void loop()
{
    // Intentionally left blank, required for Arduino framework
}
