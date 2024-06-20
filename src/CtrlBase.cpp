/*!
 *  @file       CtrlBase.cpp
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

Muxable::Muxable(
    CtrlMux* mux
) {
    this->mux = mux;
    this->muxed = mux != nullptr;
}

void Muxable::enable()
{
    this->enabled = true;
}

void Muxable::disable()
{
    this->enabled = false;
}

bool Muxable::isEnabled() const
{
    return this->enabled;
}

bool Muxable::isDisabled() const
{
    return !this->isEnabled();
}

bool Muxable::isMuxed() const
{
    return this->muxed;
}

void Muxable::setMultiplexer(CtrlMux &mux)
{
    this->mux = &mux;
    this->muxed = true;
}

void setDelayMicroseconds(const uint64_t duration)
{
    const uint64_t startTime = micros();
    const uint64_t targetTime = startTime + duration;
    while (micros() < targetTime) { }
}

void setDelayMilliseconds(const uint64_t duration)
{
    const uint64_t startTime = millis();
    const uint64_t targetTime = startTime + duration;
    while (millis() < targetTime) { }
}

uint8_t DISCONNECTED = UINT8_MAX;
uint8_t PULL_DOWN = 0; // External resistor is of type pull down.
uint8_t PULL_UP = 1; // External resistor is of type pull up.