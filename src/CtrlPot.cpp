/*!
 *  @file       CtrlPot.cpp
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

#include "CtrlPot.h"

CtrlPotBase::CtrlPotBase(
    const uint8_t sig,
    const int maxOutputValue,
    const uint8_t margin,
    CtrlMux* mux
) : Muxable(mux)
{
    this->sig = sig;
    this->maxOutputValue = maxOutputValue;
    this->margin = margin;
    if (!this->isMuxed()) pinMode(sig, INPUT);
    this->lastValue = CtrlPotBase::processInput();
}

uint16_t CtrlPotBase::processInput()
{
    if (this->isMuxed()) {
        if (this->mux->acquire()) {
            const uint16_t result = this->mux->analogReader(this->sig);
            this->mux->release();
            return result;
        }
        return this->lastValue;
    }
    #ifdef UNIT_TEST
        // Simulated analogRead for testing
        extern uint16_t mockPotentiometerInput;
        return mockPotentiometerInput;
    #else
        // Normal operation with real hardware
        return analogRead(this->sig);
    #endif
}

void CtrlPotBase::process()
{
    if (this->isDisabled()) return;

    uint16_t value = this->processInput();
    if (abs(value - this->lastValue) > this->margin) {
        if (value >= this->analogMax - this->margin) value = this->analogMax; // Snap to top
        if (value <= this->margin) value = 0; // Snap to bottom

        const uint16_t mappedValue = map(value, 0, this->analogMax, 0, this->maxOutputValue);
        if (mappedValue != this->lastMappedValue) {
            this->onValueChange(mappedValue);
            this->lastMappedValue = mappedValue;
        }
        this->lastValue = value;
    }
}

uint16_t CtrlPotBase::getValue() const { return this->lastMappedValue; }

void CtrlPotBase::onValueChange(int value) { }

CtrlPot::CtrlPot(
    const uint8_t sig,
    const int maxOutputValue,
    const uint8_t margin,
    const CallbackFunction onValueChangeCallback,
    CtrlMux* mux
): CtrlPotBase(sig, maxOutputValue, margin, mux),
    onValueChangeCallback(onValueChangeCallback) { }

void CtrlPot::setOnValueChange(const CallbackFunction callback)
{
    this->onValueChangeCallback = callback;
}

void CtrlPot::onValueChange(const int value)
{
    if (this->onValueChangeCallback) {
        this->onValueChangeCallback(value);
    }
}

CtrlPot CtrlPot::create(
    const uint8_t sig,
    const int maxOutputValue,
    const uint8_t margin,
    const CallbackFunction onValueChangeCallback,
    CtrlMux* mux
) {
    CtrlPot pot(
        sig,
        maxOutputValue,
        margin,
        onValueChangeCallback,
        mux
    );
    return pot;
}