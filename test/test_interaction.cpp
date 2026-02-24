#include <Arduino.h>
#include <unity.h>
#include "CtrlBtn.h"
#include "CtrlEnc.h"
#include "CtrlPot.h"
#include "CtrlGroup.h"
#include "CtrlMux.h"
#include "test_globals.h"

static constexpr uint8_t BTN_A_PIN = 20;
static constexpr uint8_t BTN_B_PIN = 21;

static TestTracker trackerA;
static TestTracker trackerB;

static void test_two_buttons_in_group_independent_events()
{
    trackerA.reset();
    trackerB.reset();

    CtrlGroup group;
    CtrlBtn btnA(BTN_A_PIN, TEST_DEBOUNCE, []{ trackerA.recordPress(); }, []{ trackerA.recordRelease(); });
    CtrlBtn btnB(BTN_B_PIN, TEST_DEBOUNCE, []{ trackerB.recordPress(); }, []{ trackerB.recordRelease(); });

    btnA.setGroup(&group);
    btnB.setGroup(&group);

    _mock_digital_pins()[BTN_A_PIN] = HIGH;
    _mock_digital_pins()[BTN_B_PIN] = HIGH;
    group.process();

    _mock_digital_pins()[BTN_A_PIN] = LOW;
    _mock_digital_pins()[BTN_B_PIN] = HIGH;
    group.process();
    delay(TEST_DEBOUNCE + 1);
    group.process();

    TEST_ASSERT_EQUAL_INT(1, trackerA.pressCount);
    TEST_ASSERT_EQUAL_INT(0, trackerB.pressCount);

    _mock_digital_pins()[BTN_A_PIN] = HIGH;
    group.process();
    delay(TEST_DEBOUNCE + 1);
    group.process();

    TEST_ASSERT_EQUAL_INT(1, trackerA.releaseCount);
    TEST_ASSERT_EQUAL_INT(0, trackerB.releaseCount);
}

static void test_multiple_pots_on_mux_converge_independently()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);

    CtrlPot potA(0, 100, TEST_SENSITIVITY, [](int val){ tracker.recordValueChange(val); });
    CtrlPot potB(1, 200, TEST_SENSITIVITY);

    potA.setMultiplexer(&mux);
    potB.setMultiplexer(&mux);

    _mock_analog_pins()[MUX_SIG_PIN] = 1023;

    converge(
        [&]{ mux.process(); },
        [&]{ return (int)potA.getValue(); },
        100
    );

    converge(
        [&]{ mux.process(); },
        [&]{ return (int)potB.getValue(); },
        200
    );

    TEST_ASSERT_EQUAL_INT(100, potA.getValue());
    TEST_ASSERT_EQUAL_INT(200, potB.getValue());
}

static void test_button_and_encoder_coexist_in_separate_groups()
{
    CtrlGroup btnGroup;
    CtrlGroup encGroup;

    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); });
    CtrlEnc encoder(ENC_CLK_PIN, ENC_DT_PIN, []{ tracker.recordTurnLeft(); });

    button.setGroup(&btnGroup);
    encoder.setGroup(&encGroup);

    btnGroup.process();
    encGroup.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    btnGroup.process();
    delay(TEST_DEBOUNCE + 1);
    btnGroup.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
    TEST_ASSERT_EQUAL_INT(0, tracker.turnLeftCount);

    _mock_digital_pins()[ENC_DT_PIN] = HIGH;
    encGroup.process();
    _mock_digital_pins()[ENC_CLK_PIN] = HIGH;
    encGroup.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnLeftCount);
}

static void test_pot_sensitivity_extreme_low()
{
    CtrlPot potentiometer(POT_PIN, 100, 0.01f);

    _mock_analog_pins()[POT_PIN] = 1023;

    converge(
        [&]{ potentiometer.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        100
    );

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue());
}

static void test_pot_sensitivity_extreme_high()
{
    CtrlPot potentiometer(POT_PIN, 100, 100.0f);

    potentiometer.process();

    _mock_analog_pins()[POT_PIN] = 1023;

    converge(
        [&]{ potentiometer.process(); },
        [&]{ return (int)potentiometer.getValue(); },
        100
    );

    TEST_ASSERT_EQUAL_INT(100, potentiometer.getValue());
}

static void test_pot_max_output_zero()
{
    CtrlPot potentiometer(POT_PIN, 0, TEST_SENSITIVITY);

    _mock_analog_pins()[POT_PIN] = 1023;

    for (int i = 0; i < 200; ++i) {
        potentiometer.process();
    }

    TEST_ASSERT_EQUAL_INT(0, potentiometer.getValue());
}

static void test_mux_set_switch_interval()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);
    CtrlBtn button(0, TEST_DEBOUNCE, []{ tracker.recordPress(); });

    button.setMultiplexer(&mux);
    mux.setSwitchInterval(10);

    _mock_digital_pins()[MUX_SIG_PIN] = HIGH;
    mux.process();

    _mock_digital_pins()[MUX_SIG_PIN] = LOW;
    mux.process();
    delay(TEST_DEBOUNCE + 1);
    mux.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

static void test_set_group_reassignment()
{
    CtrlGroup groupA;
    CtrlGroup groupB;

    groupA.setOnPress([](Groupable&) { tracker.recordPress(); });
    groupB.setOnPress([](Groupable&) { tracker.recordRelease(); });

    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE);
    button.setGroup(&groupA);

    groupA.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    groupA.process();
    delay(TEST_DEBOUNCE + 1);
    groupA.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
    TEST_ASSERT_EQUAL_INT(0, tracker.releaseCount);
}

static void test_set_group_reassignment_removes_from_old_group()
{
    trackerA.reset();
    trackerB.reset();

    CtrlGroup groupA;
    CtrlGroup groupB;

    groupA.setOnPress([](Groupable&) { trackerA.recordPress(); });
    groupB.setOnPress([](Groupable&) { trackerB.recordPress(); });

    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE);
    button.setGroup(&groupA);

    _mock_digital_pins()[BTN_PIN] = HIGH;
    groupA.process();

    button.setGroup(&groupB);

    _mock_digital_pins()[BTN_PIN] = HIGH;
    groupA.process();
    groupB.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    groupA.process();
    groupB.process();
    delay(TEST_DEBOUNCE + 1);
    groupA.process();
    groupB.process();

    TEST_ASSERT_EQUAL_INT(0, trackerA.pressCount);
    TEST_ASSERT_EQUAL_INT(1, trackerB.pressCount);
}

static void test_set_multiplexer_reassignment()
{
    CtrlMux muxA(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);
    CtrlMux muxB(6, 7, 8, 9, 10);

    CtrlBtn button(0, TEST_DEBOUNCE, []{ tracker.recordPress(); });
    button.setMultiplexer(&muxA);

    _mock_digital_pins()[MUX_SIG_PIN] = HIGH;
    muxA.process();

    _mock_digital_pins()[MUX_SIG_PIN] = LOW;
    muxA.process();
    delay(TEST_DEBOUNCE + 1);
    muxA.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);

    button.setMultiplexer(&muxB);

    _mock_digital_pins()[6] = HIGH;
    muxB.process();
    delay(TEST_DEBOUNCE + 1);
    muxB.process();

    _mock_digital_pins()[6] = LOW;
    muxB.process();
    delay(TEST_DEBOUNCE + 1);
    muxB.process();

    TEST_ASSERT_EQUAL_INT(2, tracker.pressCount);
}

static void test_set_multiplexer_reassignment_removes_from_old_mux()
{
    trackerA.reset();
    trackerB.reset();

    CtrlMux muxA(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);
    CtrlMux muxB(6, 7, 8, 9, 10);

    CtrlBtn button(0, TEST_DEBOUNCE, []{ trackerA.recordPress(); });
    button.setMultiplexer(&muxA);

    _mock_digital_pins()[MUX_SIG_PIN] = HIGH;
    muxA.process();

    button.setMultiplexer(&muxB);

    _mock_digital_pins()[MUX_SIG_PIN] = LOW;
    muxA.process();
    delay(TEST_DEBOUNCE + 1);
    muxA.process();

    TEST_ASSERT_EQUAL_INT(0, trackerA.pressCount);

    _mock_digital_pins()[6] = HIGH;
    muxB.process();

    _mock_digital_pins()[6] = LOW;
    muxB.process();
    delay(TEST_DEBOUNCE + 1);
    muxB.process();

    TEST_ASSERT_EQUAL_INT(1, trackerA.pressCount);
}

static void test_mux_process_round_robin()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);

    CtrlBtn button(0, TEST_DEBOUNCE, []{ tracker.recordPress(); });
    button.setMultiplexer(&mux);

    _mock_digital_pins()[MUX_SIG_PIN] = HIGH;
    mux.process(1);

    _mock_digital_pins()[MUX_SIG_PIN] = LOW;
    mux.process(1);
    delay(TEST_DEBOUNCE + 1);
    mux.process(1);

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

static void test_mux_process_empty_mux()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);

    mux.process(1);

    TEST_ASSERT_EQUAL_INT(0, tracker.eventCount);
}

static void test_mux_reserve_pre_allocates()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);
    mux.reserve(8);

    CtrlBtn btn1(0, TEST_DEBOUNCE, []{ tracker.recordPress(); });
    CtrlBtn btn2(1, TEST_DEBOUNCE);
    CtrlBtn btn3(2, TEST_DEBOUNCE);
    CtrlBtn btn4(3, TEST_DEBOUNCE);
    CtrlBtn btn5(4, TEST_DEBOUNCE);

    btn1.setMultiplexer(&mux);
    btn2.setMultiplexer(&mux);
    btn3.setMultiplexer(&mux);
    btn4.setMultiplexer(&mux);
    btn5.setMultiplexer(&mux);

    _mock_digital_pins()[MUX_SIG_PIN] = HIGH;
    mux.process();

    _mock_digital_pins()[MUX_SIG_PIN] = LOW;
    mux.process();
    delay(TEST_DEBOUNCE + 1);
    mux.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

static void test_group_reserve_pre_allocates()
{
    CtrlGroup group;
    group.reserve(8);

    CtrlBtn btn1(BTN_A_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); });
    CtrlBtn btn2(BTN_B_PIN, TEST_DEBOUNCE);

    btn1.setGroup(&group);
    btn2.setGroup(&group);

    _mock_digital_pins()[BTN_A_PIN] = HIGH;
    _mock_digital_pins()[BTN_B_PIN] = HIGH;
    group.process();

    _mock_digital_pins()[BTN_A_PIN] = LOW;
    group.process();
    delay(TEST_DEBOUNCE + 1);
    group.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

static void test_group_process_round_robin()
{
    trackerA.reset();
    trackerB.reset();

    CtrlGroup group;
    CtrlBtn btnA(BTN_A_PIN, TEST_DEBOUNCE, []{ trackerA.recordPress(); }, []{ trackerA.recordRelease(); });
    CtrlBtn btnB(BTN_B_PIN, TEST_DEBOUNCE, []{ trackerB.recordPress(); }, []{ trackerB.recordRelease(); });

    btnA.setGroup(&group);
    btnB.setGroup(&group);

    _mock_digital_pins()[BTN_A_PIN] = HIGH;
    _mock_digital_pins()[BTN_B_PIN] = HIGH;

    group.process(1);
    group.process(1);

    _mock_digital_pins()[BTN_A_PIN] = LOW;

    group.process(1);
    delay(TEST_DEBOUNCE + 1);
    group.process(1);
    group.process(1);

    TEST_ASSERT_EQUAL_INT(1, trackerA.pressCount);
    TEST_ASSERT_EQUAL_INT(0, trackerB.pressCount);
}

static void test_group_process_empty_group()
{
    CtrlGroup group;

    group.process(1);

    TEST_ASSERT_EQUAL_INT(0, tracker.eventCount);
}

static void test_group_process_disabled_group()
{
    CtrlGroup group;
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); });
    button.setGroup(&group);

    group.disable();

    _mock_digital_pins()[BTN_PIN] = HIGH;
    group.process(1);

    _mock_digital_pins()[BTN_PIN] = LOW;
    group.process(1);
    delay(TEST_DEBOUNCE + 1);
    group.process(1);

    TEST_ASSERT_EQUAL_INT(0, tracker.pressCount);
}

static void test_mux_object_destroyed_unregisters()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);

    {
        CtrlBtn button(0, TEST_DEBOUNCE, []{ tracker.recordPress(); });
        button.setMultiplexer(&mux);

        _mock_digital_pins()[MUX_SIG_PIN] = HIGH;
        mux.process();

        _mock_digital_pins()[MUX_SIG_PIN] = LOW;
        mux.process();
        delay(TEST_DEBOUNCE + 1);
        mux.process();

        TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
    }

    mux.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

static void test_group_object_destroyed_unregisters()
{
    CtrlGroup group;

    {
        CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); });
        button.setGroup(&group);

        _mock_digital_pins()[BTN_PIN] = HIGH;
        group.process();

        _mock_digital_pins()[BTN_PIN] = LOW;
        group.process();
        delay(TEST_DEBOUNCE + 1);
        group.process();

        TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
    }

    group.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

static void test_mux_destroyed_before_objects_no_crash()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); });

    {
        CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);
        button.setMultiplexer(&mux);
    }

    TEST_ASSERT_FALSE(button.isMuxed());

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

static void test_group_destroyed_before_objects_no_crash()
{
    CtrlBtn button(BTN_PIN, TEST_DEBOUNCE, []{ tracker.recordPress(); });

    {
        CtrlGroup group;
        button.setGroup(&group);
    }

    TEST_ASSERT_FALSE(button.isGrouped());

    button.process();

    _mock_digital_pins()[BTN_PIN] = LOW;
    button.process();
    delay(TEST_DEBOUNCE + 1);
    button.process();

    TEST_ASSERT_EQUAL_INT(1, tracker.pressCount);
}

void run_interaction_tests()
{
    RUN_TEST(test_two_buttons_in_group_independent_events);
    RUN_TEST(test_multiple_pots_on_mux_converge_independently);
    RUN_TEST(test_button_and_encoder_coexist_in_separate_groups);
    RUN_TEST(test_pot_sensitivity_extreme_low);
    RUN_TEST(test_pot_sensitivity_extreme_high);
    RUN_TEST(test_pot_max_output_zero);
    RUN_TEST(test_mux_set_switch_interval);
    RUN_TEST(test_set_group_reassignment);
    RUN_TEST(test_set_group_reassignment_removes_from_old_group);
    RUN_TEST(test_set_multiplexer_reassignment);
    RUN_TEST(test_set_multiplexer_reassignment_removes_from_old_mux);
    RUN_TEST(test_mux_process_round_robin);
    RUN_TEST(test_mux_process_empty_mux);
    RUN_TEST(test_mux_reserve_pre_allocates);
    RUN_TEST(test_group_reserve_pre_allocates);
    RUN_TEST(test_group_process_round_robin);
    RUN_TEST(test_group_process_empty_group);
    RUN_TEST(test_group_process_disabled_group);
    RUN_TEST(test_mux_object_destroyed_unregisters);
    RUN_TEST(test_group_object_destroyed_unregisters);
    RUN_TEST(test_mux_destroyed_before_objects_no_crash);
    RUN_TEST(test_group_destroyed_before_objects_no_crash);
}
