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

void run_multiplexer_encoder_tests()
{
    RUN_TEST(test_mux_encoder_can_turn_left);
    RUN_TEST(test_mux_encoder_can_turn_right);
}
