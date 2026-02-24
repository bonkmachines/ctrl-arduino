#include <Arduino.h>
#include <unity.h>
#include "test_globals.h"

extern void run_button_common_tests();
extern void run_button_basic_tests();
extern void run_button_alternative_tests();
extern void run_button_advanced_tests();
extern void run_button_pull_down_tests();
extern void run_button_pull_up_tests();
extern void run_button_delayed_release_tests();

extern void run_encoder_common_tests();
extern void run_encoder_basic_tests();
extern void run_encoder_alternative_tests();
extern void run_encoder_advanced_tests();
extern void run_encoder_pull_down_tests();
extern void run_encoder_pull_up_tests();

extern void run_potentiometer_common_tests();
extern void run_potentiometer_basic_tests();
extern void run_potentiometer_alternative_tests();
extern void run_potentiometer_advanced_tests();

extern void run_led_tests();

extern void run_multiplexer_button_tests();
extern void run_multiplexer_encoder_tests();
extern void run_multiplexer_potentiometer_tests();

extern void run_group_button_tests();
extern void run_group_encoder_tests();
extern void run_group_potentiometer_tests();

extern void run_groupable_metadata_tests();

extern void run_interaction_tests();

void setUp(void)
{
    resetAllMocks();
}

void tearDown(void)
{
}

int run_tests()
{
    UNITY_BEGIN();

    run_button_common_tests();
    run_button_basic_tests();
    run_button_alternative_tests();
    run_button_advanced_tests();
    run_button_pull_down_tests();
    run_button_pull_up_tests();
    run_button_delayed_release_tests();

    run_encoder_common_tests();
    run_encoder_basic_tests();
    run_encoder_alternative_tests();
    run_encoder_advanced_tests();
    run_encoder_pull_down_tests();
    run_encoder_pull_up_tests();

    run_potentiometer_common_tests();
    run_potentiometer_basic_tests();
    run_potentiometer_alternative_tests();
    run_potentiometer_advanced_tests();

    run_led_tests();

    run_multiplexer_button_tests();
    run_multiplexer_encoder_tests();
    run_multiplexer_potentiometer_tests();

    run_group_button_tests();
    run_group_encoder_tests();
    run_group_potentiometer_tests();

    run_groupable_metadata_tests();

    run_interaction_tests();

    return UNITY_END();
}

#ifdef ARDUINO
void setup()
{
    delay(2000);
    Serial.begin(9600);
    while (!Serial) { }
    run_tests();
}

void loop()
{
}
#else
int main(int argc, char **argv)
{
    return run_tests();
}
#endif
