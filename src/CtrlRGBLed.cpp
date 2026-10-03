/*!
 *  @file       CtrlRGBLed.cpp
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

#include "CtrlRGBLed.h"

CtrlRGBLed::CtrlRGBLed(
    const uint8_t sigR,
    const uint8_t sigG,
    const uint8_t sigB,
    const uint8_t maxBrightness
) {
    this->sigR = sigR;
    this->sigG = sigG;
    this->sigB = sigB;
    this->on = false;
    this->brightness = maxBrightness;
    this->maxBrightness = maxBrightness;
}

void CtrlRGBLed::initialize()
{
    if (this->initialized) return;
    this->sigArr[0] = this-> sigR;
    this->sigArr[1] = this-> sigG;
    this->sigArr[2] = this-> sigB;

    for (uint8_t i = 0; i < 3; i++) {
        pinMode(this->sigArr[i], OUTPUT);
        analogWrite(this->sigArr[i], 0);
    }
    this->initialized = true;
}

void CtrlRGBLed::processOutput() const {
    for (uint8_t i = 0; i < 3; i++) {
        uint8_t out = 0;
        if (this->maxBrightness > 0) {
            out = (uint16_t(this->rgbArr[i]) * uint16_t(this->brightness)) / 255;
        }
        analogWrite(this->sigArr[i], out);
    }
}

void CtrlRGBLed::set(bool state)
{
    if (this->isDisabled()) return;
    this->initialize();
    this->on = state;
    if (this->on) {
        processOutput();
    } else {
        for (uint8_t i = 0; i < 3; i++) {
            analogWrite(this->sigArr[i], 0);
        }
    }
}

void CtrlRGBLed::setRGB(const uint8_t rgb[3])
{
    if (this->isDisabled()) return;
    this->initialize();
    this->on = true;
    for (uint8_t i = 0; i < 3; i++) {
        this->rgbArr[i] = rgb[i];
    }
    processOutput();
}

void CtrlRGBLed::toggle()
{
    if (this->isDisabled()) return;
    this->initialize();
    this->on = !this->on;
    if (this->on) {
        processOutput();
    } else {
        for (uint8_t i = 0; i < 3; i++) {
            analogWrite(this->sigArr[i], 0);
        }
    }
}

void CtrlRGBLed::turnOn()
{
    if (this->isDisabled()) return;
    this->initialize();
    this->on = true;
    processOutput();
}

void CtrlRGBLed::turnOff()
{
    if (this->isDisabled()) return;
    this->initialize();
    this->on = false;
    for (uint8_t i = 0; i < 3; i++) {
        analogWrite(this->sigArr[i], 0);
    }
}

void CtrlRGBLed::setMaxBrightness(int maxBrightness)
{
    if (maxBrightness > 255) maxBrightness = 255;
    if (maxBrightness < 0) maxBrightness = 0;
    this->maxBrightness = maxBrightness;
    if (this->brightness > this->maxBrightness) {
        this->brightness = this->maxBrightness;
    }
}

void CtrlRGBLed::setBrightness(int percentage)
{
    if (this->isDisabled()) return;
    this->initialize();
    if (percentage > 100) percentage = 100;
    if (percentage < 0) percentage = 0;
    this->brightness = map(percentage, 0, 100, 0, this->maxBrightness);
    if (this->on) {
        processOutput();
    }
}

uint8_t CtrlRGBLed::getMaxBrightness() const
{
    return this->maxBrightness;
}

uint8_t CtrlRGBLed::getBrightness() const
{
    if (this->maxBrightness == 0) return 0;
    return map(this->brightness, 0, this->maxBrightness, 0, 100);
}

std::array<uint8_t, 3> CtrlRGBLed::getRGBRaw() const {
    return this->rgbArr;
}

std::array<uint8_t, 3> CtrlRGBLed::getRGB() const {
    std::array<uint8_t, 3> var = {0, 0, 0};
    if (this->maxBrightness > 0) {
        for (uint8_t i = 0; i < 3; i++) {
            var[i] = (uint16_t(this->rgbArr[i]) * uint16_t(this->brightness)) / 255;
        }
    }
    return var;
}

bool CtrlRGBLed::isOn() const
{
    return this->on;
}

bool CtrlRGBLed::isOff() const
{
    return !this->on;
}