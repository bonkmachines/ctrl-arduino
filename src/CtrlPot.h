/*!
 *  @file       CtrlPot.h
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

#ifndef CtrlPot_h
#define CtrlPot_h

#include "CtrlBase.h"
#include <Arduino.h>

class CtrlPotBase : public IMuxableInput
{
protected:
    uint8_t sig; // Analog pin connected to the potentiometer.
    int maxOutputValue; // The maximum output value of the potentiometer.
    uint8_t margin; // Margin to handle noisy pots.
    uint16_t lastValue = 0; // Last read value from the potentiometer.
    uint16_t lastMappedValue = 0; // Last mapped value.
    uint16_t analogMax = 1023; // Maximum value from analogRead().

    CtrlPotBase(
        uint8_t sig,
        int maxOutputValue,
        uint8_t margin
    );

    virtual uint16_t processInput();

    virtual void onValueChange(int value);

    public:
        void process() override;

        [[nodiscard]] uint16_t getValue() const;
};

class CtrlPot final : public CtrlPotBase
{
    using CallbackFunction = void (*)(int);
    CallbackFunction onValueChangeCallback;

    protected:
        CtrlPot(
            uint8_t sig,
            int maxOutputValue,
            uint8_t margin,
            CallbackFunction onValueChangeCallback = nullptr
        );

    public:
        static CtrlPot create(
            uint8_t sig,
            int maxOutputValue,
            uint8_t margin,
            CallbackFunction onValueChangeCallback = nullptr
        );

        void setOnValueChange(CallbackFunction callback);

    private:
        void onValueChange(int value) override;
};

#endif