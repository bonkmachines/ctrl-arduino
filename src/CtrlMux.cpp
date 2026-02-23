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
#include "Muxable.h"

CtrlMux::CtrlMux(
    const uint8_t sig,
    const uint8_t s0,
    const uint8_t s1,
    const uint8_t s2,
    const uint8_t s3
) : sig(sig),
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

CtrlMux::~CtrlMux() {
    for (size_t i = 0; i < this->objectCount; ++i) {
        this->objects[i]->mux = nullptr;
        this->objects[i]->muxed = false;
    }
    delete[] this->objects;
}

void CtrlMux::setPinMode(const uint8_t pinModeType)
{
    if (this->currentPinMode != pinModeType) {
        pinMode(this->sig, pinModeType);
        this->currentPinMode = pinModeType;
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

void CtrlMux::addObject(Muxable* object) {
    if (this->objectCount == this->capacity) {
        resize();
    }
    this->objects[this->objectCount++] = object;
}

void CtrlMux::removeObject(Muxable* object) {
    for (size_t i = 0; i < this->objectCount; ++i) {
        if (this->objects[i] == object) {
            for (size_t j = i; j < this->objectCount - 1; ++j) {
                this->objects[j] = this->objects[j + 1];
            }
            --this->objectCount;
            if (this->nextIndex >= this->objectCount && this->objectCount > 0) {
                this->nextIndex = 0;
            }
            return;
        }
    }
}

void CtrlMux::process(const uint8_t count)
{
    if (this->objectCount == 0) return;
    if (count == 0) {
        for (size_t i = 0; i < this->objectCount; ++i) {
            this->objects[i]->process();
        }
    } else {
        const uint8_t n = count > this->objectCount ? static_cast<uint8_t>(this->objectCount) : count;
        for (uint8_t i = 0; i < n; ++i) {
            this->objects[this->nextIndex]->process();
            this->nextIndex = (this->nextIndex + 1) % this->objectCount;
        }
    }
}

bool CtrlMux::readBtnSig(const uint8_t channel, const uint8_t pinModeType)
{
    this->setPinMode(pinModeType);

    this->setChannel(channel);

    delayMicroseconds(this->switchInterval);

    return digitalRead(this->sig);
}

bool CtrlMux::readEncClk(const uint8_t channel, const uint8_t pinModeType)
{
    this->setPinMode(pinModeType);

    this->setChannel(channel);

    delayMicroseconds(this->switchInterval);

    return digitalRead(this->sig);
}

bool CtrlMux::readEncDt(const uint8_t channel, const uint8_t pinModeType)
{
    this->setPinMode(pinModeType);

    this->setChannel(channel);

    delayMicroseconds(this->switchInterval);

    return digitalRead(this->sig);
}

uint16_t CtrlMux::readPotSig(const uint8_t channel, const uint8_t pinModeType)
{
    this->setPinMode(pinModeType);

    this->setChannel(channel);

    delayMicroseconds(this->switchInterval);

    return analogRead(this->sig);
}

void CtrlMux::setSwitchInterval(const uint8_t interval)
{
    this->switchInterval = interval;
}

void CtrlMux::reserve(const size_t capacity) {
    if (capacity <= this->capacity) return;
    auto** newObjects = new Muxable*[capacity];
    for (size_t i = 0; i < this->objectCount; ++i) {
        newObjects[i] = this->objects[i];
    }
    delete[] this->objects;
    this->objects = newObjects;
    this->capacity = capacity;
}

void CtrlMux::resize() {
    const size_t newCapacity = this->capacity == 0 ? 4 : this->capacity * 2;
    auto** newObjects = new Muxable*[newCapacity];
    for (size_t i = 0; i < this->objectCount; ++i) {
        newObjects[i] = this->objects[i];
    }
    delete[] this->objects;
    this->objects = newObjects;
    this->capacity = newCapacity;
}