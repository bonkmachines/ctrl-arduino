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
    const uint8_t maxBrightness,
    const uint8_t type
) {
    this->sig[0] = sigR;
    this->sig[1] = sigG;
    this->sig[2] = sigB;
    this->type = type;
    this->on = false;
    this->brightness = maxBrightness;
    this->maxBrightness = maxBrightness;
}

void CtrlRGBLed::initialize()
{
    if (this->initialized) return;
    for (const uint8_t pin : this->sig) {
        pinMode(pin, OUTPUT);
        this->writeChannel(pin, 0);
    }
    this->initialized = true;
}

void CtrlRGBLed::writeChannel(const uint8_t pin, const uint8_t value) const
{
    // A common anode LED lights up when its pin is pulled low, so its output is inverted.
    analogWrite(pin, this->type == COMMON_ANODE ? 255 - value : value);
}

void CtrlRGBLed::processOutput() const
{
    const CtrlRGB output = this->getOutputColor();
    this->writeChannel(this->sig[0], output.r);
    this->writeChannel(this->sig[1], output.g);
    this->writeChannel(this->sig[2], output.b);
}

void CtrlRGBLed::set(const bool state)
{
    state ? this->turnOn() : this->turnOff();
}

void CtrlRGBLed::toggle()
{
    this->set(!this->on);
}

void CtrlRGBLed::turnOn()
{
    if (this->isDisabled()) return;
    this->initialize();
    this->on = true;
    this->processOutput();
}

void CtrlRGBLed::turnOff()
{
    if (this->isDisabled()) return;
    this->initialize();
    this->on = false;
    this->processOutput();
}

void CtrlRGBLed::setColor(const uint8_t r, const uint8_t g, const uint8_t b)
{
    this->setColor(CtrlRGB{r, g, b});
}

void CtrlRGBLed::setColor(const CtrlRGB color)
{
    if (this->isDisabled()) return;
    this->initialize();
    this->color = color;
    if (this->on) {
        this->processOutput();
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
    if (this->on) {
        this->processOutput();
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
        this->processOutput();
    }
}

CtrlRGB CtrlRGBLed::getColor() const
{
    return this->color;
}

CtrlRGB CtrlRGBLed::getOutputColor() const
{
    if (!this->on) return CtrlColor::Off;
    return CtrlRGB{
        static_cast<uint8_t>(static_cast<uint16_t>(this->color.r) * this->brightness / 255),
        static_cast<uint8_t>(static_cast<uint16_t>(this->color.g) * this->brightness / 255),
        static_cast<uint8_t>(static_cast<uint16_t>(this->color.b) * this->brightness / 255)
    };
}

uint8_t CtrlRGBLed::getMaxBrightness() const
{
    return this->maxBrightness;
}

uint8_t CtrlRGBLed::getBrightness() const
{
    if (this->maxBrightness == 0) return 0;
    return (static_cast<uint16_t>(this->brightness) * 100 + this->maxBrightness / 2) / this->maxBrightness;
}

bool CtrlRGBLed::isOn() const
{
    return this->on;
}

bool CtrlRGBLed::isOff() const
{
    return !this->on;
}

bool CtrlRGBLed::isCommonAnode() const
{
    return this->type == COMMON_ANODE;
}
