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
    this->maxOutputValue = maxOutputValue < 0 ? 0 : maxOutputValue;
    setSensitivity(sensitivity);
    this->onValueChangeCallback = onValueChangeCallback;
}

void CtrlPot::process()
{
    if (!this->isInitialized()) this->initialize();

    const auto irqState = ctrlSaveInterrupts();
    const bool pending = this->isrValuePending;
    const uint16_t raw = this->isrRawValue;
    this->isrValuePending = false;
    ctrlRestoreInterrupts(irqState);

    if (this->isDisabled()) return;
    if (pending) {
        this->processSmoothedValue(this->applySmoothing(raw));
    } else {
        this->processSmoothedValue(this->processInput());
    }
}

void CtrlPot::setRawValue(const uint16_t rawValue)
{
    if (!this->initialized) {
        this->smoothedValue_q16 = static_cast<uint32_t>(rawValue) << 16;
        this->initialized = true;
    }
    if (this->isDisabled()) return;
    this->processSmoothedValue(this->applySmoothing(rawValue));
}

void CtrlPot::storeRaw(const uint16_t rawValue)
{
    const auto irqState = ctrlSaveInterrupts();
    this->isrRawValue = rawValue;
    this->isrValuePending = true;
    ctrlRestoreInterrupts(irqState);
}

uint16_t CtrlPot::getValue() const
{
    const auto irqState = ctrlSaveInterrupts();
    const uint16_t val = this->lastMappedValue;
    ctrlRestoreInterrupts(irqState);
    return val;
}

void CtrlPot::setAnalogMax(const uint16_t analogMax)
{
    if (analogMax == 0) return;
    this->analogMax = analogMax;
}

uint16_t CtrlPot::getAnalogMax() const
{
    return this->analogMax;
}

void CtrlPot::setOnValueChange(const CallbackFunction callback)
{
    this->onValueChangeCallback = callback;
}

void CtrlPot::initialize()
{
    if (!this->isMuxed()) pinMode(sig, INPUT);
    this->lastValue = this->processInput();
    this->smoothedValue_q16 = static_cast<uint32_t>(this->lastValue) << 16;
    this->initialized = true;
}

bool CtrlPot::isInitialized() const { return this->initialized; }

uint16_t CtrlPot::processInput()
{
    uint16_t rawValue;
    if (this->isMuxed()) {
        rawValue = this->mux->readPotSig(this->sig, this->pinModeType);
    } else {
        rawValue = analogRead(this->sig);
    }
    return this->applySmoothing(rawValue);
}

uint16_t CtrlPot::applySmoothing(const uint16_t rawValue)
{
    const uint32_t raw_q16 = static_cast<uint32_t>(rawValue) << 16;
    const int64_t diff = static_cast<int64_t>(raw_q16) - static_cast<int64_t>(this->smoothedValue_q16);
    const int64_t step = (static_cast<int64_t>(this->alpha_q16) * diff) >> 16;
    if (step < 0 && static_cast<uint32_t>(-step) > this->smoothedValue_q16) {
        this->smoothedValue_q16 = 0;
    } else {
        this->smoothedValue_q16 = static_cast<uint32_t>(static_cast<int64_t>(this->smoothedValue_q16) + step);
    }
    const uint32_t maxQ16 = static_cast<uint32_t>(this->analogMax) << 16;
    if (this->smoothedValue_q16 > maxQ16) this->smoothedValue_q16 = maxQ16;
    return static_cast<uint16_t>((this->smoothedValue_q16 + (1u << 15)) >> 16);
}

void CtrlPot::processSmoothedValue(const uint16_t newValue)
{
    if (newValue != this->lastValue) {
        const uint16_t mappedValue = static_cast<uint16_t>(
            (static_cast<uint32_t>(newValue) * this->maxOutputValue + (this->analogMax / 2)) / this->analogMax
        );
        this->lastValue = newValue;
        if (mappedValue != this->lastMappedValue) {
            this->lastMappedValue = mappedValue;
            this->onValueChange(mappedValue);
        }
    }
}

void CtrlPot::onValueChange(const int value)
{
    const auto callback = this->onValueChangeCallback;
    if (this->isGrouped() && this->group->onValueChangeCallback) {
        this->group->onValueChangeCallback(*this, value);
    }
    if (callback) {
        callback(value);
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
    constexpr float minSensitivity = 0.01f;
    constexpr float maxSensitivity = 100.0f;
    constexpr float minAlpha = 0.0001f;
    constexpr float maxAlpha = 1.0f;

    const float alpha = ((this->sensitivity - minSensitivity) * (maxAlpha - minAlpha) / (maxSensitivity - minSensitivity)) + minAlpha;
    this->alpha_q16 = static_cast<uint32_t>(alpha * 65536.0f);
    if (this->alpha_q16 == 0) this->alpha_q16 = 1;
}