/*!
 *  @file       CtrlLed.cpp
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

#include "CtrlLed.h"

CtrlLed::CtrlLed(
    const uint8_t sig,
    const uint8_t maxBrightness
) {
    this->sig = sig;
    this->on = false;
    this->brightness = maxBrightness;
    this->maxBrightness = maxBrightness;
    this->pwmMode = true;
    pinMode(sig, OUTPUT);
    analogWrite(sig, 0);
}

CtrlLed::CtrlLed(const uint8_t sig) {
    this->sig = sig;
    this->on = false;
    this->brightness = 0;
    this->maxBrightness = 0;
    this->pwmMode = false;
    pinMode(sig, OUTPUT);
    digitalWrite(sig, LOW);
}

void CtrlLed::processOutput(const uint8_t sig, const uint8_t brightness)
{
    analogWrite(sig, brightness);
}

void CtrlLed::toggle()
{
    this->on = !this->on;
    if (this->pwmMode) {
        if (this->on) {
            processOutput(sig, brightness);
        } else {
            processOutput(sig, 0);
        }
    } else {
        digitalWrite(sig, this->on ? HIGH : LOW);
    }
}

void CtrlLed::turnOn()
{
    this->on = true;
    if (this->pwmMode) {
        processOutput(this->sig, this->brightness);
    } else {
        digitalWrite(this->sig, HIGH);
    }
}

void CtrlLed::turnOff()
{
    this->on = false;
    if (this->pwmMode) {
        processOutput(this->sig, 0);
    } else {
        digitalWrite(this->sig, LOW);
    }
}

void CtrlLed::setMaxBrightness(int maxBrightness)
{
    if (!this->pwmMode) return;
    if (maxBrightness > 255) maxBrightness = 255;
    if (maxBrightness < 0) maxBrightness = 0;
    this->maxBrightness = maxBrightness;
}

void CtrlLed::setBrightness(int percentage)
{
    if (!this->pwmMode) return;
    if (percentage > 100) percentage = 100;
    if (percentage < 0) percentage = 0;
    this->brightness = map(percentage, 0, 100, 0, this->maxBrightness);
    if (this->on) {
        processOutput(this->sig, this->brightness);
    }
}

uint8_t CtrlLed::getMaxBrightness() const
{
    return this->maxBrightness;
}

uint8_t CtrlLed::getBrightness() const
{
    return map(this->brightness, 0, this->maxBrightness, 0, 100);
}

bool CtrlLed::isOn() const
{
    return this->on;
}

bool CtrlLed::isOff() const
{
    return !this->on;
}

bool CtrlLed::isPwmMode() const
{
    return this->pwmMode;
}