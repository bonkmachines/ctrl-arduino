/*!
 *  @file       CtrlPot.cpp
 *  Project     Arduino CTRL Library
 *  @brief      CTRL Library for interfacing with common controls
 *  @version    1.0
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
#include "CtrlGroup.h"

CtrlPot::CtrlPot(
    const uint8_t sig,
    const int maxOutputValue,
    const float sensitivity,
    const CallbackFunction onValueChangeCallback,
    CtrlMux* mux
) : Muxable(mux) {
    this->sig = sig;
    this->maxOutputValue = maxOutputValue;
    setSensitivity(sensitivity);
    this->onValueChangeCallback = onValueChangeCallback;
}

void CtrlPot::process()
{
    if (!this->isInitialized()) this->initialize();
    if (this->isDisabled()) return;
    const uint16_t newValue = this->processInput();
    if (newValue != this->lastValue) {
        const uint16_t mappedValue = map(newValue, 0, this->analogMax, 0, this->maxOutputValue);
        if (mappedValue != this->lastMappedValue) {
            this->onValueChange(mappedValue);
            this->lastMappedValue = mappedValue;
        }
        this->lastValue = newValue;
    }
}

uint16_t CtrlPot::getValue() const
{
    return this->lastMappedValue;
}

void CtrlPot::setOnValueChange(const CallbackFunction callback)
{
    this->onValueChangeCallback = callback;
}

void CtrlPot::initialize()
{
    if (!this->isMuxed()) pinMode(sig, INPUT);
    this->lastValue = CtrlPot::processInput();
    this->smoothedValue = static_cast<float>(this->lastValue);
    this->initialized = true;
}

bool CtrlPot::isInitialized() const { return this->initialized; }

uint16_t CtrlPot::processInput()
{
    uint16_t rawValue;
    if (this->isMuxed()) {
        rawValue = this->mux->readPotSig(this->sig, this->pinModeType);
    } else {
        #ifdef UNIT_TEST
            // Simulated analogRead for testing
            extern uint16_t mockPotentiometerInput;
            rawValue = mockPotentiometerInput;
        #else
            rawValue = analogRead(this->sig);
        #endif
    }

    // Apply exponential smoothing
    this->smoothedValue = this->smoothedValue + this->alpha * (static_cast<float>(rawValue) - this->smoothedValue);
    return static_cast<uint16_t>(this->smoothedValue);
}

void CtrlPot::onValueChange(const int value)
{
    if (this->grouped && this->group->onValueChangeCallback) {
        this->group->onValueChangeCallback(this, value);
    }
    if (this->onValueChangeCallback) {
        this->onValueChangeCallback(value);
    }
}

void CtrlPot::setSensitivity(float sensitivity)
{
    // Ensure sensitivity is within the valid range
    if (sensitivity < 0.01) sensitivity = 0.01;
    if (sensitivity > 100) sensitivity = 100;

    this->sensitivity = sensitivity;
    updateAlpha();
}

void CtrlPot::updateAlpha()
{
    // Map sensitivity (0.01 - 100) to alpha (0.0001 - 1)
    constexpr float minSensitivity = 0.01;
    constexpr float maxSensitivity = 100.0;
    constexpr float minAlpha = 0.0001;
    constexpr float maxAlpha = 1.0;

    this->alpha = ((this->sensitivity - minSensitivity) * (maxAlpha - minAlpha) / (maxSensitivity - minSensitivity)) + minAlpha;
}