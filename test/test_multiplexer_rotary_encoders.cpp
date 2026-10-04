#include <Arduino.h>
#include <CtrlEnc.h>
#include <CtrlMux.h>
#include <unity.h>
#include "test_globals.h"

static void test_mux_encoder_can_turn_left()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);

    CtrlEnc encoder(0, 1, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });

    encoder.setMultiplexer(&mux);

    int seq_idle[] = {LOW, LOW};
    _mock_set_digital_sequence(MUX_SIG_PIN, seq_idle, 2);
    for (int i = 0; i < 10; ++i) mux.process();

    int seq_step[] = {LOW, HIGH};
    _mock_set_digital_sequence(MUX_SIG_PIN, seq_step, 2);
    for (int i = 0; i < 10; ++i) mux.process();

    int seq_done[] = {HIGH, HIGH};
    _mock_set_digital_sequence(MUX_SIG_PIN, seq_done, 2);
    for (int i = 0; i < 10; ++i) mux.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedLeft, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnLeftCount);
}

static void test_mux_encoder_can_turn_right()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);

    CtrlEnc encoder(0, 1, []{ tracker.recordTurnLeft(); }, []{ tracker.recordTurnRight(); });

    encoder.setMultiplexer(&mux);

    int seq_idle[] = {LOW, LOW};
    _mock_set_digital_sequence(MUX_SIG_PIN, seq_idle, 2);
    for (int i = 0; i < 10; ++i) mux.process();

    int seq_step[] = {HIGH, LOW};
    _mock_set_digital_sequence(MUX_SIG_PIN, seq_step, 2);
    for (int i = 0; i < 10; ++i) mux.process();

    int seq_done[] = {HIGH, HIGH};
    _mock_set_digital_sequence(MUX_SIG_PIN, seq_done, 2);
    for (int i = 0; i < 10; ++i) mux.process();

    TEST_ASSERT_EQUAL(TestEvent::EncoderTurnedRight, tracker.lastEvent);
    TEST_ASSERT_EQUAL_INT(1, tracker.turnRightCount);
}

static void test_mux_encoder_selects_clk_then_dt_channel()
{
    CtrlMux mux(MUX_SIG_PIN, MUX_S0_PIN, MUX_S1_PIN, MUX_S2_PIN, MUX_S3_PIN);
    CtrlEnc encoder(9, 6); // CLK on channel 9 (0b1001), DT on channel 6 (0b0110)
    encoder.setMultiplexer(&mux);

    mux.process();

    // DT is read last, so the select pins are left on its channel.
    TEST_ASSERT_EQUAL_INT(LOW, digitalRead(MUX_S0_PIN));
    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(MUX_S1_PIN));
    TEST_ASSERT_EQUAL_INT(HIGH, digitalRead(MUX_S2_PIN));
    TEST_ASSERT_EQUAL_INT(LOW, digitalRead(MUX_S3_PIN));
}

void run_multiplexer_encoder_tests()
{
    RUN_TEST(test_mux_encoder_can_turn_left);
    RUN_TEST(test_mux_encoder_can_turn_right);
    RUN_TEST(test_mux_encoder_selects_clk_then_dt_channel);
}
