/*!
 *  @file       CtrlMux.cpp
 *  Project     Arduino CTRL Library
 *  @brief      CTRL Library for interfacing with common controls
 *  @author     Johannes Jan Prins
 *  @date       08/05/2024
 *  @license    MIT - Copyright (c) 2024 Johannes Jan Prins
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "CtrlBase.h"
#include "CtrlMux.h"

CtrlMux::CtrlMux(
    const uint8_t count,
    const uint8_t switchInterval,
    const uint8_t sig,
    const uint8_t s0,
    const uint8_t s1,
    const uint8_t s2,
    const uint8_t s3
) : count(count),
    switchInterval(switchInterval),
    sig(sig),
    s0(s0),
    s1(s1),
    s2(s2),
    s3(s3),
    s3Present(s3 != UINT8_MAX)
{
    pinMode(this->s0, OUTPUT);
    pinMode(this->s1, OUTPUT);
    pinMode(this->s2, OUTPUT);
    if (this->s3Present) {
        pinMode(this->s3, OUTPUT);
    }
}

void CtrlMux::setSignalPinToDigitalIn()
{
    if (this->currentPinMode != INPUT_PULLUP) {
        pinMode(this->sig, INPUT_PULLUP);
        this->currentPinMode = INPUT_PULLUP;
    }
}

void CtrlMux::setSignalPinToAnalogIn()
{
    if (this->currentPinMode != INPUT) {
        pinMode(this->sig, INPUT);
        this->currentPinMode = INPUT;
    }
}

void CtrlMux::setChannel(const uint8_t channel) const
{
    digitalWrite(this->s0, bitRead(channel, 0));
    digitalWrite(this->s1, bitRead(channel, 1));
    digitalWrite(this->s2, bitRead(channel, 2));
    if (this->s3Present) {
        digitalWrite(this->s3, bitRead(channel, 3));
    }
}

void CtrlMux::subscribe(const uint8_t channel)
{
    this->subscribers[channel] = 1;
}

bool CtrlMux::subscribed(const uint8_t channel) const
{
    return this->subscribers[channel] == 1;
}

bool CtrlMux::subscriptionComplete() const
{
    for (uint8_t i = 0; i < this->count; i++) {
        if (this->subscribers[i] != 1) return false;
    }
    return true;
}

bool CtrlMux::acquire(const uint8_t channel)
{
    if (!this->subscribed(channel)) {
        this->subscribe(channel);
        return false;
    }
    if (!this->subscriptionComplete()) {
        return false;
    }
    if (!this->occupied && this->subscriberIsNext(channel)) {
        this->occupied = true;
        this->previousSubscriber = channel;
        return true;
    }
    return false;
}

bool CtrlMux::subscriberIsNext(const uint8_t channel) const
{
    if (this->count == 1) return true; // If we declare one possible subscriber, it's always next :)
    if (this->previousSubscriber == this->count - 1) return channel == 0; // We reach the final subscriber and go back to 0
    return this->previousSubscriber == channel - 1;
}

void CtrlMux::release()
{
    this->occupied = false;
}

uint8_t CtrlMux::digitalReader(const uint8_t channel)
{
    this->setSignalPinToDigitalIn();

    this->setChannel(channel);

    setDelayMicroseconds(this->switchInterval);

    return digitalRead(this->sig);
}

uint16_t CtrlMux::analogReader(const uint8_t channel)
{
    this->setSignalPinToAnalogIn();

    this->setChannel(channel);

    setDelayMicroseconds(this->switchInterval);

    return analogRead(this->sig);
}