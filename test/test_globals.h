#ifndef TEST_GLOBALS_H
#define TEST_GLOBALS_H

#include <Arduino.h>
#include <cstdint>
#include <cstring>

static constexpr uint8_t BTN_PIN = 2;
static constexpr uint8_t ENC_CLK_PIN = 3;
static constexpr uint8_t ENC_DT_PIN = 4;
static constexpr uint8_t POT_PIN = 5;

static constexpr uint8_t MUX_SIG_PIN = 10;
static constexpr uint8_t MUX_S0_PIN = 11;
static constexpr uint8_t MUX_S1_PIN = 12;
static constexpr uint8_t MUX_S2_PIN = 13;
static constexpr uint8_t MUX_S3_PIN = 14;

enum class TestEvent : uint8_t {
    None,
    ButtonPressed,
    ButtonReleased,
    ButtonDelayedRelease,
    EncoderTurnedLeft,
    EncoderTurnedRight,
    PotValueChanged
};

struct TestTracker {
    TestEvent lastEvent;
    int lastValue;
    int eventCount;
    int pressCount;
    int releaseCount;
    int delayedReleaseCount;
    int turnLeftCount;
    int turnRightCount;
    int valueChangeCount;

    void reset() {
        lastEvent = TestEvent::None;
        lastValue = -1;
        eventCount = 0;
        pressCount = 0;
        releaseCount = 0;
        delayedReleaseCount = 0;
        turnLeftCount = 0;
        turnRightCount = 0;
        valueChangeCount = 0;
    }

    void recordPress() {
        lastEvent = TestEvent::ButtonPressed;
        ++pressCount;
        ++eventCount;
    }

    void recordRelease() {
        lastEvent = TestEvent::ButtonReleased;
        ++releaseCount;
        ++eventCount;
    }

    void recordDelayedRelease() {
        lastEvent = TestEvent::ButtonDelayedRelease;
        ++delayedReleaseCount;
        ++eventCount;
    }

    void recordTurnLeft() {
        lastEvent = TestEvent::EncoderTurnedLeft;
        ++turnLeftCount;
        ++eventCount;
    }

    void recordTurnRight() {
        lastEvent = TestEvent::EncoderTurnedRight;
        ++turnRightCount;
        ++eventCount;
    }

    void recordValueChange(int value) {
        lastEvent = TestEvent::PotValueChanged;
        lastValue = value;
        ++valueChangeCount;
        ++eventCount;
    }
};

extern TestTracker tracker;

void resetAllMocks();

static constexpr float TEST_SENSITIVITY = 50.0f;
static constexpr uint16_t TEST_DEBOUNCE = 15;
static constexpr int POT_MAX_ITERATIONS = 100000;

template<typename ProcessFn, typename ValueFn>
void converge(ProcessFn process, ValueFn getValue, int expected)
{
    for (int i = 0; i < POT_MAX_ITERATIONS; ++i) {
        process();
        if (getValue() == expected) return;
    }
}

#endif
